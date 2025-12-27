🏦 ATM CLI System (C++)

A fully-featured Command Line ATM application written in modern C++, designed to 
simulate real-world banking workflows with secure authentication, persistent storage, 
transaction logging, and enforced ATM rules.

This project focuses on clean architecture, data persistence, and realistic system 
behavior, rather than UI polish.

✨ Features

  🔐 Authentication
  
        User registration and login
        Salted password hashing
        Persistent user storage (users.db)
        Safe handling of invalid credentials
        
  💰 Banking System
  
        Persistent account balances (accounts.db)
        Deposit and withdrawal support
        ATM rule enforcement:
        Minimum withdrawal: $20
        Withdrawals must be multiples of $20
        Daily withdrawal limit: $500
        Overdraft protection
  🧾 Transaction Logging
  
        Append-only transaction log (transactions.db)
        Each transaction records:
        Username
        Timestamp
        Transaction type (DEPOSIT / WITHDRAW)
        Amount (in cents)
        Balance after transaction
        Designed like a real audit log (never rewritten)
  💾 Persistent Storage
  
      File-based storage using standard C++ I/O
      Data survives program restarts
      Clear separation between state files and logs
  🧱 Clean Architecture
  
      Auth → authentication & password handling
      Bank → business logic & rules
      Storage → file persistence
      main → CLI interface & orchestration


🗂 Project Structure

ATM/

├── data/

│   ├── users.db          # user credentials (username|salt|hash)

│   ├── accounts.db       # balances (username|balanceCents)

│   └── transactions.db  # append-only transaction log

│

├── src/

│   ├── Auth.h / Auth.cpp

│   ├── Bank.h / Bank.cpp

│   ├── Storage.h / Storage.cpp

│   └── main.cpp

│

├── CMakeLists.txt

└── README.md

🛠 Build & Run
Requirements
  
    C++14 or newer
    CMake
    CLion / MinGW / GCC / Clang

Build

    mkdir build
    cd build
    cmake ..
    cmake --build .

Run

    ./ATM

⚠️ The program assumes it is run from the project root so relative paths like 
data/users.db resolve correctly.

📄 Data Formats
  users.db
  
      username|salt|passwordHash
  accounts.db
  
      username|balanceCents
  transactions.db
  
      username|YYYY-MM-DD HH:MM:SS|TYPE|amountCents|balanceAfterCents


Example:

    ammar|2025-01-03 22:41:12|DEPOSIT|4000|4000

🧠 Design Decisions

    Balances stored in cents (long long) to avoid floating-point errors
    Append-only transaction log for auditability
    Business logic isolated from file I/O
    Relative paths + fixed working directory to avoid data loss
    Minimal global state, passed explicitly where needed

🚀 Future Improvements

    Transaction history viewer
    User-to-user transfers
    SQLite backend
    Account lockout after repeated failed logins
    Password input masking
    Unit tests

📌 Why this project matters

    This project demonstrates:
    Practical C++ system design
    File persistence and data integrity
    Real-world banking constraints
    Debugging build/runtime issues
    Clean modular architecture
    It is intentionally not a toy example.

👤 Author

    Ammaar Khan
    Computer Science Student / C++ Developer
