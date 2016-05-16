#ifndef __STRUCTURE_H__
#define __STRUCTURE_H__

#include "constant.h"
#include "Object_.h"
#include "Interface.h"

class Structure : public Object_{
protected:		//value
	int x,y;					//변수

	int gx,gy;					//변수(내부)

public:		//constructor & destructor
	Structure();
	virtual ~Structure();
	Structure(const StructureDBdata& data, int id, int x, int y);

public:		//virtual method
	virtual void base() = 0;
	virtual bool skipTimeSlice();

public:		//own method

public:		//getter & setter
	const int& get_x() const;
	const int& get_y() const;
	const int& get_gx() const;
	const int& get_gy() const;

	void set_x(const int& x);
	void set_y(const int& y);
	void set_gx(const int& gx);
	void set_gy(const int& gy);
};

#endif