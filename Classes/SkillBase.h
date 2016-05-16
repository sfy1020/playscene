#ifndef __SKILLBASE_H__
#define __SKILLBASE_H__

#include "Skill.h"
class SkillBase : public Skill{
protected:				//value

public:					//constructor & destructor
	SkillBase();
	virtual ~SkillBase();
	SkillBase(const SkillDBdata& data, int id, int gx, int gy, int targetID, int damage, int level);

public:					//virtual method
	virtual void base();

public:					//own method

public:					//getter & setter

};

#endif