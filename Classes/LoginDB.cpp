#include "LoginDB.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

LoginDB::LoginDB(){
	loginDB_init();
	
}
LoginDB::~LoginDB(){
	for (auto e:loginDB){
		delete (e.second);
	}
}

void LoginDB::loginDB_init(){
	std::ifstream loginDBtxt("loginDB.txt");
	std::string str;
	
	std::string DB_ID;
	std::string password;
	int stage;

	std::getline(loginDBtxt,str);	//¸Ç À­ÁÙ Á¦°Å
	while (!loginDBtxt.eof()){
		loginDBtxt>>DB_ID;		
		if (loginDBtxt.eof())break;
		loginDBtxt>>password>>stage;
		loginDB.emplace(DB_ID,new LoginDBdata(DB_ID,password,stage));
		
	}
	loginDBtxt.close();
	
}

void LoginDB::saveDB(){
	std::ofstream loginDBtxt("loginDB.txt");

	loginDBtxt<<"DB_ID(name)"<<"\t"<<"password"<<"\t"<<"stage"<<std::endl;
	for (auto e:loginDB){
		loginDBtxt<<e.second->DB_ID<<"\t\t\t"<<e.second->password<<"\t\t\t"<<e.second->stage<<std::endl;
	}

	loginDBtxt.close();
}

LoginDBdata* LoginDB::get_User_DBdata(std::string DB_ID,std::string password){
	auto iter = loginDB.find(DB_ID);

	if (iter==loginDB.end()){
		std::cout<<"-----------in------------"<<std::endl;
		auto temp = new LoginDBdata(DB_ID, password, 1);
		loginDB.insert(std::unordered_map<std::string, LoginDBdata*> ::value_type(DB_ID, temp));
		LoginDB::saveDB();
		return temp;
	}
	else if (iter->second->password!=password)
	{
		std::cout<<"-----------in3------------"<<std::endl;
		return nullptr;
	}	
	else{
		std::cout<<"-----------in2------------"<<std::endl;
		return iter->second;
	}
}
void LoginDB::set_User_DBdata(std::string DB_ID,int stage){

	auto iter = loginDB.find(DB_ID);	
	iter->second->stage = stage;

	return;
}



std::map<std::string, LoginDBdata*>& LoginDB::get_loginDB(){
	return this->loginDB;
}


void LoginDB::setCurrentUser(LoginDBdata* user){
	currentUser = user;
}

LoginDBdata* LoginDB::getCurrentUser(){
	
	return currentUser;
}