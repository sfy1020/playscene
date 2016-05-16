#include "Map_.h"

//constructor & destructor
Map_::Map_():Object_(){}

Map_::~Map_(){
}

Map_::Map_(const MapDBdata& data, int id):Object_(data, id){
	GraphicDBdata gtemp =	graphic.get_GraphicDBdata(data.imgID);
	this->bgmID			=	data.bgmID;
	this->sprite = cocos2d::Sprite::create();
	this->sprite->setTag(id);
	this->sprite->setAnchorPoint(cocos2d::Vec2(0,0));

	for(int i=0; i<BOARD_Y; i++){
		for(int j=0; j<BOARD_X; j++){
			if (data.road_board[i][j] <= 0)
				gtemp = graphic.get_GraphicDBdata(-data.road_board[i][j]);
			else
				gtemp = graphic.get_GraphicDBdata(data.road_board[i][j]);

			cocos2d::Sprite* stemp = cocos2d::Sprite::create(gtemp.filename,cocos2d::Rect(0, 0, gtemp.size_x, gtemp.size_y));
			stemp->setPosition(cocos2d::Vec2(j*SIZE_OF_BOARD_CELL_X, i*SIZE_OF_BOARD_CELL_Y));
			this->tile.push_back(stemp);
			this->sprite->addChild(stemp);
		}
	}
	objectLayer->addChild(this->sprite);
}

//virtual method
bool Map_::skipTimeSlice(){
	return true;
}

void Map_::base(){
	Object_::sound.run(bgmID);
}

//own method

//getter & setter

const int& Map_::get_bgmID() const{
	return bgmID;
}

void Map_::set_bgmID(const int& bgmID){
	this->bgmID = bgmID;
}

