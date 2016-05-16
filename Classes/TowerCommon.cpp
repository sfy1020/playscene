#include "TowerCommon.h"

//constructor & destructor
TowerCommon::TowerCommon():Tower(){}

TowerCommon::~TowerCommon(){
}

TowerCommon::TowerCommon(const TowerDBdata& data, int id, int x, int y, int targetID)
	:Tower(data, id, x, y, targetID){

	stateMachine.emplace_back(std::make_shared<AttackTower>(AttackTower()));		//interface
	stateMachine.emplace_back(std::make_shared<TargetTower>(TargetTower()));

}

//virtual method
void TowerCommon::base(){
	auto iter = all.find(targetID);
	if(iter == all.end()){										//target이 hash에 없을 때
		//EXCEPTION("Object_ is not in hash (TowerCommon)");
		message.push(STATE::TARGET);
	}else{
		Unit* target = dynamic_cast<Unit*>(iter->second);
		if (target->get_state() != STATE::DIE){						//target이 살아있을 때
			if(inRange(gx,gy,target->get_gx(),target->get_gy(),range)){			//범위 내에 있을 때
				message.push(STATE::ATTACK);
			}else{																//범위 밖에 있을 때
				targetID = 0;
				message.push(STATE::BASE);
			}
		}else{														//target이 죽었을 때
			targetID = 0;
			message.push(STATE::BASE);
		}
	}
}

//own method

