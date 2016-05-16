#include "Tower.h"

//constructor & destructor
Tower::Tower() :Unit(), attackID(0), skillID(0){
	board[y][x] = -id;
}

Tower::~Tower(){
	board[y][x] = BIG_INT; 
}

Tower::Tower(const TowerDBdata& data, int id, int x, int y, int targetID)
	:Unit(data, id, x, y, DIRECTION::EMPTY, targetID){
	this->cost			=	data.cost;
	this->attackID		=	data.attackID;
	this->skillID		=	data.skillID;
	board[y][x]			=	-id;		//자리차지
	sprite->setAnchorPoint(cocos2d::Vec2(0.5f,0.25f));		//sprite image setting
}

//virtual method

void Tower::levelUp(){
	if (level > MAX_LEVEL)return;
	this->level++;
	this->cost   += this->cost		/ 2;
	this->damage += this->damage	/ 10;
	this->range  += this->range		/ 10;
	this->speed  -= this->speed		/ 10;
	this->sprite->setScale(this->sprite->getScale()+0.05);
	Object_::mainQ.push(Message(-1,id,CONTROLLER::TOWER_LEVELUP));
}
//own method

//getter & setter
const int& Tower::get_cost() const{
	return cost;
}
const int& Tower::get_attackID() const{
	return attackID;
}
const int& Tower::get_skillID() const{
	return skillID;
}
void Tower::set_cost(const int& cost){
	this->cost = cost;
}
void Tower::set_attackID(const int& attackID){
	this->attackID = attackID;
}
void Tower::set_skillID(const int& skillID){
	this->skillID = skillID;
}