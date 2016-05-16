#ifndef __CONSTANT__
#define __CONSTANT__
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <chrono>
#include <utility>
#include <memory>

#include <ctime>
#include <cstdlib>
#include <cmath>
#include "cocos2d.h"

#define DEBUG	0
#define EXCEPTION(STR)		if(DEBUG)	cocos2d::log("(NOTIFY : %s) (line : %d), (function : %s)",STR,__LINE__,__FUNCTION__);
#define EXCEPTION2(STR,ID)	if(DEBUG)	cocos2d::log("(NOTIFY : %s) (ID : %d) (line : %d), (function : %s)",STR,ID,__LINE__,__FUNCTION__);

const int SIZE_OF_GLWIN_WIDTH  = 1280;
const int SIZE_OF_GLWIN_HEIGHT = 800;
const int SIZE_OF_BOARD_CELL_X = 50;
const int SIZE_OF_BOARD_CELL_Y = 50;
const int BOARD_X = SIZE_OF_GLWIN_WIDTH / SIZE_OF_BOARD_CELL_X;
const int BOARD_Y = SIZE_OF_GLWIN_HEIGHT / SIZE_OF_BOARD_CELL_Y;
const int DEFAULT_DELAY_TIME = 100;
const int CIRCLE_RANGE_ID = 123456789;
const int MAX_WAVE_NUM = 10;
const int LABEL_RADIX = 10;
const int BIG_INT = 2000000000;
const int MAX_LEVEL = 5;
const int MAX_OBJECT = 100000;

const float SCHEDULE_TIME = 0.01f;
const std::string FONT= "SF Action Man";
const float SCALE_OF_OBJECT_LAYER_WIDTH = 0.8f;
const float SCALE_OF_OBJECT_LAYER_HEIGHT = 0.8f;

#define OBJECT(X) ((X/1000000)*1000000)	//object비교를 위해
#define TYPE(X) ((X/10000)*10000)		//type 비교를 위해
const enum{								//object & type
	OBJECT, UNIT,
	CHARACTER	=	1000000, CHARACTER_COMMON	=	1010000, CHARACTER_FLY	=	1020000,
	SKILL		=	2000000, DAMGED_EFFECT		=	2010000, SKILL_BASE		=	2020000, SKILL_DIRECT = 2030000, SKILL_SPLASH = 2040000, SKILL_DIRECTSPLASH = 2050000, SKILL_APPROACH = 2060000, SLOW = 2070000, POISON = 2080000, STUN = 2090000,
	MAP			=	3000000, MAP_COMMON			=	3010000,
	ITEM		=	4000000,
	TOWER		=	5000000, TOWER_COMMON		=	5010000,
	STRUCTURE	=	6000000, STRUCTURE_COMMON	=	6010000
};
const enum class STATE{								//Object 상태
	MOVE = 0, ATTACK, DIE, TARGET,			//state message
	IMMIDIATE = 10000, BASE					//immidiate state message
};

const enum class DIRECTION{							//direction 상태
	UP = 0, LEFT = 1, RIGHT = 2, DOWN = 3, EMPTY = 0
};
const enum{											//board 상태
	EMPTY = 0, BLOCK = -1
};
const enum class CONTROLLER{						//GameController의 명령어
	CREATE, DELETE, ARRIVED, SELLED, TOWER_LEVELUP, CHARACTER_DAMAGED, EMPTY
};
const enum class PANEL{								//panel 내부에 있는지 판별 flag
	IN1, IN3, IN4, IN5, IN6, IN7
};
const enum class MESMERIZE{							//상태이상 flag
	NONE = 0, SLOW, POISON, STUN
};

const int move_x[4] = {0, -1, 1, 0};	//방향을 위한 변수
const int move_y[4] = {-1, 0, 0, 1};

//상용 method
float square(float x);
float distance2D(float x, float y, float other_x, float other_y);	//거리^2
bool inRange(int x, int y, int other_x, int other_y, int range);	//범위 내에 있는지 판별
DIRECTION getDirection(int sx, int sy, int fx, int fy);				//방향 획득
int P(int a, int b);												//확률 생성
void make_around_position(int &around_x, int &around_y, int target_x, int target_y, int board[BOARD_Y][BOARD_X]);	//빈 공간 탐색
void allPrint(cocos2d::Node * root);								//project tree의 모든 노드 출력

