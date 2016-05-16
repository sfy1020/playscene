#ifndef __CHARARCTERCOMMON_H__
#define __CHARARCTERCOMMON_H__

#include "constant.h"
#include "Unit.h"
#include "Character.h"

class CharacterCommon : public Character{
private:						//value
public:							//constructor & destructor
	CharacterCommon();
	virtual ~CharacterCommon();
	CharacterCommon(const CharacterDBdata& data, int id, int x, int y, DIRECTION direction, int targetID);

public:							//virtual method
	virtual void base();

public:							//own method
};

#endif