#include "Skill.h"
#include "Character.h"

//constructor & destructor
Skill::Skill() :Object_(), gx(0), gy(0), frame(0), target_x(0), target_y(0), targetID(0), damage(0),
speed(0), range(0), move_frame(0), move_imgID(0), move_soundID(0), damagedEffectID(0){}

Skill::~Skill(){
}

Skill::Skill(const SkillDBdata& data, int id, int gx, int gy, int targetID, int damage, int level):Object_(data, id){
	this->gx				=	gx;				//변수
	this->gy				=	gy;
	this->targetID			=	targetID;
	this->damage			=	damage;
	this->level				=	level;

	this->frame				=	0;				//변수(내부에서 생성)
	this->sleep_time		=	data.speed;

	this->speed				=	data.speed;		//DB
	this->range				=	data.range;
	this->move_frame		=	data.move_frame;
	this->move_imgID		=	data.move_imgID;
	this->move_soundID		=	data.move_soundID;
	this->damagedEffectID	=	data.damagedEffectID;

	GraphicDBdata gtemp = graphic.get_GraphicDBdata(imgID);			//sprite image setting
	this->sprite			=	cocos2d::Sprite::create(gtemp.filename,cocos2d::Rect(0, 0, gtemp.size_x, gtemp.size_y));
	this->sprite->setTag(id);
	this->sprite->setPosition(cocos2d::Vec2(gx,gy));
	this->sprite->setScale(0.75 + level*0.05);
	this->sprite->setLocalZOrder(BIG_INT+1);
	objectLayer->addChild(this->sprite);

	auto iter = all.find(targetID);
	if(iter == all.end()){
		EXCEPTION2("target is not in hash!", targetID);
		Object_::mainQ.push(Message(id,id,CONTROLLER::DELETE));
	}else{
		Unit* target = dynamic_cast<Unit*>(iter->second);
		this->target_x			=	target->get_gx();
		this->target_y			=	target->get_gy();
		this->sprite->setRotation(-atan2(this->target_y - gy, this->target_x - gx) * 180 / M_PI + 180 + gtemp.angle);

		if (target->get_state() == STATE::DIE){
			Object_::mainQ.push(Message(id,id,CONTROLLER::DELETE));
		}
	}
}
//virtual method

//own method

//getter & setter
const int& Skill::get_gx() const{
	return gx;
}
const int& Skill::get_gy() const{
	return gy;
}
const int& Skill::get_frame() const{
	return frame;
}
const int& Skill::get_targetID() const{
	return targetID;
}
const int& Skill::get_damage() const{
	return damage;
}
const int& Skill::get_level() const{
	return level;
}
const int& Skill::get_speed() const{
	return speed;
}
const int& Skill::get_range() const{
	return range;
}
const int& Skill::get_move_frame() const{
	return move_frame;
}
const int& Skill::get_move_imgID() const{
	return move_imgID;
}
const int& Skill::get_move_soundID() const{
	return move_soundID;
}
const int& Skill::get_damagedEffectID() const{
	return damagedEffectID;
}

void Skill::set_gx(const int& gx) {
	this->gx = gx;
}
void Skill::set_gy(const int& gy) {
	this->gy = gy;
}
void Skill::set_frame(const int& frame) {
	this->frame = frame;
}
void Skill::set_targetID(const int& targetID) {
	this->targetID = targetID;
}
void Skill::set_damage(const int& damage) {
	this->damage = damage;
}
void Skill::set_level(const int& level){
	this->level = level;
}
void Skill::set_speed(const int& speed) {
	this->speed = speed;
}
void Skill::set_range(const int& range) {
	this->range = range;
}
void Skill::set_move_frame(const int& move_frame) {
	this->move_frame = move_frame;
}
void Skill::set_move_imgID(const int& move_imgID) {
	this->move_imgID = move_imgID;
}
void Skill::set_move_soundID(const int& move_soundID) {
	this->move_soundID = move_soundID;
}
void Skill::set_damagedEffectID(const int& damagedEffectID){
	this->damagedEffectID = damagedEffectID;
}