template <typename T>		//hash에서 탐색 후 casting
T objectFinder(int id){
	auto e = Object_::all.find(id);
	if (e == Object_::all.end()){
		EXCEPTION2("Object_ is not in hash", id);
		return nullptr;
	}
	return dynamic_cast<T>(e->second);			//주체에 대한 casting
}

//GameController로의 Message
class Message{
public:
	int fromID;
	int toID;
	CONTROLLER msg;
	Message() :fromID(0), toID(0), msg(CONTROLLER::EMPTY){}
	Message(int fromID, int toID, CONTROLLER msg){
		this->fromID	=	fromID;
		this->toID		=	toID;
		this->msg		=	msg;
	}
	Message(const Message& temp){
		this->fromID	=	temp.fromID;
		this->msg		=	temp.msg;
		this->toID		=	temp.toID;
	}
	Message& operator = (const Message& temp){
		this->fromID	=	temp.fromID;
		this->msg		=	temp.msg;
		this->toID		=	temp.toID;
		return *this;
	}
};


//SoundDB hash의 data type(soundDB.txt로 얻은 데이터를 저장)
class SoundDBdata{	
public:
	int id;
	std::string filename;
	int msg;
	SoundDBdata():id(0),msg(0){}
	SoundDBdata(int id, std::string filename, int msg){
		this->id		=	id;
		this->filename	=	filename;
		this->msg		=	msg;
	}
	SoundDBdata(const SoundDBdata& temp){
		this->id		=	temp.id;
		this->filename	=	temp.filename;
		this->msg		=	temp.msg;
	}
	SoundDBdata& operator = (const SoundDBdata& temp){
		this->id		=	temp.id;
		this->filename	=	temp.filename;
		this->msg		=	temp.msg;
		return *this;
	}
};

//GraphicDB hash의 data type(GraphicDB.txt로 얻은 데이터를 저장)
class GraphicDBdata{
public:
	int id;
	std::string filename;
	float size_x;
	float size_y;
	float angle;

	GraphicDBdata():id(0),filename(""),size_x(0),size_y(0),angle(0){}
	GraphicDBdata(int id, std::string filename, float size_x, float size_y, float angle){
		this->id		=	id;
		this->filename	=	filename;
		this->size_x	=	size_x;
		this->size_y	=	size_y;
		this->angle		=	angle;
	}
	GraphicDBdata(const GraphicDBdata& temp){
		this->id		=	temp.id;
		this->filename	=	temp.filename;
		this->size_x	=	temp.size_x;
		this->size_y	=	temp.size_y;
		this->angle		=	temp.angle;
	}
	GraphicDBdata& operator = (const GraphicDBdata& temp){
		this->id		=	temp.id;
		this->filename	=	temp.filename;
		this->size_x	=	temp.size_x;
		this->size_y	=	temp.size_y;
		this->angle		=	temp.angle;
		return *this;
	}
};

//LoginDB hash의 data type(LoginDB.txt로 얻은 데이터를 저장)
class LoginDBdata{
public:
	std::string DB_ID;
	std::string password;
	int stage;
public:
	LoginDBdata() : DB_ID(0), password(""), stage(0){}
	LoginDBdata(std::string DB_ID, std::string password, int stage){
		this->DB_ID = DB_ID;
		this->password = password;
		this->stage = stage;
	}
	LoginDBdata(const LoginDBdata& temp){
		this->DB_ID = temp.DB_ID;
		this->password = temp.password;
		this->stage = temp.stage;
	}
	LoginDBdata& operator=(const LoginDBdata& temp){
		this->DB_ID = temp.DB_ID;
		this->password = temp.password;
		this->stage = temp.stage;
		return *this;
	}
	virtual void f(){}
};

//ObjectDBdata hash를 구성
class ObjectDBdata{
public:
	int DB_ID;
	std::string name;
	int imgID;
public:
	ObjectDBdata() : DB_ID(0),name(""),imgID(0){}
	ObjectDBdata(int DB_ID, std::string name, int imgID){
		this->DB_ID			=	DB_ID;
		this->name			=	name;
		this->imgID			=	imgID;
	}
	ObjectDBdata(const ObjectDBdata& temp){
		this->DB_ID			=	temp.DB_ID;
		this->name			=	temp.name;
		this->imgID			=	temp.imgID;
	}
	ObjectDBdata& operator=(const ObjectDBdata& temp){
		this->DB_ID			=	temp.DB_ID;
		this->name			=	temp.name;
		this->imgID			=	temp.imgID;
		return *this;
	}
	virtual void f(){}
};

