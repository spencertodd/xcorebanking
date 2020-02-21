#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <climits>
#include <unordered_set>

using std::string;
using std::vector;

class Account
{
    public:
        int id;
        string first_name;
        string last_name;
        string dob;
        double balance;
        string pin;
        string user_name;

        void create(void);
        bool login(void);
        void updateBalance(Account &account);

    protected :
        void saveAccount(void);
        void createUsername(void);
        void createPin(void);
        bool validateUsername(void);
        bool validatePin(void);
        vector <vector<string>> getAccounts(void);
        vector<string> getAccount(vector <vector<string>> &accounts, string username, string pin);
    private :
        vector <vector<string>>getAccount(Account &account);
};