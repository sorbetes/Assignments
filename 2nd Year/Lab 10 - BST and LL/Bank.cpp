#include <iostream>
#include <string>
#include "Bank.h"
#include <fstream>
#include <iomanip>

Bank::Bank(){
        a_root = NULL;
        c_root = NULL;
        a_head = NULL;
        c_head = NULL;
        NumCustomers = 0;
        Sum = 0;
        NumComparisons = 0;
        NumAccounts = 0;
        cout << "DEFAULT BANK CONSTRUCTOR" << endl;
}

Bank::~Bank(){
        if(a_root != NULL)
                delete a_root;

        if(c_root != NULL)
                delete c_root;

        cout << "BANK DESTRUCTOR" << endl;

        while(a_head) {
                Account *ap = a_head->a_next;
                delete a_head;
                a_head = ap;
        }

        while(c_head) {
                Customer *cp = c_head->c_next;
                delete c_head;
                c_head = cp;
        }
        cout << "BANK DESTRUCTOR" << endl;
}

void Bank::addCustomerBST (Customer* c){
        Customer *p, *pp;
        int r;

        if (c_root == NULL)
                c_root = c;

        else {
                p = c_root;
                pp = NULL;
                while (p) {
                        pp = p;
                        r = c->compare(p);
                        p = (r > 0) ? p->c_right : p->c_left;
                }
                if (r > 0)
                        pp->c_right = c;
                else
                        pp->c_left = c;
        }
        NumCustomers++;

}
void Bank::addAccountBST (Account* a){
        Account *p, *pp;
        int r;

        if (a_root == NULL)
                a_root = a;

        else {
                p = a_root;
                pp = NULL;
                while (p) {
                        pp = p;
                        r = a->compare(p);
                        p = (r > 0) ? p->a_right : p->a_left;
                }
                if (r > 0)
                        pp->a_right = a;
                else
                        pp->a_left = a;
        }
        Sum = Sum + a->Balance;
}

Customer* Bank::FindCustomerBST(int id){
        cout << "Looking for customer with the given ID(Binary Search Tree). " << endl;
        Customer *p, *pp;
        NumComparisons = 0;
        p = c_root;
        pp = NULL;
        while (p) {
                NumComparisons++;
                if (p->CustomerID == id){
                        cout << "-----Number of Comparisons (Binary Searh Tree): " << NumComparisons << endl;
                        return p;
                }
                pp = p;
                p = (p->CustomerID > id) ? p->c_right : p->c_left;
        }
        cout << "-----Number of Comparisons (Binary Searh Tree): " << NumComparisons << endl;
        return NULL;
}

void Bank::addCustomerLL (Customer* c){
        if((c_head == 0) || (c->compare(c_head) == 1)){
                c->c_next = c_head;
                c_head = c;
        }
        else {
                Customer *p = c_head;
                while ((p->c_next) && (c->compare(p->c_next) == 0 ))
                        p = p->c_next;

                c->c_next = p->c_next;
                p->c_next = c;
        }
        NumCustomers++;
}

void Bank::addAccountLL (Account* a){
        if((a_head == 0) || (a->compare(a_head) == 1)){
                a->a_next = a_head;
                a_head = a;
        }
        else {
                Account *p = a_head;
                while ((p->a_next) && (a->compare(p->a_next) == 0 ))
                        p = p->a_next;

                a->a_next = p->a_next;
                p->a_next = a;
        }
        Sum = Sum + a->Balance;
}

Customer* Bank::FindCustomerLL(int id){
        cout << "Looking for customer with the given ID (Linked List). " << endl;
        Customer *c = c_head;
        NumComparisons = 0;
        NumAccounts = 0;
        while(c){
                NumComparisons++;
                if(c->CustomerID==id){
                        cout << "-----Number of Comparisons(Linked List): " << NumComparisons << endl;
                        Account *a = a_head;
                        while (a){
                                if (a->CustomerID == id)
                                        NumAccounts++;
                                a = a->a_next;
                        }

                        return c;
                }
                c = c->c_next;
        }
        cout << "-----Number of Comparisons (Linked List): " << NumComparisons << endl;
        return NULL;
}

int Bank::NumberOfCustomers() {
        return NumCustomers;
}

int Bank::SumBalance(){
        return Sum;
}

int Bank::NumberofComparisons(){
        return NumComparisons;
}

int Bank::NumberOfAccounts(){
        return NumAccounts;
}