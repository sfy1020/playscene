#ifndef __SLOW_H__
#define __SLOW_H__

#include "Mesmerize.h"

class Slow : public Mesmerize{
protected:		//value

public:			//constructor & destructor
	Slow();
	virtual ~Slow();
	Slow(const MesmerizeDBdata& data, int id, int gx, int gy, int targetID, int damage, int level);

public:			//virtual method
	virtual void start();
	virtual void finish();
	virtual void middle(){}

public:			//own method

public:			//getter & setter

};

#endif