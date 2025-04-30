#include "account.h"

// date class use
bool Date::setDate(int m, int d, int y)
{
    if (m < 1 || m > 12 || d < 1 || d > 31 || y < 1900)
    {
        return false;
    }

    // validation for days in month
    if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30)
    {
        return false;
    }
    if (m == 2)
    {
        bool leapYear = (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
        if ((leapYear && d > 29) || (!leapYear && d > 28))
        {
            return false;
        }
    }

    month = m;
    day = d;
    year = y;
    return true;
}

bool Date::readFromUser(const std::string &prompt)
{
    int m, d, y;
    char separator;

    std::cout << prompt << " (mm/dd/yyyy): ";
    std::cin >> m >> separator >> d >> separator >> y;

    if (std::cin.fail() || separator != '/')
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "INVALID date format. Please use mm/dd/yyyy format.\n";
        return false;
    }

    if (!setDate(m, d, y))
    {
        std::cout << "INVALID date values. Please enter a valid date.\n";
        return false;
    }

    return true;
}

std::string Date::toString() const
{
    return std::to_string(month) + "/" + std::to_string(day) + "/" + std::to_string(year);
}

std::ostream &operator<<(std::ostream &os, const Date &date)
{
    os << date.month << "/" << date.day << "/" << date.year;
    return os;
}

std::istream &operator>>(std::istream &is, Date &date)
{
    char separator;
    is >> date.month >> separator >> date.day >> separator >> date.year;
    return is;
}

// acc class use
void Account::setAccountNumber(int accNo)
{
    accountNumber = accNo;
}

bool Account::setName(const std::string &n)
{
    if (n.empty())
        return false;
    name = n;
    return true;
}

bool Account::setAge(int a)
{
    if (a < 0 || a > 120)
        return false;
    age = a;
    return true;
}

bool Account::setAddress(const std::string &addr)
{
    if (addr.empty())
        return false;
    address = addr;
    return true;
}

bool Account::setId(const std::string &idd)
{
    if (idd.empty())
        return false;
    id = idd;
    return true;
}

bool Account::setPhoneNumber(const std::string &phone)
{
    // phone number validation cheks not empty and digits only
    if (phone.empty())
        return false;

    for (char c : phone)
    {
        if (!std::isdigit(c))
            return false;
    }

    phoneNumber = phone;
    return true;
}

bool Account::setAccountType(const std::string &type)
{
    // check acc type
    std::vector<std::string> validTypes = {"Saving", "Fixed1", "Fixed2", "Fixed3"};
    if (std::find(validTypes.begin(), validTypes.end(), type) == validTypes.end())
        return false;

    accountType = type;
    return true;
}

bool Account::setBalance(double amt)
{
    if (amt < 0)
        return false;
    balance = amt;
    return true;
}

bool Account::deposit(double amount)
{
    if (amount <= 0)
        return false;

    // check if account type is fixed as we can not deposit in fixed acc
    if (accountType == "Fixed1" || accountType == "Fixed2" || accountType == "Fixed3")
    {
        return false;
    }

    balance += amount;
    return true;
}

bool Account::withdraw(double amount)
{
    if (amount <= 0 || amount > balance)
        return false;

    // check if account type is fixed as we can not withdraw from fixed acc
    if (accountType == "Fixed1" || accountType == "Fixed2" || accountType == "Fixed3")
    {
        return false;
    }

    balance -= amount;
    return true;
}

