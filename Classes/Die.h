#ifndef __DIE_H__
#define __DIE_H__
#include "State.h"
#include "Object_.h"

//Die
class Die : public State{
public:
	Die(){ state = STATE::DIE; }
	virtual void run(cocos2d::Ref* ref) = 0;
};

class DieCommon : public Die{
public:
	virtual void run(cocos2d::Ref* ref);
};

#endif