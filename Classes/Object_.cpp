#include "Object_.h"
#include <algorithm>

std::map<int, Object_*> Object_::all;		//Object_ class의 static 변수
int Object_::board[BOARD_Y][BOARD_X]={0};
std::queue<Message> Object_::mainQ;
GraphicClass  Object_::graphic;
SoundClass  Object_::sound;
cocos2d::Layer* Object_::objectLayer = cocos2d::Layer::create();
DBClass Object_::DBmanager;

//constructor
Object_::Object_() :id(0), name(""), DB_ID(0), state(STATE::BASE), time_slice_cnt(0), sleep_time(0), started(false), sprite(0){
	message.push(STATE::BASE);
}

Object_::~Object_(){		//정리
	while (!message.empty())
		message.pop();

	Object_::objectLayer->removeChild(sprite,false);
}

Object_::Object_(const ObjectDBdata& data, int id){
	message.push(STATE::BASE);
	this->state				=	STATE::BASE;		//내부 변수
	this->time_slice_cnt	=	0;		//내부 변수
	this->sleep_time		=	1;		//내부 변수
	this->started			=	false;
	this->id				=	id;			//변수
	this->name				=	data.name;
	this->DB_ID				=	data.DB_ID;	//DB
	this->imgID				=	data.imgID;
}

//virtual method
void Object_::run(){
	if(!skipTimeSlice())return;
	STATE msg;
	while(!message.empty() && message.front()>STATE::IMMIDIATE){	//모든 즉시 실행해야 할 msg 실행
		msg = message.front();
		if (msg == STATE::BASE)	base();
		message.pop();
	}

	if(!message.empty()){						//한번만 실행할 msg 실행
		msg = message.front();
		
		//stateMachine에서 msg에 맞는 행동을 찾아 실행
		auto temp = std::find_if(stateMachine.begin(), stateMachine.end(), [msg](const std::shared_ptr<State> s) { return s->get_state() == msg; });
		if (temp == stateMachine.end()){
			EXCEPTION("not valid message")
		}else{
			(*temp)->run(this);
		}
		message.pop();
	}
}

bool Object_::skipTimeSlice(){
	time_slice_cnt = (time_slice_cnt + 1) % sleep_time;
	if (time_slice_cnt == 0){
		return true;
	}else{
		return false;
	}
}

//own method
void Object_::initMessage(STATE msg){
	message.push(msg);
}

STATE Object_::popMessage(){
	STATE temp = message.front();
	message.pop();
	return temp;
}

bool Object_::isMessageEmpty(){
	return message.empty();
}

//getter & setter
const int& Object_::get_id() const{
	return id;
}
const std::string& Object_::get_name() const{
	return name;
}
const int& Object_::get_DB_ID() const{
	return DB_ID;
}
const STATE& Object_::get_state() const{
	return state;
}
const int& Object_::get_time_slice_cnt() const{
	return time_slice_cnt;
}
const int& Object_::get_sleep_time() const{
	return sleep_time;
}
const bool& Object_::get_started() const{
	return started;
}

const int& Object_::get_imgID() const{
	return imgID;
}
cocos2d::Sprite*& Object_::get_sprite(){
	return this->sprite;
}

void Object_::set_id(const int& id){
	this->id = id;
}
void Object_::set_name(const std::string& name){
	this->name = name;
}
void Object_::set_DB_ID(const int& DB_ID){
	this->DB_ID = DB_ID;
}
void Object_::set_state(const STATE& state){
	this->state = state;
}
void Object_::set_time_slice_cnt(const int& time_slice_cnt){
	this->time_slice_cnt = time_slice_cnt;
}
void Object_::set_sleep_time(const int& sleep_time){
	this->sleep_time = sleep_time;
}
void Object_::set_started(const bool &started){
	this->started = started;
}
void Object_::set_imgID(const int& imgID){
	this->imgID = imgID;
}