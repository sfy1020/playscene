#include "Target.h"
#include "Tower.h"

//Target
void TargetTower::run(cocos2d::Ref* ref){
	Tower* own = dynamic_cast<Tower*>(ref);				//��ü�� ���� casting
	Unit* target = nullptr;

	if (own->get_frame() == 0){							//ù �������� ���
		own->set_state(STATE::TARGET);
	}

	for (auto i : Object_::all){
		if (OBJECT(i.second->get_DB_ID()) == CHARACTER){		//CHARACTER�� ��	
			target = dynamic_cast<Unit*>(i.second);		//��� ���� casting
			if (inRange(own->get_gx(), own->get_gy(), target->get_gx(), target->get_gy(), own->get_range())){	//�������� ������
				own->set_targetID(target->get_id());			//target ����
			}
		}
	}
	own->initMessage(STATE::BASE);
};