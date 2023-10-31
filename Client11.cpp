// Copyright 2022
// This program creates a menu for the client which allows them to choose
// between three options after they have been authenticated to use the system
// Author: Malak Lamsettef

#include <iostream>
#include <cstring>
#include "PracticalSocket.h"  // For Socket
#include "../Assignment3/bank.h"

using std::cout;
using std::cerr;
using std::endl;


int main(int argc, char *argv[]) {
    if (argc != 3) {     // Test for correct number of arguments
        cerr << "Usage: " << argv[0]
             << " <Server> <Port>" << endl;
        exit(1);
    }

    string serverAddress = argv[1];  // First arg: server address
    unsigned int mathServerPort = atoi(argv[2]);
    // int x = atoi(argv[3]); // number to send
    try {
        // Establish connection with the echo server
        TCPSocket sock(serverAddress, mathServerPort);
        char username[32];
        char password[32];
        int code = 1;
        while (code == 1) {
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;
        // Send the user name and password to server and receive the result
        sock.send(&username, sizeof(username));
        sock.send(&password, sizeof(password));
        sock.recv(&code, sizeof(code));
         if (code == 1) {
            cout << "Login Failed" << endl;
        }
        }
            cout << "Login Successful"  << endl;
    int ch;
    int balance;
    int depAmt;
    int drawAmt;
    char line[]= " ";
    // Creates a menu for client to pick an option from
    do {
        system("cls");
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t01. DEPOSIT AMOUNT";
        cout << "\n\n\t02. WITHDRAW AMOUNT";
        cout << "\n\n\t03. OUT OF COUNTRY SERVICE FEE";
        cout << "\n\n\t04. EXIT";
        cout << "\n\n\tSelect Your Option (1-4) ";
        cin >> ch;
        system("cls");
        switch (ch) {
        //  If client picks option 1, the client would like to deposit
        //  money to their account
        case 1:
            cout << "Please Confirm Username: ";
            cin >> username;
            cout << "\n\nEnter The Amount To Be Deposited: ";
            cin >> depAmt;
            sock.send(&ch, sizeof(ch));
            sock.send(&depAmt, sizeof(depAmt));
            sock.send(&username, sizeof(username));
            sock.recv(&balance, sizeof(balance));
            cout << "Successful, Your Current Balance Is: " << balance;
            break;
        //  If client picks option 2, the client would like to withdraw
        //  money from their account
        case 2:
            cout << "Please Confirm Username: ";
            cin >> username;
            cout << "\n\nEnter The Amount To Be Withdrawn: ";
            cin >> drawAmt;
            sock.send(&ch, sizeof(ch));
            sock.send(&drawAmt, sizeof(drawAmt));
            sock.send(&username, sizeof(username));
            sock.recv(&balance, sizeof(balance));
            cout << "Successful, Your Current Balance Is " << balance;
            break;
        //  If client picks option 3, the client is out of the country
        //  and is charged a fee which is subtracted from their balance
        //  along with their withdrawal
        case 3:
            cout << "Please Confirm Username: ";
            cin >> username;
            cout << "\n\nEnter The Amount To Be Withdrawn: ";
            cin >> drawAmt;
            sock.send(&ch, sizeof(ch));
            sock.send(&drawAmt, sizeof(drawAmt));
            sock.send(&username, sizeof(username));
            sock.recv(&balance, sizeof(balance));
            cout << "Balance After Foreign Transfer Fee: " << balance;
            break;
        //  If client picks option 4, the client would like to
        //  exit the banking system
        case 4:
            cout << "\n\n\tThank You For Using My Banking System";
            break;
         default:
         cout << "\a";
        }
        cin.ignore();
        cin.get();
    //  Do any of the three methods as long as the client does not
    //  pick a number that is not equal to 4
    } while (ch != 4);
    } catch(std::exception &e) {
        cerr << e.what() << endl;
        exit(1);
    }
    return(0);
}
