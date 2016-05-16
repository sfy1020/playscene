#ifndef __UNIT_H__
#define __UNIT_H__

#include "constant.h"
#include "Object_.h"
#include "Interface.h"

class Unit : public Object_{
protected:		//value
	int x,y;					//변수
	DIRECTION direction;
	int targetID;

	int gx,gy;					//변수(내부에서 생성)
	int hp,mp;
	int frame;
	int level;
	MESMERIZE mesmerize_state;

	int maxhp,maxmp;			//DB
	int damage;
	int speed;
	int range;
	int attack_frame;
	int skill_frame;
	int die_frame;
	int attack_imgID;
	int skill_imgID;
	int die_imgID;
	int attack_soundID;
	int skill_soundID;
	int die_soundID;

public:		//constructor
	Unit();
	virtual ~Unit();
	Unit(const UnitDBdata& data, int id, int x, int y, DIRECTION direction, int targetID);

public:		//virtual method
	virtual void base()					=	0;
	virtual void levelUp()				=	0;

public:		//own method
	void damaged(int damagedEffectID, int damage);

public:		//getter & setter
	const int& get_x() const;
	const int& get_y() const;
	const int& get_gx() const;
	const int& get_gy() const;
	const int& get_frame() const;
	const int& get_level() const;
	const MESMERIZE& get_mesmerize_state() const;
	const DIRECTION& get_direction() const;
	const int& get_hp() const;
	const int& get_mp() const;
	const int& get_targetID() const;
	const int& get_range() const;
	const int& get_maxhp() const;
	const int& get_maxmp() const;
	const int& get_damage() const;
	const int& get_speed() const;
	const int& get_attack_frame() const;
	const int& get_skill_frame() const;
	const int& get_die_frame() const;
	const int& get_attack_imgID() const;
	const int& get_skill_imgID() const;
	const int& get_die_imgID() const;
	const int& get_attack_soundID() const;
	const int& get_skill_soundID() const;
	const int& get_die_soundID() const;

	void set_x(const int& x);
	void set_y(const int& y);
	void set_gx(const int& gx);
	void set_gy(const int& gy);
	void set_frame(const int& frame);
	void set_level(const int& level);
	void set_mesmerize_state(const MESMERIZE& level);
	void set_direction(const DIRECTION& direction);
	void set_hp(const int& hp);
	void set_mp(const int& mp);
	void set_targetID(const int& targetID);
	void set_range(const int& range);
	void set_maxhp(const int& maxhp);
	void set_maxmp(const int& maxmp);
	void set_damage(const int& damage);
	void set_speed(const int& speed);
	void set_attack_frame(const int& attack_frame);
	void set_skill_frame(const int& skill_frame);
	void set_die_frame(const int& die_frame);
	void set_attack_imgID(const int& attack_imgID);
	void set_skill_imgID(const int& skill_imgID);
	void set_die_imgID(const int& die_frame);
	void set_attack_soundID(const int& attack_soundID);
	void set_skill_soundID(const int& skill_soundID);
	void set_die_soundID(const int& die_frame);
};

#endif