bool Account::readFromUser(int accNo)
{
    accountNumber = accNo;

    std::cout << "\nEnter the name: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    if (name.empty())
    {
        std::cout << "Name cannot be EMPTY.\n";
        return false;
    }

    if (!dateOfBirth.readFromUser("\nEnter the date of birth"))
    {
        return false;
    }

    std::cout << "\nEnter the age: ";
    std::cin >> age;
    if (std::cin.fail() || age <= 0 || age > 120)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "INVALID age. Please enter a valid number between 1 and 120.\n";
        return false;
    }

    std::cout << "\nEnter the address: ";
    std::cin.ignore();
    std::getline(std::cin, address);
    if (address.empty())
    {
        std::cout << "Address cannot be EMPTY.\n";
        return false;
    }

    std::cout << "\nEnter the id number: ";
    std::getline(std::cin, id);
    if (id.empty())
    {
        std::cout << "Id number cannot be EMPTY.\n";
        return false;
    }

    std::cout << "\nEnter the phone number: ";
    std::getline(std::cin, phoneNumber);
    if (phoneNumber.empty() || !std::all_of(phoneNumber.begin(), phoneNumber.end(), ::isdigit))
    {
        std::cout << "INVALID phone number. Please enter numbers only.\n";
        return false;
    }

    int choice;
    std::cout << "\nType of account:\n";
    std::cout << "1. Saving\n";
    std::cout << "2. Fixed1 (for 1 year)\n";
    std::cout << "3. Fixed2 (for 2 years)\n";
    std::cout << "4. Fixed3 (for 3 years)\n";
    std::cout << "Enter your choice (1-4): ";
    std::cin >> choice;

    if (std::cin.fail() || choice < 1 || choice > 4)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "INVALID choice. Please enter a number between 1 and 4.\n";
        return false;
    }

    switch (choice)
    {
    case 1:
        accountType = "Saving";
        break;
    case 2:
        accountType = "Fixed1";
        break;
    case 3:
        accountType = "Fixed2";
        break;
    case 4:
        accountType = "Fixed3";
        break;
    }

    std::cout << "\nEnter initial deposit amount: ₹";
    std::cin >> balance;
    if (std::cin.fail() || balance < 0)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "INVALID amount. Please enter a positive number.\n";
        return false;
    }

    // set date created to today
    time_t now = time(nullptr);
    struct tm *timeinfo = localtime(&now);
    dateCreated.setDate(timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_year + 1900);

    return true;
}

void Account::display() const
{
    std::cout << "\n\n------ Account Information ------\n";
    std::cout << "Account Number: " << accountNumber << "\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Date of Birth: " << dateOfBirth.toString() << "\n";
    std::cout << "Age: " << age << "\n";
    std::cout << "Address: " << address << "\n";
    std::cout << "Id Number: " << id << "\n";
    std::cout << "Phone Number: " << phoneNumber << "\n";
    std::cout << "Account Type: " << accountType << "\n";
    std::cout << "Balance: ₹" << std::fixed << std::setprecision(2) << balance << "\n";
    std::cout << "Date Created: " << dateCreated.toString() << "\n";
    std::cout << "--------------------------------\n";
}

std::ostream &operator<<(std::ostream &os, const Account &account)
{
    os << account.accountNumber << " "
       << account.name << " "
       << account.dateOfBirth << " "
       << account.age << " "
       << account.address << " "
       << account.id << " "
       << account.phoneNumber << " "
       << account.accountType << " "
       << account.balance << " "
       << account.dateCreated;
    return os;
}

std::istream &operator>>(std::istream &is, Account &account)
{
    is >> account.accountNumber;
    is.ignore();
    std::getline(is, account.name, ' ');
    is >> account.dateOfBirth;
    is >> account.age;
    is.ignore();
    std::getline(is, account.address, ' ');
    std::getline(is, account.id, ' ');
    std::getline(is, account.phoneNumber, ' ');
    std::getline(is, account.accountType, ' ');
    is >> account.balance;
    is >> account.dateCreated;
    return is;
}

// BankingSystem class use
BankingSystem::BankingSystem()
{
    loadAccounts();
}

void BankingSystem::forDelay(int seconds)
{
    time_t start = time(nullptr);
    while (time(nullptr) < start + seconds)
        ;
}

int BankingSystem::getNextAccountNumber()
{
    if (accounts.empty())
        return 1001; // first acc no.

    int maxAccNo = 0;
    for (const auto &account : accounts)
    {
        maxAccNo = std::max(maxAccNo, account.getAccountNumber());
    }
    return maxAccNo++;
}

bool BankingSystem::isAccountExists(int accNo)
{
    for (const auto &account : accounts)
    {
        if (account.getAccountNumber() == accNo)
            return true;
    }
    return false;
}

int BankingSystem::findAccountIndex(int accNo)
{
    for (size_t i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].getAccountNumber() == accNo)
            return static_cast<int>(i);
    }
    return -1;
}

int BankingSystem::findAccountIndex(const std::string &name)
{
    for (size_t i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].getName() == name)
            return static_cast<int>(i);
    }
    return -1;
}

void BankingSystem::saveAccounts()
{
    std::ofstream outFile(RECORDS_FILE);
    if (!outFile)
    {
        std::cout << "ERROR: Cannot open file for writing.\n";
        return;
    }

    for (const auto &account : accounts)
    {
        outFile << account << "\n";
    }

    outFile.close();
}

