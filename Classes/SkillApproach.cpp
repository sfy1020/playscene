#include "SkillApproach.h"
#include "Character.h"

//constructor & destructor
SkillApproach::SkillApproach() :Skill(){}

SkillApproach::~SkillApproach(){
}

SkillApproach::SkillApproach(const SkillDBdata& data, int id, int gx, int gy, int targetID, int damage, int level, int range)
	:Skill(data, id, gx, gy, targetID, damage, level){

	stateMachine.emplace_back(std::make_shared<AttackSkillApproach>(AttackSkillApproach()));		//interface
	stateMachine.emplace_back(std::make_shared<MoveSkillDirect>(MoveSkillDirect()));

	auto iter = all.find(targetID);							//sprite image setting
	if (iter == all.end()){
		EXCEPTION2("target is not in hash!", targetID);
		Object_::mainQ.push(Message(id, id, CONTROLLER::DELETE));
	}
	else{
		Unit* target = dynamic_cast<Unit*>(iter->second);

		this->target_x = target->get_gx();
		this->target_y = target->get_gy();

		GraphicDBdata gtemp = graphic.get_GraphicDBdata(imgID);
		if (target->get_state() == STATE::DIE){
			Object_::mainQ.push(Message(id, id, CONTROLLER::DELETE));
		}
		this->range = range;
		this->sprite->setPosition(cocos2d::Vec2(this->gx, this->gy));
	}
	sound.run(move_soundID);
}

//virtual method
void SkillApproach::base(){
	if (targetID == 0){
		EXCEPTION("no target");
		return;
	}
	else{
		auto target = all.find(targetID);
		if (target == all.end()){
			EXCEPTION2("Object_ is not in hash", targetID);
		}
		if (frame == move_frame - 1){
			message.push(STATE::ATTACK);
		}
		else{
			message.push(STATE::MOVE);
		}
	}
}

//own method


//getter & setter
