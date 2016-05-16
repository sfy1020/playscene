#include "SkillDirectSplash.h"
#include "Character.h"

//constructor & destructor
SkillDirectSplash::SkillDirectSplash():Skill(){}

SkillDirectSplash::~SkillDirectSplash(){
}

SkillDirectSplash::SkillDirectSplash(const SkillDBdata& data, int id, int gx, int gy, int targetID, int damage, int level)
	:Skill(data, id, gx, gy, targetID, damage, level){

	stateMachine.emplace_back(std::make_shared<AttackSkillSplash>(AttackSkillSplash()));			//interface
	stateMachine.emplace_back(std::make_shared<MoveSkillDirect>(MoveSkillDirect()));

	auto iter = all.find(targetID);								//sprite image setting
	if(iter == all.end()){
		EXCEPTION2("target is not in hash!", targetID);
		Object_::mainQ.push(Message(id,id,CONTROLLER::DELETE));
	}else{
		Unit* target = dynamic_cast<Unit*>(iter->second);

		this->target_x			=	target->get_gx();
		this->target_y			=	target->get_gy();

		float sx = (float)gx;
		float sy = (float)gy;
		float dx = (float)this->target_x;
		float dy = (float)this->target_y;

		float dis = sqrt(distance2D(sx,sy,dx,dy));
		float xflus = (dx-sx)/dis;
		float yflus = (dy-sy)/dis;
		GraphicDBdata gtemp = graphic.get_GraphicDBdata(imgID);
		this->gx = (int)((sx + gtemp.size_x*xflus/2*dis/(float)gtemp.size_x));
		this->gy = (int)((sy + gtemp.size_y*yflus/2*dis/(float)gtemp.size_y));

		if (target->get_state() == STATE::DIE){
			Object_::mainQ.push(Message(id,id,CONTROLLER::DELETE));
		}
		
		this->sprite->setScaleY(std::max(dis/(float)gtemp.size_y,0.35f));
		this->sprite->setPosition(cocos2d::Vec2(this->gx,this->gy));
	}

	sound.run(move_soundID);
}

//virtual method
void SkillDirectSplash::base(){
	if(targetID == 0){
		EXCEPTION("no target");
		return;
	}else{
		auto target = all.find(targetID);
		if(target == all.end()){
			EXCEPTION2("Object_ is not in hash",targetID);
		}
		if(frame == move_frame-1){
			message.push(STATE::ATTACK);
		}else{
			message.push(STATE::MOVE);
		}
	}
}

//own method

//getter & setter
