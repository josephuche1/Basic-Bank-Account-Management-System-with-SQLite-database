/** \file user.h
* \brief contains User structure to store user information
* \details This file contains all the necessary function prototypes for aall the 
* functions needed for the bank Account project
* <BR>
* \author Joseph Uche
* \date 02-03-2023 
*/
#include <winsqlite/winsqlite3.h>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

/**
* Class <code>User</code> will be be used to create objects for every user
* that creates an account with the software
* <BR>
* @param name is used to store the name of the user
* @param username is used to store the username of every user each users username is unique
* @param balance is used to store the current balance of the user in the software
* @param password is used to store the password of each user
*/
class User {
public:
	User();
	string name;
	string username;
	double balance;
	string password;
	
	void read_details(sqlite3* db);
	int save_details(sqlite3* db, char* error_message, int& rc);
};

// Prototype Functions

int callback(void* data, int argc, char** argv, char** colName);
double deposit(sqlite3* db, double amount, User& user);
double withdraw(sqlite3* db, double amount,User& user);
string edit_name(sqlite3* db,string new_name,User& user);
string change_password(sqlite3* db,string new_password,User& user);
string change_username(sqlite3* db,string new_username,User& user);
int is_user_in_database(sqlite3* db,  const char* username);
bool correct_password(string username, string password, sqlite3* db);
int print_details(sqlite3* db, string username);
void get_details(sqlite3* db, string username,User& user);
bool delete_user(sqlite3* db, string username);
