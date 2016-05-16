#include "StructureCommon.h"

//constructor & destructor
StructureCommon::StructureCommon():Structure(){
	board[y][x] = -id;		//자리차지
}

StructureCommon::~StructureCommon(){
}

StructureCommon::StructureCommon(const StructureDBdata& data, int id, int x, int y):Structure(data,id,x,y){
	board[y][x] = -id;		//자리차지
	sprite->setAnchorPoint(cocos2d::Vec2(0.5f, 0.25f));
}

//virtual method
void StructureCommon::base(){}




