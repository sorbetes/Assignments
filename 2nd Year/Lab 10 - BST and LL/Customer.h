#include <string>
#include <iostream>
#pragma once

using namespace std;

class Customer {

public:
        int CustomerID;                 //start at 80000000
        string lastName;
        string firstName;
        string Address;                 //town

        Customer();
        ~Customer();
        Customer(int, string, string, string);

        Customer *c_left;
        Customer *c_right;
        Customer *c_next;

        int compare(Customer* data);
};