//ObjectDB hash의 data type 중 일부(SkillDB.txt로 얻은 Skill 데이터를 저장)
class SkillDBdata : public ObjectDBdata{
public:
	int speed;
	int range;
	int move_frame;
	int move_imgID;
	int move_soundID;
	int damagedEffectID;
public:
	SkillDBdata():ObjectDBdata(),speed(0),range(0),move_frame(0),move_imgID(0),move_soundID(0),damagedEffectID(0){}
	
	SkillDBdata(int DB_ID, std::string name, int speed, int range, int imgID, int move_frame, int move_imgID, int move_soundID,int damagedEffectID) : ObjectDBdata(DB_ID,name,imgID){
		this->speed				=	speed;
		this->range				=	range;
		this->move_frame		=	move_frame;
		this->move_imgID		=	move_imgID;
		this->move_soundID		=	move_soundID;
		this->damagedEffectID	=	damagedEffectID;
	}

	SkillDBdata(const SkillDBdata& temp) : ObjectDBdata(temp){
		this->speed				=	temp.speed;
		this->range				=	temp.range;
		this->move_frame		=	temp.move_frame;
		this->move_imgID		=	temp.move_imgID;
		this->move_soundID		=	temp.move_soundID;
		this->damagedEffectID	=	temp.move_soundID;
	}

	SkillDBdata& operator=(const SkillDBdata& temp){
		ObjectDBdata::operator=(temp);
		this->speed				=	temp.speed;
		this->range				=	temp.range;
		this->move_frame		=	temp.move_frame;
		this->move_imgID		=	temp.move_imgID;
		this->move_soundID		=	temp.move_soundID;
		this->damagedEffectID	=	temp.move_soundID;
		return *this;
	}
	virtual void f(){}
};

//ObjectDB hash의 data type 중 일부(SkillDB.txt로 얻은 Mesmerize 데이터를 저장)
class MesmerizeDBdata : public SkillDBdata{
public:
	int speed_control;
	int wait_control;
	int continue_damage;
	int life_time;
public:
	MesmerizeDBdata() :SkillDBdata(), speed_control(0), wait_control(0), continue_damage(0), life_time(0){}

	MesmerizeDBdata(int DB_ID, std::string name, int speed, int range, int imgID, int move_frame, int move_imgID, int move_soundID,
		int damagedEffectID, int speed_control, int wait_control, int continue_damage, int life_time)
		: SkillDBdata(DB_ID, name, speed, range, imgID, move_frame, move_imgID, move_soundID, damagedEffectID){
		this->speed_control		=	speed_control;
		this->wait_control		=	wait_control;
		this->continue_damage	=	continue_damage;
		this->life_time			=	life_time;
	}

	MesmerizeDBdata(const MesmerizeDBdata& temp) : SkillDBdata(temp){
		this->speed_control		=	temp.speed_control;
		this->wait_control		=	temp.wait_control;
		this->continue_damage	=	temp.continue_damage;
		this->life_time			=	temp.life_time;
	}

	MesmerizeDBdata& operator=(const MesmerizeDBdata& temp){
		SkillDBdata::operator=(temp);
		this->speed_control		=	temp.speed_control;
		this->wait_control		=	temp.wait_control;
		this->continue_damage	=	temp.continue_damage;
		this->life_time			=	temp.life_time;
		return *this;
	}
	virtual void f(){}
};

//UnitDBdata
class UnitDBdata : public ObjectDBdata{
public:
	int maxhp;
	int maxmp;
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
public:
	UnitDBdata():ObjectDBdata(),maxhp(0),maxmp(0),damage(0),speed(0),range(0),
		attack_frame(0),skill_frame(0),die_frame(0),attack_imgID(0),skill_imgID(0),die_imgID(0),
		attack_soundID(0),skill_soundID(0),die_soundID(0){}
	
	UnitDBdata(int DB_ID, std::string name, int maxhp, int maxmp, int damage, int speed, int range,
		int imgID,int attack_frame, int skill_frame, int die_frame, int attack_imgID, int skill_imgID, int die_imgID,
		int attack_soundID, int skill_soundID, int die_soundID) : ObjectDBdata(DB_ID,name,imgID){

		this->maxhp				=	maxhp;
		this->maxmp				=	maxmp;
		this->damage			=	damage;
		this->speed				=	speed;
		this->range				=	range;
		this->attack_frame		=	attack_frame;
		this->skill_frame		=	skill_frame;
		this->die_frame			=	die_frame;
		this->attack_imgID		=	attack_imgID;
		this->skill_imgID		=	skill_imgID;
		this->die_imgID			=	die_imgID;
		this->attack_soundID	=	attack_soundID;
		this->skill_soundID		=	skill_soundID;
		this->die_soundID		=	die_soundID;
	}

