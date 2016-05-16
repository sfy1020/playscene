#include <vector>
#include "GraphicClass.h"
#include "Object_.h"

USING_NS_CC;

GraphicClass::GraphicClass(){
}

GraphicClass::~GraphicClass(){
}


void GraphicClass::display(int id, int x, int y, int max_frame, DIRECTION direction, int speed, Sprite* sprite){
	auto Find = DBdata.find(id);
	if (Find == DBdata.end()){
		EXCEPTION2("GraphicDBdata is not in hash", id);
		return;
	}
	int size_x = (int)(Find->second.size_x);
	int size_y = (int)(Find->second.size_y);
	std::string filename = Find->second.filename;

	Animation* animation = Animation::create();
	animation->setDelayPerUnit(SCHEDULE_TIME*1.5f*((float)speed));
	
	for (int i = 0; i < max_frame * speed; i++){
		animation->addSpriteFrameWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(filename), Rect(size_x*(i%max_frame), size_y * (int)direction, size_x, size_y));
	}
	
	Animate* animate = Animate::create(animation);
	sprite->stopAllActions();
	sprite->runAction(animate);
}


void GraphicClass::init(){
	std::ifstream graphicDB;
	int id;
	std::string filename;
	std::string type;
	float size_x,size_y,angle;

	std::vector<char*> arr;
	graphicDB.open("graphicData\\graphicDB.txt");

	std::getline(graphicDB, filename);
	while(!graphicDB.eof()){
		graphicDB>>id>>filename>>size_x>>size_y>>angle;
		if(graphicDB.eof())break;
		filename = "graphicData\\"+filename+".png";
		
		DBdata.emplace(id, GraphicDBdata(id, filename, size_x, size_y, angle));
		Director::getInstance()->getTextureCache()->addImage(filename.c_str());
	}
	graphicDB.close();
}

GraphicDBdata GraphicClass::get_GraphicDBdata(int id){
	auto Find = DBdata.find(id);
	if(Find == DBdata.end()){
		EXCEPTION2("GraphicDBdata is not in hash",id);
		return GraphicDBdata();
	}

	return Find->second;
}
