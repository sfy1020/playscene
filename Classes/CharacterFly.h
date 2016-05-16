#ifndef __CHARARCTERFLY_H__
#define __CHARARCTERFLY_H__

#include "constant.h"
#include "Unit.h"
#include "Character.h"

class CharacterFly : public Character{
private:						//value
public:							//constructor & destructor
	CharacterFly();
	virtual ~CharacterFly();
	CharacterFly(const CharacterDBdata& data, int id, int x, int y, DIRECTION direction, int targetID);

public:							//virtual method
	virtual void base();

public:							//own method
};

#endif