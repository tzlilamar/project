#include "DataBase.h"
#include "sqlite3.h"
#include <iostream>

//Includes for the calculation of the average
#include <iomanip> // setprecision
#include <sstream> // stringstream

using namespace std;

DataBase::DataBase() //C'tor
{
	int rc;
	char *zErrMsg = 0;
	bool flag = true;

	try //Opening the database
	{
		rc = sqlite3_open("database.db", &this->_db); //Connection to the database

		if (rc)
		{
			sqlite3_close(this->_db);
		}

	}
	catch (...) //If there is an error
	{
		sqlite3_close(this->_db);
	}
}

DataBase::~DataBase() //D'tor
{
	sqlite3_close(this->_db); //Closing the database
}

bool DataBase::isUserExists(string username)
//This function checks if a specific user exists in the database.
//If the user exists the function returns TRUE (else - FALSE).
{
	char *zErrMsg = 0; 
	int counter = 0; //An integer for keeping the result of the callback function
	string query = "SELECT COUNT(*) FROM t_users where(username == \"" + username + "\");"; //Creating the query for the database
	int rc = sqlite3_exec(this->_db, query.c_str(), DataBase::callbackCount, &counter, &zErrMsg); //Sending the query and calling the callback function

	if (rc != SQLITE_OK) //Checking
	{
		sqlite3_free(zErrMsg);
		throw string("Error: the function 'isUserExists'");
	}
	else
	{
		bool isExists;
		(counter == 1) ? isExists = true : isExists = false; //If counter ==  1 it means that the user exists
		return isExists;
	}
}

bool DataBase::addNewUser(string username, string password, string email)
//This function adds a new user to the database including his password and email
//In case of success the function returns TRUE, in case of failure the function returns FALSE.
{
	if (!this->isUserExists(username)) //If the user exists in the database
	{
		char *zErrMsg = 0;
		string query = "insert into t_users(username, password, email) VALUES(\"" + username + "\", \"" + password + "\" ,\"" + email + "\");"; //Creating the query for the database
		int rc = sqlite3_exec(this->_db, query.c_str(), 0, 0, &zErrMsg);  //Sending the query

		if (rc != SQLITE_OK) //Checking
		{
			sqlite3_free(zErrMsg);
			return false; //In case of failure the function returns FALSE
		}
		return true; //In case of success the function returns TRUE
	}
	return false; //In case of failure the function returns FALSE
}

bool DataBase::isUserAndPassMatch(string username, string password)
//This function checks if a specific user can sign in (by checking the match between the username and the password).
//If the username and the password match the function returns TRUE (else - FALSE).
{
	char *zErrMsg = 0;
	int counter = 0; //An integer for keeping the result of the callback function
	string query = "SELECT COUNT(*) FROM t_users where(username == \"" + username + "\" and password == \"" + password + "\");"; //Creating the query for the database
	int rc = sqlite3_exec(this->_db, query.c_str(), DataBase::callbackCount, &counter, &zErrMsg); //Sending the query and calling the callback function

	if (rc != SQLITE_OK) //Checking
	{
		sqlite3_free(zErrMsg);
		throw string("Error: the function 'isUserAndPassMatch'");
	}
	else
	{
		bool isMatching;
		(counter == 1) ? isMatching = true : isMatching = false; //If counter ==  1 it means that the username and the password match
		return isMatching;
	}
}

vector<string> DataBase::getPersonalData(string username)
//This function returns details about a specific user (number of games, number of right answers, number of wrong answers, average time for answer (2 digits after point)).
//In case of success the function returns the vector with the presonal status, in case of failure the function returns an empty vector.
{
	char *zErrMsg = 0;
	string query = "SELECT COUNT(*) FROM (SELECT username, game_id, COUNT(game_id) FROM t_players_answers WHERE username = \"" + username + "\" GROUP BY game_id);"; //Creating the query for the database
	string numberAsString; //For keeping numbers as strings and push them into the vector of strings
	vector <string> personalStatusVec; //An integer for keeping the result of the function
	int counterCorrectAnswers, counterAllAnswers = 0; //For the calculation of the number of wrong answers
	stringstream stream; //For the calculation of the average time for answer
	float floatNumber; //For the calculation of the average time for answer

	int rc = sqlite3_exec(this->_db, query.c_str(), DataBase::callbackPersonalStatus, &numberAsString, &zErrMsg); //Sending the query and calling the callback function

	if (rc != SQLITE_OK) //Checking
	{
		sqlite3_free(zErrMsg);
		personalStatusVec.clear();
		return personalStatusVec;
	}

	personalStatusVec.push_back(numberAsString); //Push into the vector the number of games of the user
	query = "SELECT SUM(is_correct) FROM t_players_answers WHERE username = \"" + username + "\";"; //Creating the query for the database

	rc = sqlite3_exec(this->_db, query.c_str(), DataBase::callbackCount, &counterCorrectAnswers, &zErrMsg); //Sending the query and calling the callback function
	if (rc != SQLITE_OK) //Checking
	{
		sqlite3_free(zErrMsg);
		personalStatusVec.clear();
		return personalStatusVec;
	}

	personalStatusVec.push_back(to_string(counterCorrectAnswers)); //Push into the vector the number of correct answers of the user

	query = "SELECT COUNT(*) FROM t_players_answers WHERE username = \"" + username + "\";"; //Creating the query for the database

	rc = sqlite3_exec(this->_db, query.c_str(), DataBase::callbackCount, &counterAllAnswers, &zErrMsg); //Sending the query and calling the callback function
	if (rc != SQLITE_OK) //Checking
	{
		sqlite3_free(zErrMsg);
		personalStatusVec.clear();
		return personalStatusVec;
	}

	personalStatusVec.push_back(to_string(counterAllAnswers - counterCorrectAnswers)); //Push into the vector the number of wrong answers of the user

	query = "SELECT AVG(answer_time) FROM t_players_answers WHERE username = \"" + username + "\";"; //Creating the query for the database

	rc = sqlite3_exec(this->_db, query.c_str(), DataBase::callbackPersonalStatus, &numberAsString, &zErrMsg); //Sending the query and calling the callback function
	if (rc != SQLITE_OK) //Checking
	{
		sqlite3_free(zErrMsg);
		personalStatusVec.clear();
		return personalStatusVec;
	}
	if (numberAsString != "")
	{
		floatNumber = stof(numberAsString); //Converting the string to a float number
		stream << fixed << setprecision(2) << floatNumber;	//2 digits after the point
		numberAsString = stream.str(); //Converting the float number (2 digits after the point) to a string
		personalStatusVec.push_back(numberAsString); //Push into the vector the average time for answer of the user

	}
	else
	{
		personalStatusVec.push_back("0"); //Push into the vector the average time for answer of the user
	}
	return personalStatusVec; //Returns the vector of the strings
}

//Callbacks:

int DataBase::callbackCount(void* data, int argc, char** argv, char** azCol)
//This function returns in the 'void*' parameter a result of a query which returns numbers ('COUNT', 'SUM', 'AVG').
{
	if (*argv != NULL)
	{
		*static_cast<int*>(data) = stoi(argv[0]);
		return 0;
	}
	else
	{
		*static_cast<int*>(data) = 0;
	}
	return 0;
}


int DataBase::callbackPersonalData(void* data, int argc, char** argv, char** azCol)
//This function returns in the 'void*' parameter a result of a query which returns one string.
{
	if (*argv != NULL)
	{
		*static_cast<string*>(data) = argv[0];
		return 0;
	}
	else
	{
		*static_cast<string*>(data) = "0";
	}
	return 0;
}
