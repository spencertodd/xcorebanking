#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include "account.h"

using std::string;
using std::vector;
using std::unordered_set;

class Transaction
{
    public:
        int type;
        void deposit(Account &account);
        void withdraw(Account &account);
    private:
        double deposit_amount;

};