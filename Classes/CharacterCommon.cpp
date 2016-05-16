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
	if(targetID == 0){			//target�� ���� ��
		message.push(STATE::TARGET);	//target�� �����.

	}else{						//target�� ���� ��
		auto target = all.find(targetID);
		if(target == all.end()){
			EXCEPTION2("Object_ is not in hash",targetID);
			return;
		}
		Structure* tempUnit = dynamic_cast<Structure*>(target->second);
		if(inRange(gx,gy,tempUnit->get_gx(),tempUnit->get_gy(),range)){			//���� ���� ���� ��
			message.push(STATE::ATTACK);
		}else{																//���� �ۿ� ���� ��
			message.push(STATE::MOVE);
		}
	}
}

//own method