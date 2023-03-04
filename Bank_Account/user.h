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
* Structure <code>User</code> will be be used to create objects for every 
* that creates an account with the bank
* <BR>
* @param id is used to store id number of every user
* @param name is used to store the name of the user
* @param username is used to store the username of every user
* @param balance is initially set to zero but can be updated as user deposits and withdraws money
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

// Prototype 

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