	UnitDBdata(const UnitDBdata& temp) : ObjectDBdata(temp){
		this->maxhp				=	temp.maxhp;
		this->maxmp				=	temp.maxmp;
		this->damage			=	temp.damage;
		this->speed				=	temp.speed;
		this->range				=	temp.range;
		this->attack_frame		=	temp.attack_frame;
		this->skill_frame		=	temp.skill_frame;
		this->die_frame			=	temp.die_frame;
		this->attack_imgID		=	temp.attack_imgID;
		this->skill_imgID		=	temp.skill_imgID;
		this->die_imgID			=	temp.die_imgID;
		this->attack_soundID	=	temp.attack_soundID;
		this->skill_soundID		=	temp.skill_soundID;
		this->die_soundID		=	temp.die_soundID;
	}

	UnitDBdata& operator=(const UnitDBdata& temp){
		ObjectDBdata::operator=(temp);
		this->maxhp				=	temp.maxhp;
		this->maxmp				=	temp.maxmp;
		this->damage			=	temp.damage;
		this->speed				=	temp.speed;
		this->range				=	temp.range;
		this->attack_frame		=	temp.attack_frame;
		this->skill_frame		=	temp.skill_frame;
		this->die_frame			=	temp.die_frame;
		this->attack_imgID		=	temp.attack_imgID;
		this->skill_imgID		=	temp.skill_imgID;
		this->die_imgID			=	temp.die_imgID;
		this->attack_soundID	=	temp.attack_soundID;
		this->skill_soundID		=	temp.skill_soundID;
		this->die_soundID		=	temp.die_soundID;
		return *this;
	}
	virtual void f(){}
};

//ObjectDB hash의 data type 중 일부(CharacterDB.txt로 얻은 Character 데이터를 저장)
class CharacterDBdata : public UnitDBdata{
public:
	int gold;
	int move_frame;
	int move_imgID;
	int move_soundID;
public:
	CharacterDBdata():UnitDBdata(),gold(0),move_frame(0),move_imgID(0),move_soundID(0){}

	CharacterDBdata(int DB_ID, std::string name, int maxhp, int maxmp, int damage, int speed, int range, int gold, int imgID,
		int attack_frame, int skill_frame, int attack_imgID, int skill_imgID, int attack_soundID, int skill_soundID,
		int die_frame, int move_frame, int die_imgID, int move_imgID,int die_soundID, int move_soundID)
		:UnitDBdata(DB_ID, name, maxhp, maxmp, damage, speed, range, imgID, attack_frame, skill_frame, die_frame,
		attack_imgID, skill_imgID, die_imgID, attack_soundID, skill_soundID, die_soundID){
		
		this->gold				=	gold;
		this->move_frame		=	move_frame;
		this->move_imgID		=	move_imgID;
		this->move_soundID		=	move_soundID;
	}

	CharacterDBdata(const CharacterDBdata& temp) : UnitDBdata(temp){
		this->gold				=	temp.gold;
		this->move_frame		=	temp.move_frame;
		this->move_imgID		=	temp.move_imgID;
		this->move_soundID		=	temp.move_soundID;
	}

	CharacterDBdata& operator=(const CharacterDBdata& temp){
		UnitDBdata::operator=(temp);
		this->gold				=	temp.gold;
		this->move_frame		=	temp.move_frame;
		this->move_imgID		=	temp.move_imgID;
		this->move_soundID		=	temp.move_soundID;
		return *this;
	}
	virtual void f(){}
};

//ObjectDB hash의 data type 중 일부(TowerDB.txt로 얻은 Tower 데이터를 저장)
class TowerDBdata : public UnitDBdata{
public:
	int cost;
	int attackID;
	int skillID;
public:
	TowerDBdata():UnitDBdata(),cost(0),attackID(0),skillID(0){}

