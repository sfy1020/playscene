#include "Move.h"
#include "Character.h"
#include "SkillBase.h"
#include "DamagedEffect.h"
#include "Structure.h"
#include "Tower.h"
#include "Mesmerize.h"
#include "AStarController.h"

//Character 움직임 (자리차지 x, astar 알고리즘)
void MoveCharacterNoneSpace::run(cocos2d::Ref* ref){
	Character* own = dynamic_cast<Character*>(ref);							//주체에 대한 casting
	Structure* target = objectFinder<Structure*>(own->get_targetID());		//Target에 대한 casting

	int around_x = 0;
	int around_y = 0;
	make_around_position(around_x, around_y, target->get_x(), target->get_y(), Object_::board);

	AstarController astar;	
	if (own->get_frame() == 0){
		own->set_state(STATE::MOVE);

		if (own->path.empty()){
			if (astar.run(Object_::board, own->path, own->get_x(), own->get_y(), around_x, around_y) == false){
				EXCEPTION("all root is blocked!");		//모든 경로가 막혔다는 메시지 전달 후 바로 끝냄
				return;
			}
			own->path.erase(own->path.begin());
		}
		own->set_started(true);							//얻은 경로에 맞게 세팅
		own->set_direction(getDirection(own->get_x(), own->get_y(), own->path.front().first, own->path.front().second));
		own->after_x = own->get_x();
		own->after_y = own->get_y();
		own->set_x(own->path.front().first);
		own->set_y(own->path.front().second);
		own->path.erase(own->path.begin());
	}else if (own->get_frame() == 1){
		Object_::graphic.display(own->get_move_imgID(), own->get_gx(), own->get_gy(), own->get_move_frame(), own->get_direction(), own->get_speed(), own->get_sprite());		//////////////////////////////////임시방편
	}

	own->set_gx(own->after_x*SIZE_OF_BOARD_CELL_X + (own->get_frame())*SIZE_OF_BOARD_CELL_X / (own->get_move_frame()*own->get_speed())*move_x[(int)own->get_direction()]);
	own->set_gy(own->after_y*SIZE_OF_BOARD_CELL_Y + (own->get_frame())*SIZE_OF_BOARD_CELL_Y / (own->get_move_frame()*own->get_speed())*move_y[(int)own->get_direction()]);
	own->get_sprite()->setPosition(cocos2d::Vec2(own->get_gx(), own->get_gy()));

	if (own->get_frame() >= own->get_move_frame()*own->get_speed() - 1){		//마지막 프레임일 경우
		own->set_started(false);
		own->initMessage(STATE::BASE);
	}
	else{
		own->initMessage(STATE::MOVE);
	}

	own->set_frame((own->get_frame() + 1) % (own->get_move_frame()*own->get_speed()));
	if (abs(own->get_x() - target->get_x()) <= 1 && abs(own->get_y() - target->get_y()) <= 1){
		Object_::mainQ.push(Message(-1, own->get_id(), CONTROLLER::ARRIVED));
	}
}


