#ifndef __POISON_H__
#define __POISON_H__

#include "Mesmerize.h"

class Poison : public Mesmerize{
protected:		//value

public:		//constructor
	Poison();
	virtual ~Poison();
	Poison(const MesmerizeDBdata& data, int id, int gx, int gy, int targetID, int damage, int level);

public:		//virtual method
	virtual void start();
	virtual void finish();
	virtual void middle();

public:		//own method

public:		//getter & setter
};

#endif