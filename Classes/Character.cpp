#include "Character.h"

//constructor
Character::Character():Unit(),move_frame(0),move_imgID(0),move_soundID(0){}

Character::~Character(){
}

Character::Character(const CharacterDBdata& data, int id, int x, int y, DIRECTION direction, int targetID)
	:Unit(data, id, x, y, direction, targetID){
		this->after_x			=	x;						//º¯¼ö
		this->after_y			=	y;
		
		this->gold				=	data.gold;				//DB
		this->move_frame		=	data.move_frame;	
		this->move_imgID		=	data.move_imgID;
		this->move_soundID		=	data.move_soundID;
		this->sprite->setScale(1.25f);
}

//virtual method
void Character::levelUp(){}

//own method


//getter & setter
const int& Character::get_gold() const{
	return gold;
}
const int& Character::get_move_frame() const{
	return move_frame;
}
const int& Character::get_move_imgID() const{
	return move_imgID;
}
const int& Character::get_move_soundID() const{
	return move_soundID;
}

void Character::set_gold(const int& gold) {
	this->gold = gold;
}
void Character::set_move_frame(const int& move_frame) {
	this->move_frame = move_frame;
}
void Character::set_move_imgID(const int& move_imgID) {
	this->move_imgID = move_imgID;
}
void Character::set_move_soundID(const int& move_soundID) {
	this->move_soundID = move_soundID;
}