void BankingSystem::loadAccounts()
{
    accounts.clear();

    std::ifstream inFile(RECORDS_FILE);
    if (!inFile)
    {
        std::cout << "No existing accounts found. Starting with empty database.\n";
        return;
    }

    Account account;
    while (inFile >> account)
    {
        accounts.push_back(account);
        inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    inFile.close();
}

int BankingSystem::getMenuChoice()
{
    int choice;
    std::cout << "\n\n\t\t------- BankEase Banking Management System -------\n";
    std::cout << "\n\t\t\t       WELCOME TO THE MENU\n";
    std::cout << "\n\t1. Create New Account";
    std::cout << "\n\t2. Update Information of Existing Account";
    std::cout << "\n\t3. Perform Transactions";
    std::cout << "\n\t4. Check Account Details";
    std::cout << "\n\t5. Remove Existing Account";
    std::cout << "\n\t6. View All Accounts";
    std::cout << "\n\t7. Exit";
    std::cout << "\n\n\tEnter your choice (1-7): ";

    std::cin >> choice;

    if (std::cin.fail() || choice < 1 || choice > 7)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "INVALID choice. Please enter a number between 1 and 7.\n";
        return -1;
    }

    return choice;
}

bool BankingSystem::login()
{
    std::string password;
    std::cout << "\n\n\tEnter the password to login: ";
    std::cin >> password;

    if (password == PASSWORD)
    {
        std::cout << "\n\nPassword match! Loading... ";
        forDelay(2);
        return true;
    }
    else
    {
        std::cout << "\nWRONG Password!\n";
        while (true)
        {
            int choice;
            std::cout << "Enter 1 to try again and 0 to exit: ";
            std::cin >> choice;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "INVALID input. Please enter 0 or 1.\n";
                continue;
            }

            if (choice == 1)
            {
                return login();
            }
            else if (choice == 0)
            {
                return false;
            }
            else
            {
                std::cout << "INVALID choice. Please enter 0 or 1.\n";
            }
        }
    }
}

void BankingSystem::createNewAccount()
{
    int accountNumber = getNextAccountNumber();
    Account newAccount;

    std::cout << "\n\n\t----- ADD RECORD -----";

    if (newAccount.readFromUser(accountNumber))
    {
        accounts.push_back(newAccount);
        saveAccounts();
        std::cout << "\nAccount created successfully!" << std::endl;
    }
    else
    {
        std::cout << "\nFAILED to create account. Please try again." << std::endl;
    }
}

void BankingSystem::updateAccount()
{
    int accountNumber;
    std::cout << "\nEnter the account number to update: ";
    std::cin >> accountNumber;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "INVALID account number.\n";
        return;
    }

    int index = findAccountIndex(accountNumber);
    if (index == -1)
    {
        std::cout << "\nAccount not found!\n";
        return;
    }

    int choice;
    std::cout << "\nWhat information do you want to update?";
    std::cout << "\n1. Address";
    std::cout << "\n2. Phone Number";
    std::cout << "\nEnter your choice (1-2): ";
    std::cin >> choice;

    if (std::cin.fail() || (choice != 1 && choice != 2))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "INVALID choice.\n";
        return;
    }

    std::cin.ignore();

    if (choice == 1)
    {
        std::string newAddress;
        std::cout << "Enter new address: ";
        std::getline(std::cin, newAddress);

        if (newAddress.empty())
        {
            std::cout << "Address cannot be empty.\n";
            return;
        }

        if (accounts[index].setAddress(newAddress))
        {
            std::cout << "Address updated successfully!\n";
            saveAccounts();
        }
        else
        {
            std::cout << "FAILED to update address.\n";
        }
    }
    else if (choice == 2)
    {
        std::string newPhone;
        std::cout << "Enter new phone number: ";
        std::getline(std::cin, newPhone);

        if (newPhone.empty() || !std::all_of(newPhone.begin(), newPhone.end(), ::isdigit))
        {
            std::cout << "INVALID phone number. Please enter digits only.\n";
            return;
        }

        if (accounts[index].setPhoneNumber(newPhone))
        {
            std::cout << "Phone number updated successfully!\n";
            saveAccounts();
        }
        else
        {
            std::cout << "FAILED to update phone number.\n";
        }
    }
}