//Skill 움직임
void MoveSkill::run(cocos2d::Ref* ref){
	Skill* own = dynamic_cast<Skill*>(ref);							//주체에 대한 casting
	Unit* target = objectFinder<Unit*>(own->get_targetID());		//Target에 대한 casting

	if (own->get_frame() == 0){										//첫 프레임일 경우
		own->set_state(STATE::MOVE);
		Object_::graphic.display(own->get_move_imgID(), own->get_gx(), own->get_gy(), own->get_move_frame(), DIRECTION::EMPTY, own->get_speed(), own->get_sprite());
	}

	if (target == 0){												//Target이 없으면
		//EXCEPTION("Object_ is not in hash ");
		float sx = (float)own->get_gx();
		float sy = (float)own->get_gy();
		float dx = (float)own->target_x;
		float dy = (float)own->target_y;

		float dis = sqrt(distance2D(sx, sy, dx, dy));
		float xflus = (dx - sx) / dis;
		float yflus = (dy - sy) / dis;

		own->set_gx((int)(sx + 20 * xflus));
		own->set_gy((int)(sy + 20 * yflus));
		own->get_sprite()->setPosition(cocos2d::Vec2(own->get_gx(), own->get_gy()));

	}
	else{
		own->target_x = target->get_gx();			//target과 own사이의 직선 위에서 20만큼의 거리를 이동
		own->target_y = target->get_gy();

		float sx = (float)own->get_gx();
		float sy = (float)own->get_gy();
		float dx = (float)target->get_gx();
		float dy = (float)target->get_gy();

		float dis = sqrt(distance2D(sx, sy, dx, dy));
		float xflus = (dx - sx) / dis;
		float yflus = (dy - sy) / dis;
		
		own->set_gx((int)(sx + 20 * xflus));
		own->set_gy((int)(sy + 20 * yflus));
		own->get_sprite()->setPosition(cocos2d::Vec2(own->get_gx(), own->get_gy()));
	}

	if (inRange(own->get_gx(), own->get_gy(), own->target_x, own->target_y, 10)){		//범위 내부
		own->initMessage(STATE::ATTACK);
	}
	else{																				//범위 외부
		if (own->get_frame() >= own->get_move_frame() - 1){		//마지막 프레임일 경우
			own->initMessage(STATE::BASE);
		}
		else{
			own->initMessage(STATE::MOVE);
		}
	}
	own->set_frame((own->get_frame() + 1) % own->get_move_frame());
}

//Skill 움직임(피격효과)
void MoveDamagedEffect::run(cocos2d::Ref* ref){
	DamagedEffect* own = dynamic_cast<DamagedEffect*>(ref);				//주체에 대한 casting
	Unit* target = objectFinder<Unit*>(own->get_targetID());			//Target에 대한 casting

	if (own->get_frame() == 0){											//첫 프레임일 경우
		own->set_state(STATE::MOVE);
		Object_::graphic.display(own->get_move_imgID(), own->get_gx(), own->get_gy(), own->get_move_frame(), DIRECTION::EMPTY, own->get_speed(), own->get_sprite());
	}

	if (target == nullptr){												//Target이 없을 때
		//EXCEPTION("Object_ is not in hash (target)");
		own->set_gx(own->target_x);
		own->set_gy(own->target_y);
		own->get_sprite()->setPosition(cocos2d::Vec2(own->get_gx(), own->get_gy()));

	}
	else{
		own->target_x = target->get_gx();
		own->target_y = target->get_gy();
		own->set_gx(own->target_x);
		own->set_gy(own->target_y);
		own->get_sprite()->setPosition(cocos2d::Vec2(own->get_gx(), own->get_gy()));
	}

	if (own->get_frame() >= own->get_move_frame() - 1){		//마지막 프레임일 경우
		Object_::mainQ.push(Message(own->get_id(), own->get_id(), CONTROLLER::DELETE));
	}
	else{
		own->initMessage(STATE::MOVE);
	}
	own->set_frame((own->get_frame() + 1) % own->get_move_frame());
}

//Skill 움직임(즉시타격)
void MoveSkillDirect::run(cocos2d::Ref* ref){
	Skill* own = dynamic_cast<Skill*>(ref);							//주체에 대한 casting
	Unit* target = objectFinder<Unit*>(own->get_targetID());		//Target에 대한 casting

	if (own->get_frame() == 0){										//첫 프레임일 경우
		own->set_state(STATE::MOVE);
		Object_::graphic.display(own->get_move_imgID(), own->get_gx(), own->get_gy(), own->get_move_frame(), DIRECTION::EMPTY, own->get_speed(), own->get_sprite());
	}

	own->get_sprite()->setPosition(cocos2d::Vec2(own->get_gx(), own->get_gy()));
	own->initMessage(STATE::BASE);
	own->set_frame((own->get_frame() + 1) % own->get_move_frame());
}

