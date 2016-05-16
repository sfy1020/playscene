#include "CharacterCommon.h"
#include "Structure.h"

//constructor & destructor
CharacterCommon::CharacterCommon():Character(){}

CharacterCommon::~CharacterCommon(){
}

CharacterCommon::CharacterCommon(const CharacterDBdata& data, int id, int x, int y, DIRECTION direction, int targetID)
	:Character(data, id, x, y, direction, targetID){

	stateMachine.emplace_back(std::make_shared<MoveCharacterNoneSpace>(MoveCharacterNoneSpace()));		//interface
}

//virtual method
void CharacterCommon::base(){
	if(targetID == 0){			//target이 없을 때
		message.push(STATE::TARGET);	//target을 만든다.

	}else{						//target이 있을 때
		auto target = all.find(targetID);
		if(target == all.end()){
			EXCEPTION2("Object_ is not in hash",targetID);
			return;
		}
		Structure* tempUnit = dynamic_cast<Structure*>(target->second);
		if(inRange(gx,gy,tempUnit->get_gx(),tempUnit->get_gy(),range)){			//범위 내에 있을 때
			message.push(STATE::ATTACK);
		}else{																//범위 밖에 있을 때
			message.push(STATE::MOVE);
		}
	}
}

//own method