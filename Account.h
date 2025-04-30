#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <limits>
#include <vector>
#include <algorithm>
#include <cctype>

class Date
{
private:
    int month;
    int day;
    int year;

public:
    Date(int m = 0, int d = 0, int y = 0) : month(m), day(d), year(y) {}

    // getters
    int getMonth() const { return month; }
    int getDay() const { return day; }
    int getYear() const { return year; }

    // setters
    bool setDate(int m, int d, int y);

    // for innput
    bool readFromUser(const std::string &prompt);

    // for output
    std::string toString() const;

    // for file io
    friend std::ostream &operator<<(std::ostream &os, const Date &date);
    friend std::istream &operator>>(std::istream &is, Date &date);
};

class Account
{
private:
    int accountNumber;
    std::string name;
    Date dateOfBirth;
    int age;
    std::string address;
    std::string id;
    std::string phoneNumber;
    std::string accountType;
    double balance;
    Date dateCreated;

public:
    Account() : accountNumber(0), age(0), balance(0.0) {}

    // getters
    int getAccountNumber() const { return accountNumber; }
    std::string getName() const { return name; }
    std::string getAccountType() const { return accountType; }
    double getBalance() const { return balance; }

    // setters
    void setAccountNumber(int accNo);
    bool setName(const std::string &n);
    bool setAge(int a);
    bool setAddress(const std::string &addr);
    bool setId(const std::string &cit);
    bool setPhoneNumber(const std::string &phone);
    bool setAccountType(const std::string &type);
    bool setBalance(double amt);

    // for transactions
    bool deposit(double amount);
    bool withdraw(double amount);

    // method to gather user input for new acc
    bool readFromUser(int accNo);

    // display acc info
    void display() const;

    // methods for file io
    friend std::ostream &operator<<(std::ostream &os, const Account &account);
    friend std::istream &operator>>(std::istream &is, Account &account);
};

class BankingSystem
{
private:
    const std::string RECORDS_FILE = "accounts.dat";
    const std::string PASSWORD = "BankEase";
    std::vector<Account> accounts;

    void forDelay(int seconds);
    int getNextAccountNumber();
    bool isAccountExists(int accNo);
    int findAccountIndex(int accNo);
    int findAccountIndex(const std::string &name);
    void saveAccounts();
    void loadAccounts();
    int getMenuChoice();

public:
    BankingSystem();

    bool login();
    void createNewAccount();
    void updateAccount();
    void performTransaction();
    void checkAccountDetails();
    void removeAccount();
    void viewAllAccounts();
    void exitSystem();
    void run();
};

#endif // ACCOUNT_H