//Mesmerize 움직임
void MoveMesmerize::run(cocos2d::Ref* ref){
	Mesmerize* own = dynamic_cast<Mesmerize*>(ref);
	auto iter = Object_::all.find(own->get_targetID());

	if (own->get_frame() == 0){
		own->set_state(STATE::MOVE);
		Object_::graphic.display(own->get_move_imgID(), own->get_gx(), own->get_gy(), own->get_move_frame(), DIRECTION::EMPTY, own->get_speed(), own->get_sprite());
	}

	if (iter ==Object_::all.end()){										//Target이 없을 때
		//EXCEPTION("Object_ is not in hash (target)");
		Object_::mainQ.push(Message(own->get_id(), own->get_id(), CONTROLLER::DELETE));
		own->set_gx(own->target_x);
		own->set_gy(own->target_y);
		own->get_sprite()->setPosition(cocos2d::Vec2(own->get_gx(), own->get_gy()));
	}
	else{
		Unit* target = dynamic_cast<Unit*>(iter->second);				//Target에 대한 casting

		if (target->get_state() == STATE::DIE)own->finish();			//마지막에 수행될 상태이상

		own->target_x = target->get_gx();
		own->target_y = target->get_gy();
		own->set_gx(own->target_x);
		own->set_gy(own->target_y);
		own->get_sprite()->setPosition(cocos2d::Vec2(own->get_gx(), own->get_gy()));

		if (own->get_frame() == own->get_move_frame() * own->get_speed() - 1){		//마지막 프레임일 경우
			if (own->get_life_time() < own->get_now_time()){
				own->finish();											//마지막에 수행될 상태이상
			}
			else{
				own->middle();											//중간에 수행될 상태이상
				own->initMessage(STATE::MOVE);
				own->set_now_time(own->get_now_time() + 1);
			}
		}else{
			own->initMessage(STATE::MOVE);
		}
	}
	own->set_frame((own->get_frame() + 1) % (own->get_move_frame() * own->get_speed()));
}


//Character 움직임(비행)
void MoveFlyingCharacter::run(cocos2d::Ref* ref){
	Character* own = dynamic_cast<Character*>(ref);							//주체에 대한 casting
	Structure* target = objectFinder<Structure*>(own->get_targetID());		//Target에 대한 casting

	if (own->get_frame() == 1){												//첫 프레임일 경우
		own->set_state(STATE::MOVE);
		Object_::graphic.display(own->get_move_imgID(), own->get_gx(), own->get_gy(), own->get_move_frame(), own->get_direction(), own->get_speed(), own->get_sprite());
	}

	float sx = (float)own->get_gx();
	float sy = (float)own->get_gy();
	float dx = (float)target->get_gx();
	float dy = (float)target->get_gy();

	float m = (dy - sy) / (dx - sx);
	if (-1 < m && m < 1){										//방향 얻기
		if (dx - sx > 0)	own->set_direction(DIRECTION::RIGHT);
		else				own->set_direction(DIRECTION::LEFT);
	}
	else{
		if (dy - sy > 0)	own->set_direction(DIRECTION::DOWN);
		else				own->set_direction(DIRECTION::UP);
	}
	float dis = sqrt(distance2D(sx, sy, dx, dy));
	float xflus = (dx - sx) / dis;
	float yflus = (dy - sy) / dis;
	
	if (own->get_frame() % 2 == 0){
		own->set_gx((int)(sx + (50 * xflus) / own->get_speed()));	//속도 반영
		own->set_gy((int)(sy + (50 * yflus) / own->get_speed()));
	}
	own->set_x(sx / SIZE_OF_BOARD_CELL_X);
	own->set_y(sy / SIZE_OF_BOARD_CELL_Y);

	own->get_sprite()->setPosition(cocos2d::Vec2(own->get_gx(), own->get_gy()));

	if (own->get_frame() >= own->get_move_frame()*own->get_speed() - 1){		//마지막 프레임일 경우
		own->initMessage(STATE::BASE);
	}
	else{
		own->initMessage(STATE::MOVE);
	}

	own->set_frame((own->get_frame() + 1) % (own->get_move_frame()*own->get_speed()));	//속도 반영

	if (abs(own->get_x() - target->get_x()) <= 1 && abs(own->get_y() - target->get_y()) <= 1){
		Object_::mainQ.push(Message(-1, own->get_id(), CONTROLLER::ARRIVED));
	}
}
