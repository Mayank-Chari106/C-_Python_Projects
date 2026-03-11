#include <iostream>
#include <string>

using namespace std;

class BankAccount {
private:
string accountNumber;
string accountHolderName;
double balance;

public:
// Constructor to initialize account details
BankAccount(const string& accNum, const string& holderName, double initialBalance) {
accountNumber = accNum;
accountHolderName = holderName;
balance = initialBalance;
cout << "BankAccount object created for " << accountHolderName << endl;
}
// Destructor to display a message when object is destroyed
~BankAccount() {
cout << "BankAccount object for " << accountHolderName << " is being destroyed." <<
endl;
}

// Member functions to display account info
void displayAccountInfo() const {
cout << "Account Number: " << accountNumber << endl;
cout << "Account Holder: " << accountHolderName << endl;
cout << "Balance: $" << balance << endl;
}
// Deposit function
void deposit(double amount) {
if (amount > 0) {
balance += amount;
cout << "Deposited: $" << amount << endl;
} else {
cout << "Invalid deposit amount." << endl;
}
}

// Withdraw function
void withdraw(double amount) {
if (amount > 0 && amount <= balance) {
balance -= amount;
cout << "Withdrew: $" << amount << endl;
} else {
cout << "Invalid or insufficient funds for withdrawal." << endl;
}
}
};

int main() {
// Create a bank account object
BankAccount account("7875014246", "Mayank", 100000.0);
// Display initial info
account.displayAccountInfo();
// Perform some transactions
account.deposit(500);
account.withdraw(200);
// Display final info
account.displayAccountInfo();
// When main ends, destructor will be called automatically
return 0;
}
