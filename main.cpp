#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <random>
#include <chrono>
#include <iomanip>
#include <functional>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <dirent.h>

using namespace std;

// Structure to represent a user
struct User
{
    string username;
    string hashedPassword;
    string salt;
};

// Function to generate a random salt
string generateSalt()
{
    const string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const int saltLength = 16;

    mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> distribution(0, charset.length() - 1);

    string salt;
    generate_n(back_inserter(salt), saltLength, [&]()
    { return charset[distribution(rng)]; });

    return salt;
}

// Function to hash the password with salt
string hashPassword(const string &password, const string &salt)
{
    hash<string> hasher;
    size_t hashedValue = hasher(password + salt);

    stringstream ss;
    ss << hex << setw(16) << setfill('0') << hashedValue;
    return ss.str();
}

// Function to register a new user and write to the file
void registerUser(map<string, User> &users, const string &username, const string &password)
{
    if (users.find(username) == users.end())
    {
        User newUser;
        newUser.username = username;

        // Generate a random salt
        newUser.salt = generateSalt();
        newUser.hashedPassword = hashPassword(password, newUser.salt);

        users[username] = newUser;

        // Write user data to file
        ofstream userFile("user_data.txt", ios::app); // Open file in append mode
        if (userFile.is_open())
        {
            userFile << username << " " << newUser.hashedPassword << " " << newUser.salt << endl;
            userFile.close();
            cout << "Registration successful for user: " << username << endl;
        }
        else
        {
            cerr << "Error: Unable to open user data file for writing." << endl;
        }
    }
    else
    {
        cout << "Username already exists. Please choose a different username." << endl;
    }
}

// Function to read user data from file
void readUserDataFromFile(map<string, User> &users)
{
    ifstream userFile("user_data.txt");
    if (userFile.is_open())
    {
        string username, hashedPassword, salt;
        while (userFile >> username >> hashedPassword >> salt)
        {
            User user;
            user.username = username;
            user.hashedPassword = hashedPassword;
            user.salt = salt;
            users[username] = user;
        }
        userFile.close();
    }
    else
    {
        cerr << "Warning: Unable to open user data file for reading. Continuing with an empty user list." << endl;
    }
}

// Function to authenticate a user
bool authenticateUser(const map<string, User> &users, const string &username, const string &password)
{
    auto it = users.find(username);
    if (it != users.end())
    {
        const User &user = it->second;
        string hashedInput = hashPassword(password, user.salt);

        return hashedInput == user.hashedPassword;
    }
    return false; // User not found or passwords do not match
}

// Function to generate a random password
string generateRandomPassword(int length)
{
    string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789@#*-_=+%$.";

    srand(static_cast<unsigned int>(time(nullptr)));

    string password;
    for (int i = 0; i < length; ++i)
    {
        int index = rand() % charset.length();
        password += charset[index];
    }

    return password;
}

// Function to write content to a file
void writeToFile(const string &content, const string &fileName)
{
    ofstream outputFile(fileName);

    if (!outputFile)
    {
        cerr << "Error: Could not open the file." << endl;
        exit(1);
    }

    outputFile << content;
    outputFile.close();

    cout << "String has been written to the file '" << fileName << "'." << endl;
}

// Function to perform Caesar cipher-like encryption/decryption
string custom_shift(const string &input, int shift)
{
    string result = input;

    for (char &c : result)
    {
        if (isalpha(c))
        {
            bool isUppercase = isupper(c);
            char base = isUppercase ? 'A' : 'a';
            c = base + ((c - base + shift) + 26) % 26;
        }
    }

    return result;
}

// Function to perform Caesar cipher-like encryption
string custom_encrypt(const string &input, int shift)
{
    string encryptedText = input;

    for (char &c : encryptedText)
    {
        // Check if the character is a letter (uppercase or lowercase)
        if (isalpha(c))
        {
            // Determine whether the letter is uppercase or lowercase
            bool isUppercase = isupper(c);

            // Apply the shift to the letter while wrapping around the alphabet
            char base = isUppercase ? 'A' : 'a';
            c = base + ((c - base + shift) + 26) % 26;
        }
        // If the character is not a letter, leave it unchanged
    }

    return encryptedText;
}

// Function to perform Caesar cipher-like decryption (opposite shift)
string custom_decrypt(const string &input, int shift)
{
    // To decrypt, apply the opposite shift (negative)
    return custom_encrypt(input, -shift);
}

