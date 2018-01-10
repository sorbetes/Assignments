#include <string>
#include <iostream>
#pragma once

using namespace std;

class Account {

public:

        int AccountID;
        int CustomerID;
        int Balance;                    //in cents

        Account();
        ~Account();
        Account(int, int, int);

        Account *a_left;
        Account *a_right;
        Account *a_next;

        int compare(Account* data);
};
