/** \file bank_functions.cpp
* \brief This file contains the implementations of the bank functions necessary for Bank_App.cpp to run smoothly.
* <BR>
* \author Joseph Uche
* \date 02-03-2023
*/

#include "user.h"

/**
* Function <code>User</code> is a constructor for the class User .It sets all the class variables to an initial value.
*/
User::User() {
	name = "";
	username = "";
	balance = 0;
	password = "";
}

/**
* Function <code>callback</code> is a funtion that is called by the SQlite library whenever information is retrieved from the library
* @param data is a pointer to any additional data that was passed to the `sqlite3_exec()` function when the SQL statement is
* executed
* <BR>
* @param argc is the number of columns in the current row of data being processed
* @param argv is an array of strings that contains the data in the current row being processed each element element of the array
* corresponds to the columns of the row.
* <BR>
* @param colName is an array of strings that contains the names of each columns in the current row being processed
* @return the function returns  0
*/
int callback(void* data, int argc, char** argv, char** colName) {
	int* count = (int*)data;
	(*count)++;
	return 0;
}

/**
* Function <code>deposit</code> adds the given value to the current user balance
* @param amount is a value given by the user that they are willing to add to their balance
* @param db  is a pointer to the database in the main program where all users data is stored.
* @param user is the object that refers to the user that is currently logged into the software
* @return returns new user balance.
*/
double deposit(sqlite3* db, double amount, User& user) {
	double new_bal = user.balance + amount;
	char* error_message = 0;
	int rc;
	char* sql = sqlite3_mprintf("UPDATE USERS SET balance=%f WHERE username='%q';", new_bal, user.username.c_str());
	rc = sqlite3_exec(db, sql, callback, 0, &error_message);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", error_message);
		sqlite3_free(error_message);
		sqlite3_close(db);
	}
	else {
		cout << "Balance updated\n";
	}
	sqlite3_free(sql);
	return new_bal;
}

/**
* Function <code>withdraw</code> removes the given value from the current user balance
* @param amount is a value given by the user that they are willing to remove from their balance
* @param db  is a pointer to the database in the main program where all users data is stored.
* @param user is the object that refers to the user that is currently logged into the software
* @return returns new user balance.
*/
double withdraw(sqlite3* db, double amount, User& user) {
	double new_bal = user.balance - amount;
	char* error_message = 0;
	int rc;
	char* sql = sqlite3_mprintf("UPDATE USERS SET balance=%f WHERE username='%q';", new_bal, user.username.c_str());
	rc = sqlite3_exec(db, sql, callback, 0, &error_message);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", error_message);
		sqlite3_free(error_message);
		sqlite3_close(db);
	}
	else {
		cout << "Balance Updated\n";
	}

	sqlite3_free(sql);
	return new_bal;
}

/**
* Function <code>edit_name</code> changes the users name.
* @param new_name is the new name of the user.
* @param db is a pointer to the database in the main program where all users data is stored.
* @param user is the object that refers to the user that is currently logged into the software
* @return returns the users new name.
*/
string edit_name(sqlite3* db, string new_name, User& user) {
	cout << "Full Name: ";
	getline(cin, new_name);

	char* error_message = 0;
	int rc;
	char* sql = sqlite3_mprintf("UPDATE USERS SET name='%q' WHERE username='%q';", new_name.c_str(), user.username.c_str());
	rc = sqlite3_exec(db, sql, callback, 0, &error_message);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", error_message);
		sqlite3_free(error_message);
		sqlite3_close(db);
	}
	else {
		cout << "Name changed Successfully.\n";
	}
	sqlite3_free(sql);

	return new_name;
}

/**
* Function <code>change_password</code> changes the users password.
* @param new_password is the new password of the user.
* @param db is a pointer to the database in the main program where all users data is stored.
* @param user is the object that refers to the user that is currently logged into the software
* @return returns the users new password.
*/
string change_password(sqlite3* db, string new_password, User& user) {
	string confirm_password;
	cout << "New Password: ";
	getline(cin, new_password);
	cout << "Confirm Password: ";
	getline(cin, confirm_password);
	while (new_password != confirm_password) {
		cout << "Password doesn't match. Try again.\n";
		cout << "New Password: ";
		getline(cin, new_password);
		cout << "Confirm Password: ";
		getline(cin, confirm_password);
	}
	char* error_message = 0;
	int rc;
	char* sql = sqlite3_mprintf("UPDATE USERS SET password='%q' WHERE username='%q';", new_password.c_str(), user.username.c_str());
	rc = sqlite3_exec(db, sql, callback, 0, &error_message);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", error_message);
		sqlite3_free(error_message);
		sqlite3_close(db);
	}
	else {
		cout << "Password changed Successfully.\n";
	}
	sqlite3_free(sql);
	return new_password;
}

/**
* Function <code>change_username</code> changes the users username.
* @param new_username is the new username of the user.
* @param db is a pointer to the database in the main program where all users data is stored.
* @param user is the object that refers to the user that is currently logged into the software
* @return returns the users new username.
*/
string change_username(sqlite3* db, string new_username, User& user) {
	cout << "New username: ";
	getline(cin, new_username);
	cout << "Username changed.\n";
	char* error_message = 0;
	int rc;
	char* sql = sqlite3_mprintf("UPDATE USERS SET username='%q' WHERE username='%q';", new_username.c_str(), user.username.c_str());
	rc = sqlite3_exec(db, sql, callback, 0, &error_message);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", error_message);
		sqlite3_free(error_message);
		sqlite3_close(db);
	}
	else {
		cout << "Username changed Successfully.\n";
	}
	sqlite3_free(sql);
	return new_username;
}

