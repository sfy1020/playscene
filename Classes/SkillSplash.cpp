#include "SkillSplash.h"
#include "Character.h"

//constructor & destructor
SkillSplash::SkillSplash():Skill(){}

SkillSplash::~SkillSplash(){
}

SkillSplash::SkillSplash(const SkillDBdata& data, int id, int gx, int gy, int targetID, int damage, int level)
	:Skill(data, id, gx, gy, targetID, damage, level){

	stateMachine.emplace_back(std::make_shared<AttackSkillSplash>(AttackSkillSplash()));		//interface
	stateMachine.emplace_back(std::make_shared<MoveSkill>(MoveSkill()));
	sound.run(move_soundID);
}

//virtual method
void SkillSplash::base(){
	if(targetID == 0){
		EXCEPTION("no target");
		return;
	}else{
		auto target = all.find(targetID);
		if(target == all.end()){
			EXCEPTION2("Object_ is not in hash", targetID);
		}

		if(inRange(gx,gy,target_x,target_y,10)){		//범위 내부
			message.push(STATE::ATTACK);
		}else{															//범위 외부
			message.push(STATE::MOVE);
		}
	}
}

//own method


//getter & setter
