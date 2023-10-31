# Encrypt Vault

## Overview

Encrypt Vault is a C++ console application designed for secure user authentication and enhanced file protection. This application employs password hashing, salt generation, and file encryption to ensure a robust level of security for user data and sensitive files.

## Features

- **User Registration and Authentication:**
  - Users can securely register with unique usernames and passwords.
  - Passwords are hashed and stored with randomly generated salts for increased security.
  - Authentication ensures a secure login process.

- **File Security:**
  - Generates random secure passwords for extra protection.
  - Encrypts sensitive files using a Caesar cipher-like encryption.
  - Utilizes ZIP compression with a password for additional file security.

- **Intuitive Console Interface:**
  - Provides a patterned and user-friendly console interface.
  - Modular code structure for easy maintenance and extensibility.

## Data Structures Used

- **Map:**
  - Used to store user data, mapping usernames to corresponding User structures.

- **Struct (User):**
  - Represents a user with attributes such as username, hashed password, and salt.

- **String:**
  - Various string operations are employed for password hashing, salt generation, and file handling.

- **Vector (for future extensibility):**
  - The program is structured to allow for potential future features that may benefit from the use of vectors.

## Usage

1. **Registration:**
   - Select option 1 from the main menu.
   - Enter your desired username and password when prompted.

2. **Login:**
   - Select option 2 from the main menu.
   - Enter your username and password when prompted.

3. **Secure File:**
   - Generates a random password and a text file.
   - Encrypts the file content using a Caesar cipher-like encryption.
   - Creates a ZIP file with a password for additional security.

4. **Decrypt File:**
   - Reads and prints the content of the encrypted file.
   - Decrypts the content using the original encryption password.

## Prerequisites

- C++ compiler (supporting C++11 or later).
- Standard C++ libraries.

## Installation

1. **Clone the Repository:**

    ```bash
    git clone https://github.com/akshit2941/Encrypt-Vault.git
    ```

2. **Compile the Source Code:**

    ```bash
    g++ -o main main.cpp
    ```

3. **Run the Executable:**

    ```bash
    ./main
    ```

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.
