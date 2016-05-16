#include "Target.h"
#include "Tower.h"

//Target
void TargetTower::run(cocos2d::Ref* ref){
	Tower* own = dynamic_cast<Tower*>(ref);				//주체에 대한 casting
	Unit* target = nullptr;

	if (own->get_frame() == 0){							//첫 프레임일 경우
		own->set_state(STATE::TARGET);
	}

	for (auto i : Object_::all){
		if (OBJECT(i.second->get_DB_ID()) == CHARACTER){		//CHARACTER일 때	
			target = dynamic_cast<Unit*>(i.second);		//대상에 대한 casting
			if (inRange(own->get_gx(), own->get_gy(), target->get_gx(), target->get_gy(), own->get_range())){	//범위내에 있으면
				own->set_targetID(target->get_id());			//target 설정
			}
		}
	}
	own->initMessage(STATE::BASE);
};