// Copyright 2022
/* This program deals with the server side and is in charge
   of handeling the client functions which entails of username and
   password authentication, depositing money, withdrawing money,
   and charging a withdrawal service fee if the client is out of the country
   Author: Malak Lamsettef
*/

#include <iostream>
#include <fstream>       // For cerr and cout
#include <cstring>
#include "PracticalSocket.h"  // For Socket, ServerSocket, and SocketException
#include "../Assignment3/bank.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

void HandleTCPClient(TCPSocket *sock);  // TCP client handling function


int main(int argc, char *argv[]) {
    if (argc != 2) {                     // Test for correct number of arguments
        cerr << "Usage: " << argv[0] << " <Server Port>" << endl;
        exit(1);
    }

    unsigned int mathServerPort = atoi(argv[1]);  // First arg: local port

    try {
        TCPServerSocket serverSock(mathServerPort);     // Server Socket object

        for (;;) {   // Run forever
            HandleTCPClient(serverSock.accept());  // Wait for client to connect
        }
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        exit(1);
    }
    return(0);
}

// TCP client handling function
void HandleTCPClient(TCPSocket *sock) {
    cout << "Handling client ";
    try {
        cout << sock->getForeignAddress() << ":";
    } catch (const std::exception& e) {
        cerr << "Unable to get foreign address" << endl;
        cerr << e.what() << endl;
    }
    try {
        cout << sock->getForeignPort();
    } catch (const std::exception& e) {
        cerr << "Unable to get foreign port" << endl;
        cerr << e.what() << endl;
    }
    cout << endl;

    char name[50];
    int deposit;
    char type;
    int out = 0;
    int option;
    int depAmt;
    int drawAmt;
    int balance;

    char username[32];
    char password[32];
    int code = 1;
    //  As long as the code is equal to one get the username
    //  and password and authenticate
    while (code == 1) {
    sock->recv(&username, sizeof(username));
    sock->recv(&password, sizeof(password));
    code = authenticate(username, password);

    sock->send(&code, sizeof(code));
    }
    sock->recv(&option, sizeof(option));
    while (option != 4) {
        switch (option) {
        //  If the client picks option 1 from the menu,
        //  get the deposit amount and username from client
        //  Then, check the final balance and send it back
        case 1:
        sock -> recv(&depAmt, sizeof(depAmt));
        sock -> recv(&username, sizeof(username));
        balance = dep(depAmt, username);
        sock -> send(&balance, sizeof(balance));
        break;
        //  If the client picks option 2 from the menu, get the
        //  withdrawal amount and username from client.
        //  Then, check the final balance and send it back
        case 2:
        sock -> recv(&drawAmt, sizeof(drawAmt));
        sock->recv(&username, sizeof(username));
        balance = withdraw(drawAmt, username);
        sock -> send(&balance, sizeof(balance));
        break;
        //  If the client picks option 3 from the menu, get the withdrawal
        //  amount and username from client. Then, the final balance is
        //  calculated by taking the withdrawal amount as well as
        //  the out of country fee that is attached in foreign transactions
        case 3:
        sock -> recv(&drawAmt, sizeof(drawAmt));
        sock->recv(&username, sizeof(username));
        balance = outCountryFee(drawAmt, username);
        sock -> send(&balance, sizeof(balance));
        break;
        }
    }
    delete sock;
}
/*
    This deposit method takes in a deposit from the user which then
    gets added to the current balance that is found in a text file.
    The final balance is then outputted back into the text file
*/
int dep(int depAmt, char name[32]) {
    char aname[32];
    int balance;
    int curbalance;
    ifstream account("account.txt");
    ofstream inaccount("inaccount.txt");
    account >> aname;
    inaccount << aname;
    inaccount << " ";
    while (strcmp(aname, name) != 0) {
        account >> balance;
        inaccount << balance << endl;
        account >> aname;
        inaccount << aname;
        inaccount << " ";
    }
    account >> balance;
    balance = balance + depAmt;
    curbalance = balance;
    inaccount << balance << endl;

    while (!account.eof()) {
         account >> aname;
         inaccount << aname;
         inaccount << " ";
         account >> balance;
         inaccount << balance << endl;
    }
    ifstream oldAccount("inaccount.txt");
    ofstream newAccount("account.txt");

    while (!oldAccount.eof()) {
         oldAccount >> aname;
         newAccount << aname;
         newAccount << " ";
         oldAccount >> balance;
         newAccount << balance << endl;
    }
    return curbalance;
}
/*  This withdrawal method takes in a withdrawal from the user which
    then gets subtracted to the current balance that is found in a text file.
    The final balance is then outputted back into the text file
*/ 
int withdraw(int drawAmt, char name[32]) {
    char aname[32];
    int balance;
    int currBalance;
    ifstream account("account.txt");
    ofstream inaccount("inaccount.txt");
    account >> aname;
    inaccount << aname;
    inaccount << " ";
    while (strcmp(aname, name) != 0) {
        account >> balance;
        inaccount << balance << endl;
        account >> aname;
        inaccount << aname;
        inaccount << " ";
    }
    account >> balance;

    balance = balance - drawAmt;
    currBalance = balance;
    inaccount << balance << endl;
    while (!account.eof()) {
         account >> aname;
         inaccount << aname;
         inaccount << " ";
         account >> balance;
         inaccount << balance << endl;
    }
    ifstream oldAccount("inaccount.txt");
    ofstream newAccount("account.txt");
    while (!oldAccount.eof()) {
         oldAccount >> aname;
         newAccount << aname;
         newAccount << " ";
         oldAccount >> balance;
         newAccount << balance << endl;
    }
    return currBalance;
}
/*  This authenticate method takes in the username and password
     a client enters and determines whether or not the client has
     access to use this banking service
*/
int authenticate(char username[32], char password[32]) {
    int code = 1;
    char name[32];
    char pw[32];
    ifstream account("password.txt");
    account >> name;
    if (strcmp(username, name) != 0 && !account.eof()) {
        account >> pw;
        account >> name;
    }
    if (account.eof()) {
        return code;
    }
    account >> pw;
    if (strcmp(password, pw) == 0) {
            code = 0;
    }
    return code;
}
/*  This method takes in a withdrawal from the user which gets
    multiplied with 0.05 as this bank charges a 5 percent fee for
    using the banking service out of the country. Then the balance found on
    the text file gets subtracted with the amount they want to withdraw as
    well as the amount they were charged in service fees.
    The final balance is then outputted back into the text file
*/
int outCountryFee(int drawAmt, char name[32]) {
    char aname[32];
    int balance;
    int currBalance;
    ifstream account("account.txt");
    ofstream inaccount("inaccount.txt");
    account >> aname;
    inaccount << aname;
    inaccount << " ";
    while (strcmp(aname, name) !=0) {
        account >> balance;
        inaccount << balance << endl;
        account >> aname;
        inaccount << aname;
        inaccount << " ";
    }
    account >> balance;

    balance = ((balance - drawAmt) - (drawAmt * 0.05));
    currBalance = balance;
    inaccount << balance << endl;
    while (!account.eof()) {
         account >> aname;
         inaccount << aname;
         inaccount << " ";
         account >> balance;
         inaccount << balance << endl;
    }
    ifstream oldAccount("inaccount.txt");
    ofstream newAccount("account.txt");
    while (!oldAccount.eof()) {
         oldAccount >> aname;
         newAccount << aname;
         newAccount << " ";
         oldAccount >> balance;
         newAccount << balance << endl;
    }
    return currBalance;
}
