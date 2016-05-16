#include "DamagedEffect.h"
#include "Character.h"

//constructor & destructor
DamagedEffect::DamagedEffect():Skill(){
}

DamagedEffect::~DamagedEffect(){
}

DamagedEffect::DamagedEffect(const SkillDBdata& data, int id, int gx, int gy, int targetID, int damage, int level)
	:Skill(data, id, gx, gy, targetID, damage, level){
	stateMachine.emplace_back(std::make_shared<MoveDamagedEffect>(MoveDamagedEffect()));		//interface
	sound.run(move_soundID);
}

//virtual method
void DamagedEffect::base(){
	message.push(STATE::MOVE);
}


//own method

