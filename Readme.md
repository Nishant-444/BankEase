# BankEase - C++ Bank Management System

**BankEase.exe** is a console-based Bank Management System written in C++ for educational purposes. It simulates basic banking operations like creating accounts, updating details, making deposits/withdrawals, viewing accounts, and storing data persistently using binary files.

## 🔧 Features

- Create a new bank account with personal details
- Update existing account information
- Perform transactions (Deposit/Withdraw)
- View account details
- Remove account
- View all existing accounts
- Password-protected access (`BankEase`)
- Data persistence using file I/O (`accounts.dat`)

## 📁 Project Structure

```
BankEase/
│
├── Account.h         # Class declarations: Date, Account, BankingSystem
├── Account.cpp       # Function definitions for the classes
├── main.cpp          # Entry point of the program
├── accounts.dat      # Binary file for storing account data
└── README.md         # Project documentation
```

## 🧾 Classes

### 1. `Date`
- Represents a simple date structure.
- Includes support for user input/output and file serialization.

### 2. `Account`
- Stores user details such as name, DOB, address, balance, etc.
- Handles deposit and withdrawal operations.
- Supports input/output through binary serialization.

### 3. `BankingSystem`
- Core controller class managing the flow of the application.
- Handles all user interactions and file storage.

## 🔐 Login

On running the application, users must enter the system password:

```
Password: BankEase
```

## 🏗️ Compilation & Execution

### 📌 Requirements

- C++ compiler (G++, Clang, MSVC, etc.)
- Terminal or command prompt

### 🔨 Compile

Use the following command to compile the application:

```bash
g++ main.cpp Account.cpp -o BankEase.exe
```

### ▶️ Run

After compilation, run the program:

```bash
./BankEase.exe     # On Linux/Mac
BankEase.exe       # On Windows
```

## 💾 Data Storage

- All accounts are saved in a binary file named `accounts.dat`.
- Serialization is manually handled to safely store complex objects (e.g., `std::string`, `Date`).

## 📚 Educational Goals

This project is intended to help beginner and intermediate C++ learners practice:
- Object-Oriented Programming (OOP)
- File handling (Binary I/O)
- Class design and encapsulation
- Basic data validation and input handling

## ✍️ Author

> Developed by a BCA Student with a goal to prepare for FAANG-level software engineering skills.

---
