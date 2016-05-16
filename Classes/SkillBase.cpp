#include "SkillBase.h"
#include "Character.h"

//constructor & destructor
SkillBase::SkillBase():Skill(){}

SkillBase::~SkillBase(){
}

SkillBase::SkillBase(const SkillDBdata& data, int id, int gx, int gy, int targetID, int damage, int level)
	:Skill(data, id, gx, gy, targetID, damage, level){

	stateMachine.emplace_back(std::make_shared<AttackSkill>(AttackSkill()));			//interface
	stateMachine.emplace_back(std::make_shared<MoveSkill>(MoveSkill()));

	sound.run(move_soundID);
}

//virtual method
void SkillBase::base(){
	message.push(STATE::MOVE);
}

//own method

//getter & setter
