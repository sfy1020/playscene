#ifndef __DBCLASS_H__
#define __DBCLASS_H__
#include "constant.h"
#include "LoginDB.h"
class DBClass{
private:
	std::map<int, ObjectDBdata*> objectDB;		//��� object�� DB data
	LoginDB loginDB;								//������� DB data

public:			//constructor & destructor
	DBClass();
	~DBClass();

public:			//own method
	void characterDB_init();
	void towerDB_init();
	void skillDB_init();
	void mapDB_init();
	void structureDB_init();
	LoginDB& get_LoginDB();
	ObjectDBdata* get_Object_DBdata(int DB_ID);
};
#endif