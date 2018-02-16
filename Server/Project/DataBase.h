#pragma once

#include <vector>
#include <string>
#include "sqlite3.h"
#include <time.h>       
#include <map>

using namespace std;

class DataBase
{
public:
	DataBase(); //C'tor - opening the database
	~DataBase(); //D'tor - closing the database
	

	int getHomeIdByUserId(int userId);

	map<string, int> getShoppingListByHomeId(int homeId);

	string getProductNameById(int productId);

	bool isEmailExists(string email);

	vector<string> getAllUserInHome(int homeId);

	int getHomeIdByHomePass(string homePass);
	
	//****************************************************************************************************************************************//
	bool isUserExists(string username); 
	//This function checks if a specific user exists in the database. 
	//If the user exists the function returns TRUE (else - FALSE).
	//****************************************************************************************************************************************//
	bool addNewUser(string username, string password, string email); 
	//This function adds a new user to the database including his password and email. 
	//In case of success the function returns TRUE, in case of failure the function returns FALSE.
	//****************************************************************************************************************************************//
	bool addNewHome();//decide on password 
	
	bool isProductExists(string barcode);

	bool addProductToShoppingList(int homeId, string barcode);

	string getProductNameByBarcode(string barcode);

	bool addNewProduct(string barcode, string productName); //to the table
	
	bool isUserAndPassMatch(string username, string password); 
	//This function checks if a specific user can sign in (by checking the match between the username and the password). 
	//If the username and the password match, the function returns TRUE (else - FALSE).
	//****************************************************************************************************************************************//
	vector<string> getPersonalData(string username); 
	//This function returns details about a specific user (number of games, number of right answers, number of wrong answers, average time for answer (2 digits after point)). 
	//In case of success the function returns the vector with the presonal status, in case of failure the function returns an empty vector.
	//****************************************************************************************************************************************//
private:

	//****************************************************************************************************************************************//
	int static callbackCount(void* data, int argc, char** argv, char** azCol); 
	//This function returns in the 'void*' parameter a result of a query which returns numbers ('COUNT', 'SUM', 'AVG').
	//****************************************************************************************************************************************//
	int static callbackPersonalData(void* data, int argc, char** argv, char** azCol); 
	//This function returns in the 'void*' parameter a result of a query which returns one string.
	//****************************************************************************************************************************************//

	sqlite3* _db;
};