#ifndef __SKILL_H__
#define __SKILL_H__

#include "constant.h"
#include "Object_.h"
#include "Interface.h"
class Skill : public Object_{
public:
	int target_x,target_y;
protected:		//value
	int gx,gy;					//변수
	int targetID;
	int damage;
	int level;

	int frame;					//변수(내부에서 생성)

	int speed;					//DB
	int range;
	int move_frame;
	int move_imgID;
	int move_soundID;
	int damagedEffectID;

public:		//constructor & destructor
	Skill();
	virtual ~Skill();
	Skill(const SkillDBdata& data, int id, int gx, int gy, int targetID, int damage, int level);

public:		//virtual method
	virtual void base()					=	0;

public:		//own method

public:		//getter & setter
	const int& get_gx() const;
	const int& get_gy() const;
	const int& get_frame() const;
	const int& get_targetID() const;
	const int& get_damage() const;
	const int& get_level() const;
	const int& get_speed() const;
	const int& get_range() const;
	const int& get_move_frame() const;
	const int& get_move_imgID() const;
	const int& get_move_soundID() const;
	const int& get_damagedEffectID() const;

	void set_gx(const int& gx);
	void set_gy(const int& gy);
	void set_frame(const int& frame);
	void set_targetID(const int& targetID);
	void set_damage(const int& damage);
	void set_level(const int& level);
	void set_speed(const int& speed);
	void set_range(const int& range);
	void set_move_frame(const int& attack_frame);
	void set_move_imgID(const int& skill_frame);
	void set_move_soundID(const int& attack_imgID);
	void set_damagedEffectID(const int& damagedEffectID);
};

#endif