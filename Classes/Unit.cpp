#include "Unit.h"

//constructor
Unit::Unit():Object_(),x(0),y(0),direction(DIRECTION::EMPTY),frame(0),level(1),mesmerize_state(MESMERIZE::NONE),attack_frame(0),skill_frame(0),hp(0),mp(0),maxhp(0),maxmp(0),
	damage(0),speed(0),targetID(0),range(0),attack_imgID(0),skill_imgID(0),attack_soundID(0),skill_soundID(0){gx=0;gy=0;}

Unit::~Unit(){
}

Unit::Unit(const UnitDBdata& data, int id, int x, int y, DIRECTION direction, int targetID) :Object_(data, id){
	this->x					=	x;				//변수
	this->y					=	y;
	this->direction			=	direction;
	this->targetID			=	targetID;

	this->hp				=	data.maxhp;
	this->mp				=	data.maxmp;
	this->gx				=	x*SIZE_OF_BOARD_CELL_X;
	this->gy				=	y*SIZE_OF_BOARD_CELL_Y;
	this->frame				=	0;
	this->level				=	1;
	this->mesmerize_state	=	MESMERIZE::NONE;

	this->maxhp				=	data.maxhp;		//DB
	this->maxmp				=	data.maxmp;
	this->damage			=	data.damage;
	this->speed				=	data.speed;
	this->range				=	data.range;
	this->attack_frame		=	data.attack_frame;
	this->skill_frame		=	data.skill_frame;
	this->die_frame			=	data.die_frame;
	this->attack_imgID		=	data.attack_imgID;
	this->skill_imgID		=	data.skill_imgID;
	this->die_imgID			=	data.die_imgID;
	this->attack_soundID	=	data.attack_soundID;
	this->skill_soundID		=	data.skill_soundID;
	this->die_soundID		=	data.die_soundID;

	stateMachine.emplace_back(std::make_shared<DieCommon>(DieCommon()));			//interface

	GraphicDBdata gtemp = graphic.get_GraphicDBdata(imgID);			//sprite image setting
	this->sprite			=	cocos2d::Sprite::create(gtemp.filename,cocos2d::Rect(0, gtemp.size_y * (int)direction, gtemp.size_x, gtemp.size_y));
	this->sprite->setPosition(cocos2d::Vec2(gx,gy));
	this->sprite->setTag(id);
	this->sprite->setLocalZOrder(BIG_INT - gy);
	objectLayer->addChild(this->sprite);
}

//virtual method

//own method
void Unit::damaged(int damagedEffectID, int damage){
	if (state == STATE::DIE)return;					//죽는중일 경우 return

	hp = std::max(0, hp - damage);
	mainQ.push(Message(id, damagedEffectID, CONTROLLER::CREATE));			//damagedEffect 생성
	mainQ.push(Message(-1, id, CONTROLLER::CHARACTER_DAMAGED));				//property 갱신을 위해

	if (hp == 0){
		while (!isMessageEmpty()){						//대상의 모든 행위 제거
			popMessage();
		}
		frame = 0;										//대상의 frame 초기화
		initMessage(STATE::DIE);
		state = STATE::DIE;
	}
}

//getter & setter
const int& Unit::get_x() const{
	return x;
}
const int& Unit::get_y() const{
	return y;
}
const int& Unit::get_gx() const{
	return gx;
}
const int& Unit::get_gy() const{
	return gy;
}
const int& Unit::get_frame() const{
	return frame;
}
const int& Unit::get_level() const{
	return level;
}
const MESMERIZE& Unit::get_mesmerize_state() const{
	return mesmerize_state;
}
const DIRECTION& Unit::get_direction() const{
	return direction;
}
const int& Unit::get_hp() const{
	return hp;
}
const int& Unit::get_mp() const{
	return mp;
}
const int& Unit::get_targetID() const{
	return targetID;
}
const int& Unit::get_range() const{
	return range;
}
const int& Unit::get_maxhp() const{
	return maxhp;
}
const int& Unit::get_maxmp() const{
	return maxmp;
}
const int& Unit::get_damage() const{
	return damage;
}
const int& Unit::get_speed() const{
	return speed;
}
const int& Unit::get_attack_frame() const{
	return attack_frame;
}
const int& Unit::get_skill_frame() const{
	return skill_frame;
}
const int& Unit::get_die_frame() const{
	return die_frame;
}
const int& Unit::get_attack_imgID() const{
	return attack_imgID;
}
const int& Unit::get_skill_imgID() const{
	return skill_imgID;
}
const int& Unit::get_die_imgID() const{
	return die_imgID;
}
const int& Unit::get_attack_soundID() const{
	return attack_soundID;
}
const int& Unit::get_skill_soundID() const{
	return skill_soundID;
}
const int& Unit::get_die_soundID() const{
	return die_soundID;
}

void Unit::set_x(const int& x) {
	this->x = x;
}
void Unit::set_y(const int& y) {

	this->y = y;
}
void Unit::set_gx(const int& gx) {
	this->gx = gx;
}
void Unit::set_gy(const int& gy) {
	this->gy = gy;
}
void Unit::set_frame(const int& frame) {
	this->frame = frame;
}
void Unit::set_level(const int& level) {
	this->level = level;
}
void Unit::set_mesmerize_state(const MESMERIZE& mesmerize_state) {
	this->mesmerize_state = mesmerize_state;
}
void Unit::set_direction(const DIRECTION& direction) {
	
	this->direction = direction;
}
void Unit::set_hp(const int& hp) {
	this->hp = hp;
}
void Unit::set_mp(const int& mp) {
	this->mp = mp;
}
void Unit::set_targetID(const int& targetID) {
	this->targetID = targetID;
}
void Unit::set_range(const int& range) {
	this->range = range;
}
void Unit::set_maxhp(const int& maxhp) {
	this->maxhp = maxhp;
}
void Unit::set_maxmp(const int& maxmp) {
	this->maxmp = maxmp;
}
void Unit::set_damage(const int& damage) {
	this->damage = damage;
}
void Unit::set_speed(const int& speed) {
	this->speed = speed;
}
void Unit::set_attack_frame(const int& attack_frame) {
	this->attack_frame = attack_frame;
}
void Unit::set_skill_frame(const int& skill_frame) {
	this->skill_frame = skill_frame;
}
void Unit::set_die_frame(const int& die_frame) {
	this->die_frame = die_frame;
}
void Unit::set_attack_imgID(const int& attack_imgID) {
	this->attack_imgID = attack_imgID;
}
void Unit::set_skill_imgID(const int& skill_imgID) {
	this->skill_imgID = skill_imgID;
}
void Unit::set_die_imgID(const int& die_imgID) {
	this->die_imgID = die_imgID;
}
void Unit::set_attack_soundID(const int& attack_soundID) {
	this->attack_soundID = attack_soundID;
}
void Unit::set_skill_soundID(const int& skill_soundID) {
	this->skill_soundID = skill_soundID;
}
void Unit::set_die_soundID(const int& die_soundID) {
	this->die_soundID = die_soundID;
}

