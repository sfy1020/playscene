#ifndef __TOWER_H__
#define __TOWER_H__

#include "constant.h"
#include "Unit.h"
#include <vector>
#include <utility>

class Tower : public Unit{
public:
protected:					//value
	int cost;				//DB
	int attackID;
	int skillID;
public:						//constructor
	Tower();
	virtual ~Tower();
	Tower(const TowerDBdata& data, int id, int x, int y, int targetID);

public:						//virtual method
	virtual void base()					=	0;
	virtual void levelUp();

public:						//own method

public:						//getter & setter
	const int& get_cost() const;
	const int& get_attackID() const;
	const int& get_skillID() const;
	void set_cost(const int& cost);
	void set_attackID(const int& attackID);
	void set_skillID(const int& skillID);
};

#endif