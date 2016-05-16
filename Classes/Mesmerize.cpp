#include "Mesmerize.h"

//constructor & destructor
Mesmerize::Mesmerize() :Skill(), now_time(0), unit_color(cocos2d::Color3B::BLACK), speed_control(0), wait_control(0), continue_damage(0), life_time(0){
}

Mesmerize::~Mesmerize(){
}

Mesmerize::Mesmerize(const MesmerizeDBdata& data, int id, int gx, int gy, int targetID, int damage, int level)
	:Skill(data, id, gx, gy, targetID, damage, level){
	this->now_time			=	0;							//내부변수
	this->unit_color		=	cocos2d::Color3B::BLACK;

	this->speed_control		=	data.speed_control;			//DB
	this->wait_control		=	data.wait_control;
	this->continue_damage	=	data.continue_damage;
	this->life_time			=	data.life_time;
	
	stateMachine.emplace_back(std::make_shared<MoveMesmerize>(MoveMesmerize()));			//interface
	sound.run(move_soundID);
}

//interface method

//virtual method
void Mesmerize::base(){
	message.push(STATE::MOVE);
}

//own method

//getter&setter
const int& Mesmerize::get_life_time() const{
	return life_time;
}
const int& Mesmerize::get_speed_control() const{
	return speed_control;
}
const int& Mesmerize::get_wait_control() const{
	return wait_control;
}
const int& Mesmerize::get_continue_damage() const{
	return continue_damage;
}
const int& Mesmerize::get_now_time() const{
	return now_time;
}
const cocos2d::Color3B& Mesmerize::get_unit_color() const{
	return unit_color;
}

void Mesmerize::set_life_time(const int& life_time){
	this->life_time = life_time;
}
void Mesmerize::set_speed_control(const int& speed_control){
	this->speed_control = speed_control;
}
void Mesmerize::set_wait_control(const int& wait_control){
	this->wait_control = wait_control;
}
void Mesmerize::set_continue_damage(const int& continue_damage){
	this->continue_damage = continue_damage;
}
void Mesmerize::set_now_time(const int& now_time){
	this->now_time = now_time;
}
void Mesmerize::set_unit_color(const cocos2d::Color3B& unit_color){
	this->unit_color = unit_color;
}