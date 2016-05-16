#ifndef __MESMERIZE_H__
#define __MESMERIZE_H__

#include "constant.h"
#include "Skill.h"
#include "Interface.h"

class Mesmerize : public Skill{
protected:		//value
	int now_time;		//내부변수
	cocos2d::Color3B unit_color;
	int speed_control;	//DB
	int wait_control;
	int continue_damage;
	int life_time;

public:		//constructor & destructor
	Mesmerize();
	virtual ~Mesmerize();
	Mesmerize(const MesmerizeDBdata& data, int id, int gx, int gy, int targetID, int damage, int level);

public:		//virtual method
	virtual void base();
	virtual void start()  = 0;
	virtual void finish() = 0;
	virtual void middle() = 0;

public:		//own method

public:		//getter & setter
	const int& get_life_time() const;
	const int& get_speed_control() const;
	const int& get_wait_control() const;
	const int& get_continue_damage() const;
	const int& get_now_time() const;
	const cocos2d::Color3B& get_unit_color() const;
	void set_life_time(const int& life_time);
	void set_speed_control(const int& speed_control);
	void set_wait_control(const int& wait_control);
	void set_continue_damage(const int& continue_damage);
	void set_now_time(const int& now_time);
	void set_unit_color(const cocos2d::Color3B& unit_color);
};

#endif