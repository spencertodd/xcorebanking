#include <iostream>
#include "transaction.h"

using std::cin;
using std::cout;
using std::endl;

void Transaction::deposit(Account &account)
{
    cout << account.user_name << " , enter your deposit amount: ";
    cin >> Transaction::deposit_amount;

    account.balance += Transaction::deposit_amount;
    cout << "A deposit of $" << Transaction::deposit_amount << " has been made" << endl;
    account.updateBalance(account);
    cout << "Your current balance is: " << account.balance << endl;
}

void Transaction::withdraw(Account &account)
{
    cout << "Withdraw linked" <<endl;
}

