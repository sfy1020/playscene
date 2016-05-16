#ifndef __GRAPHICCLASS_H__
#define __GRAPHICCLASS_H__

#include <queue>
#include <fstream>
#include <vector>
#include "cocos2d.h"
#include "constant.h"
class GraphicClass{
public:
	GraphicClass();
    ~GraphicClass();
	
	void display(int id, int x, int y, int max_frame, DIRECTION direction, int speed, cocos2d::Sprite* sprite);
    void init();
	GraphicDBdata get_GraphicDBdata(int id);
protected:

private:
	std::map<int,GraphicDBdata> DBdata;	//graphicDBdata Ä³½Ì
};
#endif
