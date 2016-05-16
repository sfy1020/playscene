#ifndef __STUN_H__
#define __STUN_H__

#include "Mesmerize.h"

class Stun : public Mesmerize{
protected:		//value

public:			//constructor & destructor
	Stun();
	virtual ~Stun();
	Stun(const MesmerizeDBdata& data, int id, int gx, int gy, int targetID, int damage, int level);

public:			//virtual method
	virtual void start();
	virtual void finish();
	virtual void middle(){}

public:			//own method

public:			//getter & setter
};

#endif