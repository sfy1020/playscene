#include "Move.h"
#include "Character.h"
#include "SkillBase.h"
#include "DamagedEffect.h"
#include "Structure.h"
#include "Tower.h"
#include "Mesmerize.h"
#include "AStarController.h"

//Character ������ (�ڸ����� x, astar �˰���)
void MoveCharacterNoneSpace::run(cocos2d::Ref* ref){
	Character* own = dynamic_cast<Character*>(ref);							//��ü�� ���� casting
	Structure* target = objectFinder<Structure*>(own->get_targetID());		//Target�� ���� casting

	int around_x = 0;
	int around_y = 0;
	make_around_position(around_x, around_y, target->get_x(), target->get_y(), Object_::board);

	AstarController astar;	
	if (own->get_frame() == 0){
		own->set_state(STATE::MOVE);

		if (own->path.empty()){
			if (astar.run(Object_::board, own->path, own->get_x(), own->get_y(), around_x, around_y) == false){
				EXCEPTION("all root is blocked!");		//��� ��ΰ� �����ٴ� �޽��� ���� �� �ٷ� ����
				return;
			}
			own->path.erase(own->path.begin());
		}
		own->set_started(true);							//���� ��ο� �°� ����
		own->set_direction(getDirection(own->get_x(), own->get_y(), own->path.front().first, own->path.front().second));
		own->after_x = own->get_x();
		own->after_y = own->get_y();
		own->set_x(own->path.front().first);
		own->set_y(own->path.front().second);
		own->path.erase(own->path.begin());
	}else if (own->get_frame() == 1){
		Object_::graphic.display(own->get_move_imgID(), own->get_gx(), own->get_gy(), own->get_move_frame(), own->get_direction(), own->get_speed(), own->get_sprite());		//////////////////////////////////�ӽù���
	}

	own->set_gx(own->after_x*SIZE_OF_BOARD_CELL_X + (own->get_frame())*SIZE_OF_BOARD_CELL_X / (own->get_move_frame()*own->get_speed())*move_x[(int)own->get_direction()]);
	own->set_gy(own->after_y*SIZE_OF_BOARD_CELL_Y + (own->get_frame())*SIZE_OF_BOARD_CELL_Y / (own->get_move_frame()*own->get_speed())*move_y[(int)own->get_direction()]);
	own->get_sprite()->setPosition(cocos2d::Vec2(own->get_gx(), own->get_gy()));

	if (own->get_frame() >= own->get_move_frame()*own->get_speed() - 1){		//������ �������� ���
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


//Skill ������
void MoveSkill::run(cocos2d::Ref* ref){
	Skill* own = dynamic_cast<Skill*>(ref);							//��ü�� ���� casting
	Unit* target = objectFinder<Unit*>(own->get_targetID());		//Target�� ���� casting

	if (own->get_frame() == 0){										//ù �������� ���
		own->set_state(STATE::MOVE);
		Object_::graphic.display(own->get_move_imgID(), own->get_gx(), own->get_gy(), own->get_move_frame(), DIRECTION::EMPTY, own->get_speed(), own->get_sprite());
	}

	if (target == 0){												//Target�� ������
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
		own->target_x = target->get_gx();			//target�� own������ ���� ������ 20��ŭ�� �Ÿ��� �̵�
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

	if (inRange(own->get_gx(), own->get_gy(), own->target_x, own->target_y, 10)){		//���� ����
		own->initMessage(STATE::ATTACK);
	}
	else{																				//���� �ܺ�
		if (own->get_frame() >= own->get_move_frame() - 1){		//������ �������� ���
			own->initMessage(STATE::BASE);
		}
		else{
			own->initMessage(STATE::MOVE);
		}
	}
	own->set_frame((own->get_frame() + 1) % own->get_move_frame());
}

//Skill ������(�ǰ�ȿ��)
void MoveDamagedEffect::run(cocos2d::Ref* ref){
	DamagedEffect* own = dynamic_cast<DamagedEffect*>(ref);				//��ü�� ���� casting
	Unit* target = objectFinder<Unit*>(own->get_targetID());			//Target�� ���� casting

	if (own->get_frame() == 0){											//ù �������� ���
		own->set_state(STATE::MOVE);
		Object_::graphic.display(own->get_move_imgID(), own->get_gx(), own->get_gy(), own->get_move_frame(), DIRECTION::EMPTY, own->get_speed(), own->get_sprite());
	}

	if (target == nullptr){												//Target�� ���� ��
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

	if (own->get_frame() >= own->get_move_frame() - 1){		//������ �������� ���
		Object_::mainQ.push(Message(own->get_id(), own->get_id(), CONTROLLER::DELETE));
	}
	else{
		own->initMessage(STATE::MOVE);
	}
	own->set_frame((own->get_frame() + 1) % own->get_move_frame());
}

//Skill ������(���Ÿ��)
void MoveSkillDirect::run(cocos2d::Ref* ref){
	Skill* own = dynamic_cast<Skill*>(ref);							//��ü�� ���� casting
	Unit* target = objectFinder<Unit*>(own->get_targetID());		//Target�� ���� casting

	if (own->get_frame() == 0){										//ù �������� ���
		own->set_state(STATE::MOVE);
		Object_::graphic.display(own->get_move_imgID(), own->get_gx(), own->get_gy(), own->get_move_frame(), DIRECTION::EMPTY, own->get_speed(), own->get_sprite());
	}

	own->get_sprite()->setPosition(cocos2d::Vec2(own->get_gx(), own->get_gy()));
	own->initMessage(STATE::BASE);
	own->set_frame((own->get_frame() + 1) % own->get_move_frame());
}

//Mesmerize ������
void MoveMesmerize::run(cocos2d::Ref* ref){
	Mesmerize* own = dynamic_cast<Mesmerize*>(ref);
	auto iter = Object_::all.find(own->get_targetID());

	if (own->get_frame() == 0){
		own->set_state(STATE::MOVE);
		Object_::graphic.display(own->get_move_imgID(), own->get_gx(), own->get_gy(), own->get_move_frame(), DIRECTION::EMPTY, own->get_speed(), own->get_sprite());
	}

	if (iter ==Object_::all.end()){										//Target�� ���� ��
		//EXCEPTION("Object_ is not in hash (target)");
		Object_::mainQ.push(Message(own->get_id(), own->get_id(), CONTROLLER::DELETE));
		own->set_gx(own->target_x);
		own->set_gy(own->target_y);
		own->get_sprite()->setPosition(cocos2d::Vec2(own->get_gx(), own->get_gy()));
	}
	else{
		Unit* target = dynamic_cast<Unit*>(iter->second);				//Target�� ���� casting

		if (target->get_state() == STATE::DIE)own->finish();			//�������� ����� �����̻�

		own->target_x = target->get_gx();
		own->target_y = target->get_gy();
		own->set_gx(own->target_x);
		own->set_gy(own->target_y);
		own->get_sprite()->setPosition(cocos2d::Vec2(own->get_gx(), own->get_gy()));

		if (own->get_frame() == own->get_move_frame() * own->get_speed() - 1){		//������ �������� ���
			if (own->get_life_time() < own->get_now_time()){
				own->finish();											//�������� ����� �����̻�
			}
			else{
				own->middle();											//�߰��� ����� �����̻�
				own->initMessage(STATE::MOVE);
				own->set_now_time(own->get_now_time() + 1);
			}
		}else{
			own->initMessage(STATE::MOVE);
		}
	}
	own->set_frame((own->get_frame() + 1) % (own->get_move_frame() * own->get_speed()));
}


//Character ������(����)
void MoveFlyingCharacter::run(cocos2d::Ref* ref){
	Character* own = dynamic_cast<Character*>(ref);							//��ü�� ���� casting
	Structure* target = objectFinder<Structure*>(own->get_targetID());		//Target�� ���� casting

	if (own->get_frame() == 1){												//ù �������� ���
		own->set_state(STATE::MOVE);
		Object_::graphic.display(own->get_move_imgID(), own->get_gx(), own->get_gy(), own->get_move_frame(), own->get_direction(), own->get_speed(), own->get_sprite());
	}

	float sx = (float)own->get_gx();
	float sy = (float)own->get_gy();
	float dx = (float)target->get_gx();
	float dy = (float)target->get_gy();

	float m = (dy - sy) / (dx - sx);
	if (-1 < m && m < 1){										//���� ���
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
		own->set_gx((int)(sx + (50 * xflus) / own->get_speed()));	//�ӵ� �ݿ�
		own->set_gy((int)(sy + (50 * yflus) / own->get_speed()));
	}
	own->set_x(sx / SIZE_OF_BOARD_CELL_X);
	own->set_y(sy / SIZE_OF_BOARD_CELL_Y);

	own->get_sprite()->setPosition(cocos2d::Vec2(own->get_gx(), own->get_gy()));

	if (own->get_frame() >= own->get_move_frame()*own->get_speed() - 1){		//������ �������� ���
		own->initMessage(STATE::BASE);
	}
	else{
		own->initMessage(STATE::MOVE);
	}

	own->set_frame((own->get_frame() + 1) % (own->get_move_frame()*own->get_speed()));	//�ӵ� �ݿ�

	if (abs(own->get_x() - target->get_x()) <= 1 && abs(own->get_y() - target->get_y()) <= 1){
		Object_::mainQ.push(Message(-1, own->get_id(), CONTROLLER::ARRIVED));
	}
}
