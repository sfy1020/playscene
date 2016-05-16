#include "Attack.h"
#include "Tower.h"
#include "Character.h"
#include "SkillBase.h"

//tower�� ����
void AttackTower::run(cocos2d::Ref* ref){
	Tower* own = dynamic_cast<Tower*>(ref);		//��ü�� ���� casting
	
	if (own->get_frame() == 0){															//ù �������� ���
		own->set_state(STATE::ATTACK);
		Object_::mainQ.push(Message(own->get_id(), own->get_attackID(), CONTROLLER::CREATE));
		Object_::sound.run(own->get_attack_soundID());
		Object_::graphic.display(own->get_attack_imgID(), own->get_gx(), own->get_gy(), own->get_attack_frame(), own->get_direction(), own->get_speed(), own->get_sprite());
	}

	if (own->get_frame() == own->get_attack_frame()*own->get_speed() - 1){				//������ �������� ���
		own->initMessage(STATE::BASE);
	}else{
		own->initMessage(STATE::ATTACK);
	}
	own->set_frame((own->get_frame() + 1) % (own->get_attack_frame()*own->get_speed()));
}


//skill�� ����
void AttackSkill::run(cocos2d::Ref* ref){
	Skill* own = dynamic_cast<Skill*>(ref);											//��ü�� ���� casting
	Character* target = objectFinder<Character*>(own->get_targetID());				//target�� ���� casting

	if (own->get_frame() == 0){							//ù �������� ���
		own->set_state(STATE::ATTACK);
	}

	if (target)	target->damaged(own->get_damagedEffectID(), own->get_damage());

	Object_::mainQ.push(Message(own->get_id(),own->get_id(),CONTROLLER::DELETE));	//�ڱ��ڽ��� ����
}


//skill�� ���� ����
void AttackSkillSplash::run(cocos2d::Ref* ref){
	Skill* own = dynamic_cast<Skill*>(ref);									//��ü�� ���� casting
	Character* target = objectFinder<Character*>(own->get_targetID());		//Target�� ���� casting

	if (own->get_frame() == 0){							//ù �������� ���
		own->set_state(STATE::ATTACK);
	}

	if (target){
		float sx = target->get_gx();
		float sy = target->get_gy();
		int range = own->get_range();  // ���÷��� ����
		for (auto e : Object_::all){
			if (OBJECT(e.second->get_DB_ID()) == CHARACTER){		//CHARACTER�� ��	
				target = dynamic_cast<Character*>(e.second);		//��� ���� casting
				if (inRange(sx, sy, target->get_gx(), target->get_gy(), range)){	//�������� ������
					target->damaged(own->get_damagedEffectID(), own->get_damage());
				}
			}
		}
	}
	Object_::mainQ.push(Message(own->get_id(), own->get_id(), CONTROLLER::DELETE));
}


//skill�� ���� ����
void AttackSkillApproach::run(cocos2d::Ref* ref){
	Skill* own = dynamic_cast<Skill*>(ref);									//��ü�� ���� casting
	Character* target = objectFinder<Character*>(own->get_targetID());		//Target�� ���� casting

	if (own->get_frame() == 0){							//ù �������� ���
		own->set_state(STATE::ATTACK);
	}

	if (target){
		int range = own->get_range();  // ����
		for (auto e : Object_::all){
			if (OBJECT(e.second->get_DB_ID()) == CHARACTER){		//CHARACTER�� ��	
				target = dynamic_cast<Character*>(e.second);		//��� ���� casting
				if (inRange(own->get_gx(), own->get_gy(), target->get_gx(), target->get_gy(), range)){		//�������� ������
					target->damaged(own->get_damagedEffectID(), own->get_damage());
				}
			}
		}
	}
	Object_::mainQ.push(Message(own->get_id(), own->get_id(), CONTROLLER::DELETE));
}
