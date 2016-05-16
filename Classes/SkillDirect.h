#ifndef __SKILLDIRECT_H__
#define __SKILLDIRECT_H__

#include "Skill.h"
class SkillDirect : public Skill{
protected:				//value

public:					//constructor & destructor
	SkillDirect();
	virtual ~SkillDirect();
	SkillDirect(const SkillDBdata& data, int id, int gx, int gy, int targetID, int damage, int level);

public:					//virtual method
	virtual void base();

public:					//own method

public:					//getter & setter

};

#endif