	TowerDBdata(int DB_ID, std::string name, int maxhp, int maxmp, int damage, int speed, int range, int cost,
		int imgID,int attack_frame, int skill_frame, int die_frame, int attack_imgID, int skill_imgID, int die_imgID,
		int attack_soundID, int skill_soundID, int die_soundID, int attackID, int skillID)
		:UnitDBdata(DB_ID, name, maxhp, maxmp, damage, speed, range, imgID, attack_frame, skill_frame, die_frame,
		attack_imgID, skill_imgID, die_imgID, attack_soundID, skill_soundID, die_soundID){
		
		this->cost			=	cost;
		this->attackID		=	attackID;
		this->skillID		=	skillID;
	}

	TowerDBdata(const TowerDBdata& temp) : UnitDBdata(temp){
		this->cost			=	temp.cost;
		this->attackID		=	temp.attackID;
		this->skillID		=	temp.skillID;
	}

	TowerDBdata& operator=(const TowerDBdata& temp){
		UnitDBdata::operator=(temp);
		this->cost			=	temp.cost;
		this->attackID		=	temp.attackID;
		this->skillID		=	temp.skillID;
		return *this;
	}
	virtual void f(){}
};

//ObjectDB hash의 data type 중 일부(StructureDB.txt로 얻은 Structure 데이터를 저장)
class StructureDBdata : public ObjectDBdata{	
public:

public:
	StructureDBdata():ObjectDBdata(){}
	
	StructureDBdata(int DB_ID, std::string name, int imgID) : ObjectDBdata(DB_ID,name,imgID){
	}

	StructureDBdata(const StructureDBdata& temp) : ObjectDBdata(temp){
	}

	StructureDBdata& operator=(const StructureDBdata& temp){
		ObjectDBdata::operator=(temp);
		return *this;
	}
	virtual void f(){}
};

//ObjectDB hash의 data type 중 일부(MapDB.txt로 얻은 Map 데이터를 저장)
class MapDBdata : public ObjectDBdata{	
public:
	int bgmID;
	int enemyTotalCount, enemyTypeCount;
	std::vector< std::pair<int, int> > enemyID_List;
	int startX, startY, endX, endY;

	std::vector<std::pair<int, std::pair<int, int> > > struct_data;
	int road_board[BOARD_Y][BOARD_X];

public:
	MapDBdata() :ObjectDBdata(){}

	MapDBdata(int DB_ID, std::string name, int imgID, int bgmID, int startX, int startY, int endX, int endY, int enemyTotalCount, int enemyTypeCount, std::vector< std::pair<int, int> > enemyID_List,
		std::vector<std::pair<int, std::pair<int, int> > > struct_data, int road_board[BOARD_Y][BOARD_X])
		: ObjectDBdata(DB_ID, name, imgID){
		this->bgmID = bgmID;
		this->enemyTotalCount = enemyTotalCount;
		this->enemyTypeCount = enemyTypeCount;
		this->enemyID_List = enemyID_List;
		this->startX = startX;
		this->startY = startY;
		this->endX = endX;
		this->endY = endY;
		this->struct_data = struct_data;
		for (int i = 0; i<BOARD_Y; i++){
			for (int j = 0; j<BOARD_X; j++){
				this->road_board[i][j] = road_board[i][j];
			}
		}
	}

	MapDBdata(const MapDBdata& temp) : ObjectDBdata(temp){
		this->bgmID = temp.bgmID;
		this->enemyTotalCount = temp.enemyTotalCount;
		this->enemyTypeCount = temp.enemyTypeCount;
		this->enemyID_List = temp.enemyID_List;
		this->startX = temp.startX;
		this->startY = temp.startY;
		this->endX = temp.endX;
		this->endY = temp.endY;
		this->struct_data = temp.struct_data;

		for (int i = 0; i<BOARD_Y; i++){
			for (int j = 0; j<BOARD_X; j++){
				this->road_board[i][j] = temp.road_board[i][j];
			}
		}
	}

	MapDBdata& operator=(const MapDBdata& temp){
		ObjectDBdata::operator=(temp);
		this->bgmID = temp.bgmID;
		this->enemyTotalCount = temp.enemyTotalCount;
		this->enemyTypeCount = temp.enemyTypeCount;
		this->enemyID_List = temp.enemyID_List;
		this->startX = temp.startX;
		this->startY = temp.startY;
		this->endX = temp.endX;
		this->endY = temp.endY;
		this->struct_data = temp.struct_data;

		for (int i = 0; i<BOARD_Y; i++){
			for (int j = 0; j<BOARD_X; j++){
				this->road_board[i][j] = temp.road_board[i][j];
			}
		}
		return *this;
	}
	virtual void f(){}
};

#endif