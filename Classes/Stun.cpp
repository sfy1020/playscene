#include "Stun.h"
#include "Unit.h"

//constructor & destructor
Stun::Stun() :Mesmerize(){
}

Stun::~Stun(){
}

Stun::Stun(const MesmerizeDBdata& data, int id, int gx, int gy, int targetID, int damage, int level)
	:Mesmerize(data, id, gx, gy, targetID, damage, level){
	start();
}

//virtual method
void Stun::start(){
	auto iter = all.find(targetID);

	if (iter == all.end()){												//Target이 없을 때
		//EXCEPTION("Object_ is not in hash (target)");
		Object_::mainQ.push(Message(id, id, CONTROLLER::DELETE));
	}
	else{
		Unit* unit = dynamic_cast<Unit*>(iter->second);
		if (unit->get_mesmerize_state() == MESMERIZE::STUN){
			Object_::mainQ.push(Message(id, id, CONTROLLER::DELETE));
		}
		else{
			unit_color = unit->get_sprite()->getColor();
			unit->get_sprite()->setColor(cocos2d::Color3B::BLACK);
			unit->set_sleep_time(speed_control);
			unit->set_mesmerize_state(MESMERIZE::SLOW);
		}
	}
}

void Stun::finish(){
	auto iter = all.find(targetID);
	if (iter == all.end()){												//Target이 없을 때
		//EXCEPTION("Object_ is not in hash (target)");
	}
	else{
		Unit* unit = dynamic_cast<Unit*>(iter->second);
		unit->get_sprite()->setColor(cocos2d::Color3B(255, 255, 255));
		unit->set_sleep_time(1);
		unit->set_mesmerize_state(MESMERIZE::NONE);
	}
	Object_::mainQ.push(Message(id, id, CONTROLLER::DELETE));
}

//own method

//getter&setter
