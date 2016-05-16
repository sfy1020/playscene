#include "Poison.h"
#include "Unit.h"
//constructor
Poison::Poison() :Mesmerize(){
}

Poison::~Poison(){
}

Poison::Poison(const MesmerizeDBdata& data, int id, int gx, int gy, int targetID, int damage, int level)
	:Mesmerize(data, id, gx, gy, targetID, damage, level){
	start();
}

//virtual method
void Poison::start(){
	auto iter = all.find(targetID);

	if (iter == all.end()){												//Target이 없을 때
		//EXCEPTION("Object_ is not in hash (target)");
		Object_::mainQ.push(Message(id, id, CONTROLLER::DELETE));
	}
	else{
		Unit* unit = dynamic_cast<Unit*>(iter->second);
		if (unit->get_mesmerize_state() == MESMERIZE::POISON){
			Object_::mainQ.push(Message(id, id, CONTROLLER::DELETE));
		}else{
			unit->get_sprite()->setColor(cocos2d::Color3B::GREEN);
			unit->set_mesmerize_state(MESMERIZE::POISON);
		}
	}
}

void Poison::finish(){
	auto iter = all.find(targetID);
	if (iter == all.end()){												//Target이 없을 때
		//EXCEPTION("Object_ is not in hash (target)");
	}else{
		Unit* unit = dynamic_cast<Unit*>(iter->second);
		unit->get_sprite()->setColor(cocos2d::Color3B(255,255,255));
		unit->set_mesmerize_state(MESMERIZE::NONE);
	}
	Object_::mainQ.push(Message(id, id, CONTROLLER::DELETE));
}

void Poison::middle(){
	auto iter = all.find(targetID);
	if (iter == all.end()){												//Target이 없을 때
		//EXCEPTION("Object_ is not in hash (target)");
	}
	else{
		Unit* unit = dynamic_cast<Unit*>(iter->second);
		unit->damaged(-1, continue_damage);
	}
}

//own method

//getter&setter
