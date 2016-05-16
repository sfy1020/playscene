#ifndef __STATE_H__
#define __STATE_H__
#include "constant.h"
#include "cocos2d.h"
class State{
protected:
	STATE state;
public:
	virtual void run(cocos2d::Ref* ref)		=	0;
	
	//getter & setter
	const STATE& get_state() const{
		return this->state;
	}
	void set_state(const STATE& state){
		this->state = state;
	}
};
#endif
