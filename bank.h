// Copyright 2022
// This header file containing all the methods used
// Author: Malak Lamsettef
#ifndef ASSIGNMENT3_BANK_H_
#define ASSIGNMENT3_BANK_H_

int authenticate(char username[], char password[]);
int dep(int depAmt, char name[]);
int withdraw(int drawAmt, char name[]);
int outCountryFee(int drawAmt, char name[]);
#endif  // ASSIGNMENT3_BANK_H_
