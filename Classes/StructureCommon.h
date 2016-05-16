#ifndef __STRUCTURECOMMON_H__
#define __STRUCTURECOMMON_H__

#include "constant.h"
#include "Unit.h"
#include "Structure.h"

class StructureCommon : public Structure{
private:						//value
public:							//constructor & destructor
	StructureCommon();
	virtual ~StructureCommon();
	StructureCommon(const StructureDBdata& data, int id, int x, int y);

public:							//virtual method
	virtual void base();

public:							//own method
};

#endif