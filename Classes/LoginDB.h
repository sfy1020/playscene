#ifndef __LOGINDB_H__
#define __LOGINDB_H__
#pragma once
#include "constant.h"
#include <unordered_map>
#include <string>

class LoginDB{
private:
	std::map<std::string, LoginDBdata*> loginDB;
	LoginDBdata* currentUser;

public:
	LoginDB();
	~LoginDB();
	void loginDB_init();
	void saveDB();
	LoginDBdata* get_User_DBdata(std::string DB_ID, std::string password);
	void set_User_DBdata(std::string DB_ID,int stage);

	std::map<std::string, LoginDBdata*>& get_loginDB();

	void setCurrentUser(LoginDBdata* user);
	LoginDBdata* getCurrentUser();
};
#endif