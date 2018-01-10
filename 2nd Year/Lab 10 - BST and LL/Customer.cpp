#include <iostream>
#include <string>
#include "Customer.h"

Customer::Customer():
        CustomerID (80000000), lastName (""),
        firstName (""), Address (""), c_left (NULL), c_right (NULL), c_next (NULL) {
                //cout << "DEFAULT CUSTOMER CONSTRUCTOR" << endl;
};

Customer::~Customer(){
        if (c_left!= NULL)
                delete c_left;
        if (c_right!=NULL)
                delete c_right;
        //cout << "CUSTOMER DESTRUCTOR" << endl;
}

Customer::Customer (int ID, string lastname, string firstname, string address):
        CustomerID (ID), lastName (lastname),
        firstName (firstname), Address (address), c_next (NULL) {
                cout << "CUSTOMER CONSTRUCTOR" << endl;
}

int Customer::compare(Customer* data) {
        //Used to put Accounts into Bank in order of Account ID
        if(CustomerID > data->CustomerID)
                return 0;
        else return 1;
}