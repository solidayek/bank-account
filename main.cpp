#include <iostream>
#include <string>

using namespace std;

class bankAccount {
protected:
    std::string name;
    int accountNumber;
    double balance;
public:
    bankAccount(std::string n, int a, double b);
    std::string getName() const;
    int getAccountNumber() const;
    double getBalance() const;
    virtual void makeDeposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
    virtual void createMonthlyStatement() const = 0;
    virtual ~bankAccount() {};
};

bankAccount::bankAccount(std::string n, int a, double b) {
    name = n;
    accountNumber = a;
    balance = b;
}

std::string bankAccount::getName() const {
    return name;
}

int bankAccount::getAccountNumber() const {
    return accountNumber;
}

double bankAccount::getBalance() const {
    return balance;
}

class checkingAccount : public bankAccount {
public:
    checkingAccount(std::string n, int a, double b);
    virtual void writeCheck(double amount) = 0;
};

checkingAccount::checkingAccount(std::string n, int a, double b) : bankAccount(n, a, b) {}

class serviceChargeChecking : public checkingAccount {
private:
    const double SERVICE_CHARGE = 1.0;
    int numChecks;
public:
    serviceChargeChecking(std::string n, int a, double b);
    virtual void writeCheck(double amount);
    virtual void makeDeposit(double amount);
    virtual void withdraw(double amount);
    virtual void createMonthlyStatement() const;
};

serviceChargeChecking::serviceChargeChecking(std::string n, int a, double b) : checkingAccount(n, a, b) {
    numChecks = 0;
}

void serviceChargeChecking::writeCheck(double amount) {
    if (numChecks >= 3) {
        std::cout << "Cannot write more than 3 checks per month" << std::endl;
    } else {
        balance -= amount;
        numChecks++;
    }
}

void serviceChargeChecking::makeDeposit(double amount) {
    balance += amount;
}

void serviceChargeChecking::withdraw(double amount) {
    balance -= amount;
}

void serviceChargeChecking::createMonthlyStatement() const {
    std::cout << "Monthly Statement for Service Charge Checking Account" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Account Number: " << accountNumber << std::endl;
    std::cout << "Balance: $" << balance << std::endl;
    std::cout << "Number of checks written this month: " << numChecks << std::endl;
    std::cout << "Service Charge: $" << SERVICE_CHARGE << std::endl;
}

class noServiceChargeChecking : public checkingAccount {
private:
    const double INTEREST_RATE = 0.01;
    const double MIN_BALANCE = 500.0;
public:
    noServiceChargeChecking(std::string n, int a, double b);
    virtual void writeCheck(double amount);
    virtual void makeDeposit(double amount);
    virtual void withdraw(double amount);
    virtual void createMonthlyStatement() const;
};

noServiceChargeChecking::noServiceChargeChecking(std::string n, int a, double b) : checkingAccount(n, a, b) {}

void noServiceChargeChecking::writeCheck(double amount) {
    balance -= amount;
}

void noServiceChargeChecking::makeDeposit(double amount) {
    balance += amount;
}

void noServiceChargeChecking::withdraw(double amount) {
    balance -= amount;
}

void noServiceChargeChecking::createMonthlyStatement() const {
std::cout << "Monthly Statement for No Service Charge Checking Account" << std::endl;
std::cout << "Name: " << name << std::endl;
std::cout << "Account Number: " << accountNumber << std::endl;
std::cout << "Balance: $" << balance << std::endl;
std::cout << "Interest Earned: $" << balance * INTEREST_RATE << std::endl;
}

class savingsAccount : public bankAccount {
public:
savingsAccount(std::string n, int a, double b);
virtual void makeDeposit(double amount);
virtual void withdraw(double amount);
virtual void createMonthlyStatement() const;
};

savingsAccount::savingsAccount(std::string n, int a, double b) : bankAccount(n, a, b) {}

void savingsAccount::makeDeposit(double amount) {
balance += amount;
}

void savingsAccount::withdraw(double amount) {
if (balance - amount < 0) {
std::cout << "Cannot withdraw more than the balance" << std::endl;
} else {
balance -= amount;
}
}

void savingsAccount::createMonthlyStatement() const {
std::cout << "Monthly Statement for Savings Account" << std::endl;
std::cout << "Name: " << name << std::endl;
std::cout << "Account Number: " << accountNumber << std::endl;
std::cout << "Balance: $" << balance << std::endl;
}

class highInterestSavings : public savingsAccount {
private:
const double INTEREST_RATE = 0.03;
public:
highInterestSavings(std::string n, int a, double b);
virtual void makeDeposit(double amount);
virtual void createMonthlyStatement() const;
};

highInterestSavings::highInterestSavings(std::string n, int a, double b) : savingsAccount(n, a, b) {}

void highInterestSavings::makeDeposit(double amount) {
balance += amount;
}

void highInterestSavings::createMonthlyStatement() const {
cout << "Monthly Statement for High-Interest Savings Account" << std::endl;
std::cout << "Name: " << name << std::endl;
std::cout << "Account Number: " << accountNumber << std::endl;
std::cout << "Balance: $" << balance << std::endl;
std::cout << "Interest Earned: $" << balance * INTEREST_RATE << std::endl;
} 


int main() {
string name = "Soliday Ek";
    string date = "April 13th, 2023";
    string title = "Welcome to Bank of America";

    cout << "======================================" << endl;
    cout << "|                                    |" << endl;
    cout << "|          " << title << "          |" << endl;
    cout << "|                                    |" << endl;
    cout << "|            Created by:             |" << endl;
    cout << "|              " << name << "               |" << endl;
    cout << "|                                    |" << endl;
    cout << "|             " << date << "             |" << endl;
    cout << "|                                    |" << endl;
    cout << "======================================" << endl;
  
bankAccount* accounts[4];
accounts[0] = new serviceChargeChecking("John Doe", 123456789, 1000.0);
accounts[1] = new noServiceChargeChecking("Jane Smith", 987654321, 500.0);
accounts[2] = new highInterestSavings("Bob Johnson", 246813579, 2000.0);
accounts[3] = new highInterestSavings("Alice Williams", 135792468, 10000.0);

// deposit some money into each account
accounts[0]->makeDeposit(500.0);
accounts[1]->makeDeposit(1000.0);
accounts[2]->makeDeposit(500.0);
accounts[3]->makeDeposit(2000.0);

// withdraw some money from each account
accounts[0]->withdraw(50.0);
accounts[1]->withdraw(200.0);
accounts[2]->withdraw(1000.0);
accounts[3]->withdraw(1500.0);

// write some checks from serviceChargeChecking account
static_cast<serviceChargeChecking*>(accounts[0])->writeCheck(100.0);
static_cast<serviceChargeChecking*>(accounts[0])->writeCheck(200.0);
static_cast<serviceChargeChecking*>(accounts[0])->writeCheck(300.0);
static_cast<serviceChargeChecking*>(accounts[0])->writeCheck(400.0);

// create monthly statements for all accounts
for (int i = 0; i < 4; i++) {
    accounts[i]->createMonthlyStatement();
    std::cout << std::endl;
}

// clean up
for (int i = 0; i < 4; i++) {
    delete accounts[i];
}

return 0;


}
