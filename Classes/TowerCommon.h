#ifndef __TOWERCOMMON_H__
#define __TOWERCOMMON_H__

#include "constant.h"
#include "Tower.h"
#include <vector>
#include <utility>

class TowerCommon : public Tower{
public:
protected:					//value

public:						//constructor
	TowerCommon();
	virtual ~TowerCommon();
	TowerCommon(const TowerDBdata& data, int id, int x, int y, int targetID);

public:						//virtual method
	virtual void base();

public:						//own method

public:						//getter & setter

};

#endif