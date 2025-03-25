# Kinesitherapy Center Desktop Application

This is a **desktop application** built with **Qt** for managing a kinesitherapy center. Currently, only the **employee management** module is functional.

## Features
- Employee management (CRUD, Search, Stats, Export to pdf)
- Basic authentication system with a default login and password recovery mechanism
- Database connectivity (requires setup)

## Installation & Setup

### 1. Prerequisites
- **Qt Creator** (with MinGW or MSVC compiler)
- **Qt Framework** (tested with Qt 5 or Qt 6)
- **MySQL Database** (or another compatible database)

### 2. Clone the Repository
```sh
git clone https://github.com/yahya-bichiou/kinesitherapy-desktop-app.git
cd kinesitherapy-desktop-app
```

### 3. Configure the Database
This project requires a database connection to run properly. To set it up:
- Open the **`connection.cpp`** or relevant connection file.
- Update the database credentials with your own.
- Ensure the database is running.

### 4. Run the Project
1. Open the project in **Qt Creator**.
2. Configure the kit and build the project.
3. Run the application.

## Default Login Credentials
**Username:** `admin`  
**Password:** `admin`

## Known Issues
- Only the **employee management** module is currently functional.
- The database connection **must be set up** before the full application works.

## Contributions
Contributions are welcome! Feel free to submit issues or pull requests.

