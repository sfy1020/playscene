#ifndef __MAP_H__
#define __MAP_H__

#include "constant.h"
#include "Object_.h"
#include "Interface.h"
#include "cocos2d.h"
#include <vector>

class Map_ : public Object_{
protected:		//value
	int bgmID;
	std::vector<cocos2d::Sprite*> tile;
public:			//constructor & destructor
	Map_();
	virtual ~Map_();
	Map_(const MapDBdata& data, int id);

public:			//virtual method
	virtual void base();
	virtual bool skipTimeSlice();

public:			//own method

public:			//getter & setter
	const int& get_bgmID() const;

	void set_bgmID(const int& bgmID);
};

#endif