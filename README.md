[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=9226705&assignment_repo_type=AssignmentRepo)

# Bank Management System

Banking Management System coded using C++. This program covers simple banking operations which includes deposit, withdrawal, and added foreign transaction service fees. Before a user has access to this application, the user must authenticate themselves by entering a username and password. A text file has been created to contain several usernames and passwords of those who can access this service. While another text file contains the authenticated user’s name and current balance which is modified when the user makes a deposit or withdrawal.

This program implements a Simple TCP Client program that takes the hostname/IP of the server and port number of the Server as Command Line arguments and is able to send messages to that server and receive the response from the server back.

## Features

- Admin mode and user mode
- Username and Password Authentication
- Read in and Update Records
- Update Record Information Based on Name
- Transaction (balance inquiry after deposit, withdrawal, and any possible added fees)

## Functions

Pass by Value Functions 

Pass by Reference Functions

## Details of Files Included
#### Client11.cpp
A Simple Client that communicates with the Server and provides several menu options for users to choose from after being authenticated to use the service. Based on the PracticalSocket wrapper classes.

#### Server11.cpp
A Simple Server that handles client functions which entails username and password authentication, depositing money, withdrawing money, and charging a withdrawal service fee if the client is out of the country. Based on the PracticalSocket wrapper classes.

#### bank.h
Contains all declarations in one location.

#### password.txt
This text file contains username and password of all the users created by admin.

#### account.txt
This text file is used to store all the account details such as name and current balance. 
