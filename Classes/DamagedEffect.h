#ifndef __DAMAGEDEFFECT_H__
#define __DAMAGEDEFFECT_H__

#include "constant.h"
#include "Skill.h"
#include "Interface.h"
class DamagedEffect : public Skill{	
protected:		//value
	
public:			//constructor & destructor
	DamagedEffect();
	 virtual~DamagedEffect();
	 DamagedEffect(const SkillDBdata& data, int id, int gx, int gy, int targetID, int damage, int level);

public:			//virtual method
	virtual void base();

public:			//own method

public:			//getter & setter
	
};

#endif