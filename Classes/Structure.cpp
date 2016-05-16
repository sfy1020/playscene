#include "Structure.h"

//constructor & destructor
Structure::Structure():Object_(),x(0),y(0),gx(0),gy(0){}

Structure::~Structure(){
}

Structure::Structure(const StructureDBdata& data, int id, int x, int y):Object_(data, id){
	this->x					=	x;						//변수
	this->y					=	y;

	this->gx				=	x*SIZE_OF_BOARD_CELL_X;	//변수(내부)
	this->gy				=	y*SIZE_OF_BOARD_CELL_Y;

	GraphicDBdata gtemp = graphic.get_GraphicDBdata(imgID);
	this->sprite			=	cocos2d::Sprite::create(gtemp.filename,cocos2d::Rect(0, 0, gtemp.size_x, gtemp.size_y));
	this->sprite->setTag(id);
	this->sprite->setPosition(cocos2d::Vec2(gx,gy));
	this->sprite->setLocalZOrder(BIG_INT - gy);
	objectLayer->addChild(this->sprite);
}

//virtual method

bool Structure::skipTimeSlice(){
	return true;
}

//own method

//getter & setter
const int& Structure::get_x() const{
	return x;
}
const int& Structure::get_y() const{
	return y;
}
const int& Structure::get_gx() const{
	return gx;
}
const int& Structure::get_gy() const{
	return gy;
}


void Structure::set_x(const int& x) {
	this->x = x;
}
void Structure::set_y(const int& y) {
	this->y = y;
}
void Structure::set_gx(const int& gx) {
	this->gx = gx;
}
void Structure::set_gy(const int& gy) {
	this->gy = gy;
}


