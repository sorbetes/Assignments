#include <iostream>
#include <string>
#include "Account.h"

Account::Account():
        AccountID (90000000), CustomerID (80000000),
        Balance (0), a_left (NULL), a_right(NULL), a_next (NULL) {
                //cout << "DEFAULT ACCOUNT CONSTRUCTOR" << endl;
};

Account::~Account(){
        if (a_left!= NULL)
                delete a_left;
        if (a_right!=NULL)
                delete a_right;
        //cout << "ACCOUNT DESTRUCTOR" << endl;
}

Account::Account (int aid, int cid, int bal):
        AccountID (aid), CustomerID (cid),
        Balance (bal), a_next (NULL) {
                cout << "ACCOUNT CONSTRUCTOR" << endl;
}

int Account::compare(Account* data) {
        //Used to put Accounts into Bank in Account ID order
        if(AccountID > data->AccountID)
                return 0;
        else return 1;
}