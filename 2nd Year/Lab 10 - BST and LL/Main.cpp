#include <string>
#include <iostream>
#include "Customer.h"
#include "Account.h"
#include "Bank.h"
#include <fstream>
#include <iomanip>

using namespace std;

int main () {

        Bank BankLL;
        ifstream in;

        cout << "============USING LINKED LIST===========" << endl;

        in.open("Customer0.txt");
        cout << "Opening file/Adding Customers... (Linked List)" << endl;
        if (in.fail()) {
                cout << "Unable to open Customer0.txt" << endl;
        }

        int x = 0;

        while (!in.eof()) {
                Customer *customer = new Customer();
                in >> customer->CustomerID>> customer->lastName;
                in >> customer->firstName >> customer->Address;
                x++;
                //cout << "Adding " << customer->lastName << ". Customer " << x << endl;
                BankLL.addCustomerLL(customer);
        }
        in.close();
        cout << "Added customers to Bank (LinkedList). "<< endl;

        in.open("Account0.txt");
        cout << "Opening file/Adding Accounts... (Linked List)" << endl;
        if (in.fail()) {
                cout << "Unable to open Account0.txt" << endl;
        }

        int y = 0;

        while (!in.eof()) {
                Account *account = new Account();
                in >> account->AccountID>> account->CustomerID;
                in >> account->Balance;
                y++;
                //cout << "Adding " << account->AccountID << ". Account " << y << endl;
                BankLL.addAccountLL(account);
        }

        in.close();
        cout << "Added accounts to Bank (LinkedList). "<< endl;

        int IDll;
        char yn;

        cout << "-----There are " << BankLL.NumberOfCustomers() << " customers." << endl;
        cout << "-----The sum balance of all the accounts in the bank is " << BankLL.SumBalance() << "." << endl;
        cout << "-----Would you like to search for a customer? (y or n)" << endl;
        cout << "-----";
        cin >> yn;
        while (yn == 'y'){
                cout << "-----What is the ID of the customer you are looking for?" << endl;
                cout << "-----";
                cin >> IDll;

                Customer *C;
                C = BankLL.FindCustomerLL(IDll);
                if (C == NULL)
                        cout << "-----No customer found with the ID " << IDll <<endl;
                else {
                        cout << "-----Customer ID Details-----" << endl;
                        cout << "-----Customer ID: " << C->CustomerID << endl;
                        cout << "-----Name: " <<   C->firstName << " " << C->lastName << endl;
                        cout << "-----Address: " << C->Address << endl;
                        cout << "-----Number of Accounts: " << BankLL.NumberOfAccounts() << endl;
                }

                cout << "-----Would you like to search for another customer?" << endl;
                cout << "-----";
                cin >> yn;
        }

        cout << endl;
        cout << endl;

        cout << "============USING BINARY SEARCH TREE===========" << endl;

        Bank BankBST;

        in.open("Customer0.txt");
        cout << "Opening file/Adding Customers... (Binary Search Tree)" << endl;

        if (in.fail()) {
                cout << "Unable to open Customer0.txt" << endl;
        }

        int a = 0;

        while (!in.eof()) {
                Customer *customer = new Customer();
                in >> customer->CustomerID>> customer->lastName;
                in >> customer->firstName >> customer->Address;
                a++;
                //cout << "Adding " << customer->lastName << ". Customer " << a << endl;
                BankBST.addCustomerBST(customer);
        }
        in.close();
        cout << "Added customers to Bank (BinarySearchTree). "<< endl;

        in.open("Account0.txt");
        cout << "Opening file/Adding Accounts... (Binary Search Tree)" << endl;

        if (in.fail()) {
                cout << "Unable to open Account0.txt" << endl;
        }

        int b = 0;

        while (!in.eof()) {
                Account *account = new Account();
                in >> account->AccountID>> account->CustomerID;
                in >> account->Balance;
                b++;
                //cout << "Adding " << account->AccountID << ". Account " << b << endl;
                BankBST.addAccountBST(account);
        }
        in.close();
        cout << "Added accounts to Bank (BinarySearchTree). "<< endl;

        int IDbst;
        char ny;

        cout << "-----There are " << BankBST.NumberOfCustomers() << " customers." << endl;
        cout << "-----The sum balance of all the accounts in the bank is " << BankBST.SumBalance() << "." << endl;
        cout << "-----Would you like to search for a customer? (y or n)" << endl;
        cout << "-----";
        cin >> ny;
        while (ny == 'y'){
                cout << "-----What is the ID of the customer you are looking for?" << endl;
                cout << "-----";
                cin >> IDbst;

                Customer *D;
                D = BankBST.FindCustomerBST(IDbst);
                if (D == NULL)
                        cout << "-----No customer found with the ID " << IDbst <<endl;
                else {
                        cout << "-----Customer ID Details-----" << endl;
                        cout << "-----Customer ID: " << D->CustomerID << endl;
                        cout << "-----Name: " <<   D->firstName << " " << D->lastName << endl;
                        cout << "-----Address: " << D->Address << endl;
                }

                cout << "-----Would you like to search for another customer?" << endl;
                cout << "-----";
                cin >> ny;
        }

        cout << "Goodbye." << endl;
        return 0;
}

