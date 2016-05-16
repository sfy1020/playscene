#ifndef __SKILLSPLASH_H__
#define __SKILLSPLASH_H__

#include "Skill.h"
class SkillSplash : public Skill{
protected:				//value

public:					//constructor & destructor
	SkillSplash();
	virtual ~SkillSplash();
	SkillSplash(const SkillDBdata& data, int id, int gx, int gy, int targetID, int damage, int level);

public:					//virtual method
	virtual void base();

public:					//own method

public:					//getter & setter

};

#endif