int main()
{
    map<string, User> users; // Map to store user data (username -> User)

    // Read existing user data from file
    readUserDataFromFile(users);

    // Menu
    int choice;
    do
    {
        cout << "1. Register\n2. Login\nChoose an option (0 to exit): ";
        cin >> choice;

        if (choice == 1)
        {
            // Registration
            string username, password;
            cout << "Enter your desired username: ";
            cin >> username;
            cout << "Enter your password: ";
            cin >> password;

            registerUser(users, username, password);
        }
        else if (choice == 2)
        {
            // Login
            string username, password;
            cout << "Enter your username: ";
            cin >> username;
            cout << "Enter your password: ";
            cin >> password;

            if (authenticateUser(users, username, password))
            {
                cout << "Login successful. Welcome, " << username << "!" << endl;

                int innerChoice;
                cout << "Choose an option:\n";
                cout << "**********************\n";
                cout << "1. Secure File\n";
                cout << "**********************\n";
                cout << "2. Decrypt File\n";
                cout << "**********************\n";
                cout << "Enter your choice: ";
                cin >> innerChoice;

                if (innerChoice == 1)
                {
                    int passwordLength = 200;
                    string randomPassword = generateRandomPassword(passwordLength);

                    cout << "Random Password: " << randomPassword << endl;

                    // Text File Generator
                    string fileName = "password.txt";
                    writeToFile(randomPassword, fileName);

                    // Password Encrypt
                    string encryptedPassword = custom_shift(randomPassword, 10);

                    cout << "Original: " << randomPassword << endl;
                    cout << "Encrypted: " << encryptedPassword << endl;

                    // Reading the file format

                    //     void listFiles(const std::string& folderPath) {
                    //     DIR* dir;
                    //     struct dirent* entry;

                    //     if ((dir = opendir(folderPath.c_str())) != nullptr) {
                    //         while ((entry = readdir(dir)) != nullptr) {
                    //             if (entry->d_type == DT_REG) { // Check if it's a regular file
                    //                 std::cout << "File Name: " << entry->d_name << std::endl;
                    //             }
                    //         }
                    //         closedir(dir);
                    //     } else {
                    //         std::cerr << "Error: Unable to open directory." << std::endl;
                    //     }
                    // }

                    // Zipping the file
                    string sourceFile = "Data.txt";
                    string zipFileName = "Protected\\Protected.zip";
                    const char *password = encryptedPassword.c_str();

                    string zipCommand = "7z a -p" + string(password) + " -r \"" + zipFileName + "\" \"" + sourceFile + "\"";
                    int result = system(zipCommand.c_str());

                    if (result == 0)
                    {
                        cout << "ZIP file created successfully." << endl;
                    }
                    else
                    {
                        cerr << "Failed to create ZIP file." << endl;
                    }
                }
                else if (innerChoice == 2)
                {
                    // Define the file name (change this to the path of your text file)
                    string fileName = "password.txt";

                    // Create an input file stream
                    ifstream inputFile(fileName);

                    // Check if the file opened successfully
                    if (!inputFile.is_open())
                    {
                        cerr << "Error: Unable to open file." << endl;
                        return 1; // Return an error code
                    }

                    string line;

                    // Read and print each line of the file
                    while (getline(inputFile, line))
                    {
                        cout << line << endl;
                    }

                    // Close the file
                    inputFile.close();

                    string plaintext = line; // Your text to encrypt
                    int shift = 10;          // Number of positions to shift letters (adjust as needed)

                    // Encrypt the data
                    string encryptedText = custom_encrypt(plaintext, shift);

                    // Decrypt the data
                    string decryptedText = custom_decrypt(encryptedText, shift);

                    cout << "Original: " << plaintext << endl;
                    cout << "Encrypted: " << encryptedText << endl;
                    cout << "Decrypted: " << decryptedText << endl;

                    if (plaintext == decryptedText)
                    {
                        cout << "Successful" << endl;
                    }
                    else
                    {
                        cout << "Error" << endl;
                    }

                    // std::string folderPath = "Test";
                    // listFiles(folderPath);

                    // Specify the ZIP file to unzip and the destination folder
                    const char *zipFileName = "Protected\\Protected.zip"; // ZIP file to unzip
                    const char *destinationFolder = "Unzipped_File_Secure";

                    // Ask the user for the password
                    // cout << "Enter the password for the ZIP file: ";
                    string password = encryptedText;

                    // Construct the command to unzip the file using 7z
                    string command = "7z x -p" + password + " \"" + zipFileName + "\" -o\"" + destinationFolder + "\"";

                    // Use the system function to run the command
                    int result = system(command.c_str());

                    // Check the result of the command execution
                    if (result == 0)
                    {
                        cout << "ZIP file unzipped successfully to folder '" << destinationFolder << "'." << endl;
                    }
                    else
                    {
                        cerr << "Failed to unzip ZIP file." << endl;
                    }
                }
                else
                {
                    cout << "Invalid choice. Exiting." << endl;
                }
            }
            else
            {
                cout << "Login failed. Invalid username or password." << endl;
            }
        }
        else if (choice != 0)
        {
            cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 0);

    return 0;
}
