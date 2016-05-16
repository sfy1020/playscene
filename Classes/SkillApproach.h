#ifndef __SKILLAPPROACH_H__
#define __SKILLAPPROACH_H__

#include "Skill.h"
class SkillApproach : public Skill{
protected:				//value

public:					//constructor & destructor
	SkillApproach();
	virtual ~SkillApproach();
	SkillApproach(const SkillDBdata& data, int id, int gx, int gy, int targetID, int damage, int level, int range);

public:					//virtual method
	virtual void base();

public:					//own method

public:					//getter & setter

};

#endif