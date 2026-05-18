# Bank Management System (C++)

A console-based Bank Management System built using C++ with file handling and a role-based access control system.

---

## Features

- Client management (Add, Delete, Update, Search, List)
- Transactions (Deposit, Withdraw, Total balances)
- User management system (Add, Delete, Update, Search)
- Login system with username & password
- Permission-based access control (bitwise system)

---

## Technologies

- C++
- File Handling (fstream)
- Structs & Enums
- Vectors
- Console Application

---

##  Project Structure

```txt
bank-management-system-cpp/
├── src/
│   └── main.cpp
├── data/
│   ├── ClientsData.txt
│   └── UsersData.txt
├── README.md
├── LICENSE
└── .gitignore
```
---

## Permissions

- 1: Show Clients
- 2: Add Client
- 4: Delete Client
- 8: Update Client
- 16: Find Client
- 32: Transactions
- 64: Manage Users
- -1: Full Access (Admin)

---

## Notes

- This project is for learning purposes.
- It use divide and conquer
- Focuses on file handling and system design in C++.
- No database used, only text files.


