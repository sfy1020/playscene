#include "Die.h"
#include "Character.h"
void DieCommon::run(cocos2d::Ref* ref){
	Unit* own = dynamic_cast<Unit*>(ref);		//주체에 대한 casting

	if (own->get_frame() == 0){
		own->set_state(STATE::DIE);
		Object_::graphic.display(own->get_die_imgID(), own->get_gx(), own->get_gy(), own->get_die_frame(), DIRECTION::EMPTY, 16, own->get_sprite());
		Object_::sound.run(own->get_die_soundID());
	}
	
	own->get_sprite()->setColor(cocos2d::Color3B::WHITE);
	own->get_sprite()->setOpacity(128);
	own->set_sleep_time(1);
	if (own->get_frame() == own->get_die_frame() * 16 - 1){		//마지막 프레임일 경우
		own->initMessage(STATE::BASE);
		if(OBJECT(own->get_DB_ID()) == CHARACTER)Object_::mainQ.push(Message(own->get_id(),own->get_id(),CONTROLLER::DELETE));
		else if (OBJECT(own->get_DB_ID()) == TOWER){
			Object_::mainQ.push(Message(own->get_id(), own->get_id(), CONTROLLER::SELLED));
		}
	}else{
		own->initMessage(STATE::DIE);
	}
	own->set_frame((own->get_frame() + 1) % (own->get_die_frame() * 16));
};