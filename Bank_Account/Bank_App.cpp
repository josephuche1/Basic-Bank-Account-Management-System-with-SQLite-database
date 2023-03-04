/** \file Bank_App.cpp
* \brief The bank app for user interface.
* \details This is the part of the project that the user will interact with and be able to access the functions in the
* other necessary files
* <BR>
* \author Joseph Uche
* \version 0.1
* \date 02-03-2023
*/
#include "user.h"




int main() {
	sqlite3* database;
	char* error_message = 0;
	int rc;
	const char* sql;
	const char* data = "Callback function called.";

	// open connection to database
	rc = sqlite3_open("Users.db", &database);

	if (rc) {
		cerr << "Can't open database: " << sqlite3_errmsg(database) << endl;
		sqlite3_close(database);
		return 1;
	}
	else {
		cout << "Opened database successfully.\n";
	}

	sql = "CREATE TABLE IF NOT EXISTS USERS(" \
		"name TEXT NOT NULL,"\
		"username TEXT NOT NULL,"\
		"password TEXT NOT NULL,"\
		"balance REAL NOT NULL);";

	rc = sqlite3_exec(database, sql, callback, (void*)data, &error_message);

	if (rc != SQLITE_OK) {
		cerr << "SQL erroe: " << error_message << endl;
		sqlite3_free(error_message);
	}
	else {
		cout << "Database created successfully.\n";
	}

	int option;

	cout << "Welcome to the bank.\n";
	cout << "1. Login\n";
	cout << "2. Create Account\n";
	cout << "3.Exit\n";
	cin >> option;

	while (option != 3) {
		cin.ignore();
		User user;
		double amount;
		string username;
		string password;
		string name;
		if (option == 1) {
			cout << "Username:";
			getline(cin, username);
			const char* userName = username.c_str();
			cout << userName << endl;
			int exist = is_user_in_database(database, userName);
			if (exist <= 0) {
				cout << "User does not exist.\n";
			}
			else {
				cout << "Password:";
				getline(cin, password);
				if (correct_password(username, password, database)) {
					get_details(database, username, user);
					cout << "Welcome back, " << username << endl;
					cout << "1. Deposit\n";
					cout << "2. Withdraw\n";
					cout << "3. Profile\n";
					cout << "4.Back\n";
					cin >> option;
					cin.ignore();
					while (option != 4) {
						if (option == 1) {
							cout << "Amount: ";
							cin >> amount;
							user.balance = deposit(database, amount, user);
						}
						else if (option == 2) {
							cout << "Amount: ";
							cin >> amount;
							while (amount > user.balance) {
								cout << "Insufficient funds\n";
								cout << "Amount: ";
								cin >> amount;
							}
							user.balance = withdraw(database, amount, user);
						}
						else if (option == 3) {
							cout << "1. Check Balance\n";
							cout << "2. See Profile details\n";
							cout << "3. Edit Profile Details\n";
							cout << "4. Back.\n";
							cin >> option;

							while (option != 4) {
								cin.ignore();
								if (option == 1) {
									cout << "Balance: " << user.balance << endl;
								}
								else if (option == 2) {
									print_details(database, user.username);
								}
								else if (option == 3) {
									cout << "1. Change Name\n";
									cout << "2. Change Username\n";
									cout << "3. Change Password\n";
									cout << "4. Back\n";
									cin >> option;

									while (option != 4) {
										cin.ignore();
										if (option == 1) {
											user.name = edit_name(database, name, user);
										}
										else if (option == 2) {
											user.username = change_username(database, username, user);
										}
										else if (option == 3) {
											user.password = change_password(database, password, user);
										}
										else {
											cout << "Invalid Input\n";
										}
										cout << "1. Change Name\n";
										cout << "2. Change Username\n";
										cout << "3. Change Password\n";
										cout << "4. Back\n";
										cin >> option;
									}
								}
								else {
									cout << "Invalid Input\n";
								}
								cout << "1. Check Balance\n";
								cout << "2. See Profile details\n";
								cout << "3. Edit Profile Details\n";
								cout << "4. Back.\n";
								cin >> option;
							}

						}
						else {
							cout << "Invalid Input\n";
						}
						cout << "1. Deposit\n";
						cout << "2. Withdraw\n";
						cout << "3. Profile\n";
						cout << "4.Back\n";
						cin >> option;
					}
				}
			}
		}
		else if (option == 2) {
			user.read_details(database);
			user.save_details(database, error_message, rc);
			cout << "Welcome , " << user.username << endl;
			cout << "1. Deposit\n";
			cout << "2. Withdraw\n";
			cout << "3. Profile\n";
			cout << "4.Back\n";
			cin >> option;
			while (option != 4) {
				if (option == 1) {
					cout << "Amount: ";
					cin >> amount;
					user.balance = deposit(database, amount, user);
				}
				else if (option == 2) {
					cout << "Amount: ";
					cin >> amount;
					while (amount > user.balance) {
						cout << "Insufficient funds\n";
						cout << "Amount: ";
						cin >> amount;
					}
					user.balance = withdraw(database, amount, user);
				}
				else if (option == 3) {
					cout << "1. Check Balance\n";
					cout << "2. See Profile details\n";
					cout << "3. Edit Profile Details\n";
					cout << "4. Back.\n";
					cin >> option;
					while (option != 4) {
						if (option == 1) {
							cout << "Balance: " << user.balance << endl;
						}
						else if (option == 2) {
							print_details(database, user.username);
						}
						else if (option == 3) {
							cout << "1. Change Name\n";
							cout << "2. Change Username\n";
							cout << "3. Change Password\n";
							cout << "4. Back\n";
							cin >> option;
							while (option != 4) {
								if (option == 1) {
									user.name = edit_name(database, name, user);
								}
								else if (option == 2) {
									user.username = change_username(database, username, user);
								}
								else if (option == 3) {
									user.password = change_password(database, password, user);
								}
								else {
									cout << "Invalid Input\n";
								}
								cout << "1. Change Name\n";
								cout << "2. Change Username\n";
								cout << "3. Change Password\n";
								cout << "4. Back\n";
								cin >> option;
							}
						}
						else {
							cout << "Invalid Input\n";
						}
						cout << "1. Check Balance\n";
						cout << "2. See Profile details\n";
						cout << "3. Edit Profile Details\n";
						cout << "4. Back.\n";
						cin >> option;
					}

				}
				else {
					cout << "Invalid Input\n";
				}
				cout << "1. Deposit\n";
				cout << "2. Withdraw\n";
				cout << "3. Profile\n";
				cout << "4.Back\n";
				cin >> option;
			}
		}
		else {
			cout << "Invalid Input\n";
		}
		cout << "1. Login\n";
		cout << "2. Create Account\n";
		cout << "3.Exit\n";
		cin >> option;
	}

	sqlite3_close(database);
}