void BankingSystem::performTransaction()
{
    int accountNumber;
    std::cout << "\nEnter the account number: ";
    std::cin >> accountNumber;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "INVALID account number.\n";
        return;
    }

    int index = findAccountIndex(accountNumber);
    if (index == -1)
    {
        std::cout << "\nAccount not found!\n";
        return;
    }

    // check if acc is a fixed acc
    if (accounts[index].getAccountType().find("Fixed") != std::string::npos)
    {
        std::cout << "\nYou cannot deposit or withdraw cash in Fixed accounts.\n";
        return;
    }

    int choice;
    std::cout << "\nDo you want to:";
    std::cout << "\n1. Deposit";
    std::cout << "\n2. Withdraw";
    std::cout << "\nEnter your choice (1-2): ";
    std::cin >> choice;

    if (std::cin.fail() || (choice != 1 && choice != 2))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "INVALID choice.\n";
        return;
    }

    double amount;
    if (choice == 1)
    {
        std::cout << "Enter the amount you want to deposit: ₹";
        std::cin >> amount;

        if (std::cin.fail() || amount <= 0)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "INVALID amount. Please enter a positive number.\n";
            return;
        }

        if (accounts[index].deposit(amount))
        {
            std::cout << "\nDeposited successfully!\n";
            saveAccounts();
        }
        else
        {
            std::cout << "\nDeposit failed.\n";
        }
    }
    else if (choice == 2)
    {
        std::cout << "Enter the amount you want to withdraw: ₹";
        std::cin >> amount;

        if (std::cin.fail() || amount <= 0)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "INVALID amount. Please enter a positive number.\n";
            return;
        }

        if (accounts[index].withdraw(amount))
        {
            std::cout << "\nWithdrawn successfully!\n";
            saveAccounts();
        }
        else
        {
            std::cout << "\nWithdrawal FAILED. Check if you have sufficient balance.\n";
        }
    }
}

void BankingSystem::checkAccountDetails()
{
    int choice;
    std::cout << "\nDo you want to check by:";
    std::cout << "\n1. Account Number";
    std::cout << "\n2. Name";
    std::cout << "\nEnter your choice (1-2): ";
    std::cin >> choice;

    if (std::cin.fail() || (choice != 1 && choice != 2))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "INVALID choice.\n";
        return;
    }

    int index = -1;

    if (choice == 1)
    {
        int accountNumber;
        std::cout << "Enter the account number: ";
        std::cin >> accountNumber;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "INVALID account number.\n";
            return;
        }

        index = findAccountIndex(accountNumber);
    }
    else if (choice == 2)
    {
        std::string name;
        std::cout << "Enter the name: ";
        std::cin.ignore();
        std::getline(std::cin, name);

        if (name.empty())
        {
            std::cout << "Name cannot be EMPTY.\n";
            return;
        }

        index = findAccountIndex(name);
    }

    if (index == -1)
    {
        std::cout << "\nAccount not found!\n";
        return;
    }

    accounts[index].display();
}

void BankingSystem::removeAccount()
{
    int accountNumber;
    std::cout << "\nEnter the account number you want to delete: ";
    std::cin >> accountNumber;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "INVALID account number.\n";
        return;
    }

    int index = findAccountIndex(accountNumber);
    if (index == -1)
    {
        std::cout << "\nAccount not found!\n";
        return;
    }

    accounts.erase(accounts.begin() + index);
    saveAccounts();
    std::cout << "\nAccount deleted successfully!\n";
}

void BankingSystem::viewAllAccounts()
{
    if (accounts.empty())
    {
        std::cout << "\nNo accounts found!\n";
        return;
    }

    std::cout << "\n\n----- LIST OF ALL ACCOUNTS -----\n";
    std::cout << "\nAcc No.\tName\t\tAccount Type\tBalance\n";
    std::cout << "-----------------------------------------------\n";

    for (const auto &account : accounts)
    {
        std::cout << account.getAccountNumber() << "\t"
                  << std::setw(10) << std::left << account.getName() << "\t"
                  << std::setw(10) << std::left << account.getAccountType() << "\t"
                  << "₹" << std::fixed << std::setprecision(2) << account.getBalance() << "\n";
    }
}

void BankingSystem::exitSystem()
{
    std::cout << "\n\n\nThank you for using BankEase Banking Management System!\n";
    std::cout << "Made by: NISHANT\n";
    std::cout << "Exiting...\n";
}

void BankingSystem::run()
{
    if (!login())
    {
        return;
    }

    while (true)
    {
        int choice = getMenuChoice();
        if (choice == -1)
            continue;

        switch (choice)
        {
        case 1:
            createNewAccount();
            break;
        case 2:
            updateAccount();
            break;
        case 3:
            performTransaction();
            break;
        case 4:
            checkAccountDetails();
            break;
        case 5:
            removeAccount();
            break;
        case 6:
            viewAllAccounts();
            break;
        case 7:
            exitSystem();
            return;
        }

        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
}