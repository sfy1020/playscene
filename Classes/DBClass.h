#ifndef __DBCLASS_H__
#define __DBCLASS_H__
#include "constant.h"
#include "LoginDB.h"
class DBClass{
private:
	std::map<int, ObjectDBdata*> objectDB;		//모든 object의 DB data
	LoginDB loginDB;								//사용자의 DB data

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