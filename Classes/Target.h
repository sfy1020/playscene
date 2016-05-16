#ifndef __TARGET_H__
#define __TARGET_H__
#include "State.h"
#include "Object_.h"

//Target
class Target : public State{
public:
	Target(){ state = STATE::TARGET; }
	virtual void run(cocos2d::Ref* ref) = 0;
};

class TargetTower : public Target{
public:
	virtual void run(cocos2d::Ref* ref);
};
#endif