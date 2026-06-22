#include <iostream>
#include <vector>
using namespace std;

// Base Class
class BankAccount
{
protected:
    int accountNumber;
    string accountHolderName;

private:
    double balance; // Encapsulation

public:
    BankAccount(int accNo, string name, double bal)
    {
        accountNumber = accNo;
        accountHolderName = name;
        balance = bal;
    }

    virtual ~BankAccount() {}

    double getBalance()
    {
        return balance;
    }

    void setBalance(double bal)
    {
        balance = bal;
    }

    virtual void deposit(double amount)
    {
        setBalance(getBalance() + amount);
        cout << "Amount Deposited Successfully!\n";
    }

    virtual void withdraw(double amount)
    {
        if (amount <= getBalance())
        {
            setBalance(getBalance() - amount);
            cout << "Amount Withdrawn Successfully!\n";
        }
        else
        {
            cout << "Insufficient Balance!\n";
        }
    }

    virtual double calculateInterest()
    {
        return 0;
    }

    virtual void displayAccountInfo()
    {
        cout << "\nAccount Number : " << accountNumber;
        cout << "\nAccount Holder : " << accountHolderName;
        cout << "\nBalance        : " << getBalance() << endl;
    }
};

// Savings Account
class SavingsAccount : public BankAccount
{
private:
    double interestRate;

public:
    SavingsAccount(int accNo, string name, double bal, double rate)
        : BankAccount(accNo, name, bal)
    {
        interestRate = rate;
    }

    double calculateInterest() override
    {
        return getBalance() * interestRate / 100;
    }

    void displayAccountInfo() override
    {
        cout << "\n--- Savings Account ---";
        BankAccount::displayAccountInfo();
        cout << "Interest Rate : " << interestRate << "%\n";
    }
};

// Checking Account
class CheckingAccount : public BankAccount
{
private:
    double overdraftLimit;

public:
    CheckingAccount(int accNo, string name, double bal, double limit)
        : BankAccount(accNo, name, bal)
    {
        overdraftLimit = limit;
    }

    bool checkOverdraft(double amount)
    {
        return amount <= (getBalance() + overdraftLimit);
    }

    void withdraw(double amount) override
    {
        if (checkOverdraft(amount))
        {
            setBalance(getBalance() - amount);
            cout << "Withdrawal Successful!\n";
        }
        else
        {
            cout << "Overdraft Limit Exceeded!\n";
        }
    }

    void displayAccountInfo() override
    {
        cout << "\n--- Checking Account ---";
        BankAccount::displayAccountInfo();
        cout << "Overdraft Limit : " << overdraftLimit << endl;
    }
};

// Fixed Deposit Account
class FixedDepositAccount : public BankAccount
{
private:
    int term;
    double interestRate;

public:
    FixedDepositAccount(int accNo, string name, double bal,
                        int t, double rate)
        : BankAccount(accNo, name, bal)
    {
        term = t;
        interestRate = rate;
    }

    double calculateInterest() override
    {
        return getBalance() * interestRate * term / (100 * 12);
    }

    void withdraw(double amount) override
    {
        cout << "Withdrawal Not Allowed Before Maturity!\n";
    }

    void displayAccountInfo() override
    {
        cout << "\n--- Fixed Deposit Account ---";
        BankAccount::displayAccountInfo();
        cout << "Term : " << term << " Months\n";
        cout << "Interest Rate : " << interestRate << "%\n";
    }
};

int main()
{
    vector<BankAccount*> accounts;

    accounts.push_back(
        new SavingsAccount(101, "Nikhil", 10000, 5));

    accounts.push_back(
        new CheckingAccount(102, "Rahul", 15000, 5000));

    accounts.push_back(
        new FixedDepositAccount(103, "Amit", 50000, 12, 7));

    int choice;

    do
    {
        cout << "\n\n===== BANK MANAGEMENT SYSTEM =====";
        cout << "\n1. Display All Accounts";
        cout << "\n2. Deposit";
        cout << "\n3. Withdraw";
        cout << "\n4. Calculate Interest";
        cout << "\n5. Exit";
        cout << "\nEnter Choice : ";
        cin >> choice;

        int index;
        double amount;

        switch(choice)
        {
        case 1:
            for(auto acc : accounts)
                acc->displayAccountInfo();
            break;

        case 2:
            cout << "Account Index (0-2): ";
            cin >> index;
            cout << "Amount: ";
            cin >> amount;
            accounts[index]->deposit(amount);
            break;

        case 3:
            cout << "Account Index (0-2): ";
            cin >> index;
            cout << "Amount: ";
            cin >> amount;
            accounts[index]->withdraw(amount);
            break;

        case 4:
            for(auto acc : accounts)
            {
                cout << "\nInterest = "
                     << acc->calculateInterest();
            }
            cout << endl;
            break;

        case 5:
            cout << "Thank You!\n";
            break;

        default:
            cout << "Invalid Choice!\n";
        }

    } while(choice != 5);

    for(auto acc : accounts)
        delete acc;

    return 0;
}