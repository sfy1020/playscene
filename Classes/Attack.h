#ifndef __ATTACK_H__
#define __ATTACK_H__
#include "State.h"
#include "Object_.h"
//Attack
class Attack : public State{
public:
	Attack(){ state = STATE::ATTACK; }
	virtual void run(cocos2d::Ref* ref) = 0;
};

//AttackTower
class AttackTower : public Attack{
public:
	virtual void run(cocos2d::Ref* ref);
};

//AttackSkill
class AttackSkill : public Attack{
public:
	virtual void run(cocos2d::Ref* ref);
};

//AttackSkillSplash
class AttackSkillSplash : public Attack{
public:
	virtual void run(cocos2d::Ref* ref);
};

//AttackSkillApproach
class AttackSkillApproach : public Attack{
public:
	virtual void run(cocos2d::Ref* ref);
};
#endif