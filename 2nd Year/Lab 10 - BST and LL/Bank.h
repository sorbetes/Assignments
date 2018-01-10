#include <string>
#include "Account.h"
#include "Customer.h"

class Bank {

private:
        Account *a_root;
        Customer *c_root;
        int NumCustomers;
        int Sum;
        int NumComparisons;
        int NumAccounts;

        Account *a_head;
        Customer *c_head;

public:

        Bank();
        ~Bank();

        void addCustomerBST(Customer *c);
        void addAccountBST(Account *a);
        Customer *FindCustomerBST(int id);

        void addCustomerLL(Customer *c);
        void addAccountLL(Account *a);
        Customer *FindCustomerLL(int id);

        int SumBalance();
        int NumberOfCustomers();
        int NumberofComparisons();
        int NumberOfAccounts();
};