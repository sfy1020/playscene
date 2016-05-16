#ifndef __SKILLDIRECTSPLASH_H__
#define __SKILLDIRECTSPLASH_H__

#include "Skill.h"
class SkillDirectSplash : public Skill{
protected:				//value

public:					//constructor & destructor
	SkillDirectSplash();
	virtual ~SkillDirectSplash();
	SkillDirectSplash(const SkillDBdata& data, int id, int gx, int gy, int targetID, int damage, int level);

public:					//virtual method
	virtual void base();

public:					//own method

public:					//getter & setter

};

#endif