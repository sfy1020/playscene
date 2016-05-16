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
	if(iter == all.end()){										//target�� hash�� ���� ��
		//EXCEPTION("Object_ is not in hash (TowerCommon)");
		message.push(STATE::TARGET);
	}else{
		Unit* target = dynamic_cast<Unit*>(iter->second);
		if (target->get_state() != STATE::DIE){						//target�� ������� ��
			if(inRange(gx,gy,target->get_gx(),target->get_gy(),range)){			//���� ���� ���� ��
				message.push(STATE::ATTACK);
			}else{																//���� �ۿ� ���� ��
				targetID = 0;
				message.push(STATE::BASE);
			}
		}else{														//target�� �׾��� ��
			targetID = 0;
			message.push(STATE::BASE);
		}
	}
}

//own method