/**
* Function <code>is_user_in_database</code> is used to check if a user in already in the database
* @param db is a pointer argument that refers to the database where all users details are stored
* @param username is the username that will be looked for in the database each one is unique.
* @return returns 0 or less if the user is not in database and 1 if the user is in the database.
*/
int is_user_in_database(sqlite3* db, const char* username) {
	char sql[100];
	snprintf(sql, 100, "SELECT * FROM USERS WHERE username='%s'", username);
	int count = 0;
	int rc = sqlite3_exec(db, sql, callback, &count, NULL);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
		return -1;
	}
	return count>0;
}

/**
* Function <code>read_details</code> reads users deatils and stores them in the class.
* @param db is a pointer argument that refers to the database where all users details are stored
*/
void User::read_details(sqlite3* db) {
	cout << "Full Name: ";
	getline(cin, name);
	cout << "Username: ";
	getline(cin, username);
	const char* username1 = username.c_str();
	int is_in_database = is_user_in_database(db, username1);
	while (is_in_database > 0) {
		cout << "Oops, username already taken.Try another\n";
		cout << "Username: ";
		getline(cin, username);
		username1 = username.c_str();
		is_in_database = is_user_in_database(db, username1);
	}

	string confirm_password;
	cout << "Password:";
	getline(cin, password);
	cout << "Confirm Password: ";
	getline(cin, confirm_password);
	while (password != confirm_password) {
		cout << "Password does not match.\n";
		cout << "Password:";
		getline(cin, password);
		cout << "Confirm Password: ";
		getline(cin, confirm_password);
	}

}

/**
* Function <code>correct_password</code> checks if the password that the user entered is the same as the password on the username from the database
* basically checking if the password is correct.
* <BR>
* @param username is the users username every users username is unique
* @param password is the input from the user as password when the user is logging in.
* @param db is a pointer to the database where all the users information are stored.
* @return returns true if the password is correct and false if not.
*/
bool correct_password(string username, string password, sqlite3* db) {
	string sql = "SELECT password FROM USERS WHERE username = ? AND password = ?";
	sqlite3_stmt* stmt;
	sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
	sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
	int result = sqlite3_step(stmt);

	if (result == SQLITE_ROW) {
		sqlite3_finalize(stmt);
		return true;
	}
	else {
		sqlite3_finalize(stmt);
		return false;
	}
}

/**
* Function <code>print_details</code> helps the user to see their details
* @param db is a pointer to the database where all users information is stored.
* @param username is the username of the user that will be used to search for the users own details.
* @return returns the value for result at the end of the program.
*/
int print_details(sqlite3* db, string username) {
	string sql = "SELECT name,username,password,balance FROM USERS WHERE username = ?";
	sqlite3_stmt* stmt;
	int result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		cout << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
		return result;
	}
	result = sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
	if (result != SQLITE_OK) {
		cout << "Error binding parameter: " << sqlite3_errmsg(db) << endl;
		sqlite3_finalize(stmt);
		return result;
	}
	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW) {
		cout <<"Name: " << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)) << endl;
		cout <<"Username: " << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)) << endl;
		cout <<"Password: " << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)) << endl;
		cout <<"Balance: "<< sqlite3_column_double(stmt, 3) << endl;
	}
	else {
		cout << SQLITE_ROW << endl;
		cout << "User details not found.\n";
	}
	sqlite3_finalize(stmt);
	return result;

}

/**
* Function <code>get_details</code> gets the users details from the database and stores as an object in a class.
* @param db is a pointer to the database where all user information are stored.
* @param username is the username of the user that will be used to search for their deatils in the database
* @param user is an object of the class User where all the details will be stored.
*/
void get_details(sqlite3* db, string username, User& user) {
	string sql = "SELECT name,username,password,balance FROM USERS WHERE username = ?";
	sqlite3_stmt* stmt;
	sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
	sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
	int result = sqlite3_step(stmt);

	if (result == SQLITE_ROW) {
		user.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
		user.username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
		user.password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
		user.balance = sqlite3_column_double(stmt, 3);
	}
	else {
		cout << "User details not found.\n";
	}
	sqlite3_finalize(stmt);
}

/**
* Function <code>save_details</code> is a class function that saves the deatils of the user to the database after they have created an account in the software.
* @param db is pointer to the databse where all users detiailsa re stored.
* @param error_message is apointer that stores all the error messages that are return in function.
* @param rc is an integer variable that is used to store the return values for the all SQL statements execution in the function.
* @return returns 1 if the functio gives an error and zero otherwise.
*/
int User::save_details(sqlite3* db, char* error_message, int& rc) {

	char* sql;
	sql = sqlite3_mprintf("INSERT INTO USERS (name, username, password, balance) VALUES ('%q', '%q', '%q', %f);", name.c_str(), username.c_str(), password.c_str(), balance);
	rc = sqlite3_exec(db, sql, callback, 0, &error_message);
	if (rc != SQLITE_OK) {
		cout << rc << endl;
		fprintf(stderr, "SQL error: %s\n", error_message);
		sqlite3_free(error_message);
		sqlite3_close(db);
		return 1;
	}
	else {
		printf("Records created successfully\n");
	}
	sqlite3_free(sql);
	return 0;
}

/**
* Function <code>delete_user</code> deletes searches for a user in the database and deletes their information
* from it
* <BR>
* @param db is a pointer to the database that was used to store user information.
* @param username is a string that is the user's username that will be used to look for the users information in the database.
* @return returns true if the user was successfully deleted and false if otherwise
*/
bool delete_user(sqlite3* db, string username) {
	string sql = "DELETE FROM USERS WHERE username = ?;";
	sqlite3_stmt* stmt;
	sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
	sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
	int result = sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	if (result == SQLITE_DONE) {
		cout << "Account Deleted.\n";
		return true;
	}
	else {
		cout << "Error occured during deletion.\n";
		return false;
	}
}