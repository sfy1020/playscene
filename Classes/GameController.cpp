#include <process.h>                       
#include "GameController.h"
#include "CharacterCommon.h"
#include "StructureCommon.h"
#include "Tower.h"
#include "SkillBase.h"
#include "DamagedEffect.h"
#include "TowerCommon.h"
#include "SkillDirect.h"
#include "SkillSplash.h"
#include "SkillDirectSplash.h"
#include "SkillApproach.h"
#include "CharacterFly.h"
#include "LoginScene.h"
#include "Map_.h"
#include "Slow.h"
#include "Poison.h"
#include "Stun.h"
#include "PlayScene.h"
#include "LoadingScene.h"
#include "RecordScene.h"


GameController::GameController(cocos2d::Layer* view) 
	: view(view), current_clickID(-1), currentMapID(MAP_COMMON+4)
{
	//wave label 생성
	auto wave_l = cocos2d::Label::createWithSystemFont("WAVE", "SF Action Man", 24, cocos2d::Size(150, 150), cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::CENTER);
	wave_l->setPosition(cocos2d::Point(900, 20));
	wave_l->setColor(cocos2d::Color3B::WHITE);
	view->addChild(wave_l);

	waveValueLabel = cocos2d::Label::createWithSystemFont("8", "SF Action Man", 24, cocos2d::Size(150, 150), cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::CENTER);
	waveValueLabel->setPosition(cocos2d::Point(1030, 20));
	waveValueLabel->setColor(cocos2d::Color3B::WHITE);
	view->addChild(waveValueLabel);

	startFlag = false;						//game setting
	dwStartTick = GetTickCount();
	enemyCreateFlag = true;

	lifeValUpdate(50);						//label setting
	goldValUpdate(1000);
	waveValUpdate(9);
	enemyCountValUpdate(0);
	
	for(int i=1; i<MAX_OBJECT+1; i++){		//유일한 id를 위해 초기화
		ID_making_queue.push(i);
	}
}

GameController::~GameController(){
	for (auto e : Object_::all){
		delete (e.second);
	}
}


void GameController::run(){
	//자기만의 기능
	int fromID = 0;
	int toID = 0;
	CONTROLLER msg = CONTROLLER::EMPTY;
	while (!Object_::mainQ.empty()){
		fromID = Object_::mainQ.front().fromID;
		toID = Object_::mainQ.front().toID;
		msg = Object_::mainQ.front().msg;
		Object_::mainQ.pop();
		decodeMSG(fromID, toID, msg);
	}

	for (auto e : Object_::all)
		e.second->run();


	if ((!startFlag) && ((int)(GetTickCount() - dwStartTick) < 2000 + (currentWave * 1000)))
		return;

	if (GetTickCount() - dwStartTick >= 500 * (1 - (1 / (double)(currentWave * 10))))
	{
		enemyCreateFlag = true;
		dwStartTick = GetTickCount();
	}

	if (startFlag && enemyCreateFlag)
	{
		makeEnemy(currentMapID);
		enemyCreateFlag = false;
	}

	if (!startFlag && currentEnemyCount == 0)  // wave clear
	{
		startFlag = true;
		waveValUpdate(currentWave + 1);
	}

	if (currentWave == MAX_WAVE_NUM+1)  // stage change
		stageChange();
}

void GameController::deleteObject_(int deleteID, CONTROLLER dieType){					//deleteID가 삭제됨
	auto Find = Object_::all.find(deleteID);

	if (Find == Object_::all.end()){
		EXCEPTION2("Object_ is not in hash", deleteID)
			return;
	}

	if (OBJECT(Find->second->get_DB_ID()) == CHARACTER)
	{
		if (dieType == CONTROLLER::DELETE)  // 타워가 죽임
		{
			Character* died = dynamic_cast<Character*>(Find->second);
			goldValUpdate(gold + died->get_gold());
		}
		else if (dieType == CONTROLLER::ARRIVED)  // 타겟에 도착
		{
			life -= 1;
			lifeValUpdate(life);
		}
		enemyCountValUpdate(currentEnemyCount - 1);
	}
	else if (OBJECT(Find->second->get_DB_ID()) == TOWER)
	{

		if (dieType == CONTROLLER::SELLED)
		{
			Tower* tower = dynamic_cast<Tower*>(Find->second);
			goldValUpdate(gold + tower->get_cost() * 0.8f);

		}
	}
	delete Find->second;
	Object_::all.erase(deleteID);

	if (life <= 0)
	{
		auto recordscene = RecordScene::createScene();
		TransitionScene* record = TransitionFade::create(1.0f, recordscene, Color3B::WHITE);
		Director::getInstance()->replaceScene(record);
		//Director::getInstance()->popScene();
	}
}

void GameController::createObject_(int createID, int madeID, int x, int y){		//createID가 madeID로부터 만들어짐
	int id=0;
	auto made = Object_::all.find(madeID);

	//CHARACTER
	if(OBJECT(createID) == CHARACTER){

		if(TYPE(createID) == CHARACTER_COMMON){
			id = IDmaker();
			Object_::all.emplace(id, new CharacterCommon(*dynamic_cast<CharacterDBdata*>(Object_::DBmanager.get_Object_DBdata(createID)), id, x, y, DIRECTION::LEFT, targetID));
		}else if(TYPE(createID) == CHARACTER_FLY){
			id = IDmaker();
			Object_::all.emplace(id, new CharacterFly(*dynamic_cast<CharacterDBdata*>(Object_::DBmanager.get_Object_DBdata(createID)), id, x, y, DIRECTION::LEFT, targetID));
		}else{
			EXCEPTION2("not valid ID!(in CHARACTER)",createID);
		}

	//SKILL
	}else if(OBJECT(createID) == SKILL){
		if(made == Object_::all.end()){
			EXCEPTION2("Object_ is not in hash",createID);
			return;
		}
		Unit* unit = dynamic_cast<Unit*>(made->second);
		int gx = unit->get_gx();
		int gy;
		if(OBJECT(unit->get_DB_ID()) == TOWER)
			gy = unit->get_gy() + (unit->get_sprite()->getBoundingBox().getMaxY() - unit->get_sprite()->getBoundingBox().getMinY()) / 2;
		else
			gy = unit->get_gy();
		int level = unit->get_level();

		if(TYPE(createID) == SKILL_BASE){
			int targetID = unit->get_targetID();
			int damage = unit->get_damage();
			id = IDmaker();
			Object_::all.emplace(id, new SkillBase(*dynamic_cast<SkillDBdata*>(Object_::DBmanager.get_Object_DBdata(createID)), id, gx, gy, targetID, damage, level));
		
		}else if(TYPE(createID) == DAMGED_EFFECT){
			int targetID = unit->get_id();
			int damage = 0;
			id = IDmaker();
			Object_::all.emplace(id, new DamagedEffect(*dynamic_cast<SkillDBdata*>(Object_::DBmanager.get_Object_DBdata(createID)), id, gx, gy, targetID, damage, level));
		
		}else if(TYPE(createID) == SKILL_DIRECT){
			int targetID = unit->get_targetID();
			int damage = unit->get_damage();
			id = IDmaker();
			Object_::all.emplace(id, new SkillDirect(*dynamic_cast<SkillDBdata*>(Object_::DBmanager.get_Object_DBdata(createID)), id, gx, gy, targetID, damage, level));
		
		}else if(TYPE(createID) == SKILL_SPLASH){
			int targetID = unit->get_targetID();
			int damage = unit->get_damage();
			id = IDmaker();
			Object_::all.emplace(id, new SkillSplash(*dynamic_cast<SkillDBdata*>(Object_::DBmanager.get_Object_DBdata(createID)), id, gx, gy, targetID, damage, level));
		
		}else if(TYPE(createID) == SKILL_DIRECTSPLASH){
			int targetID = unit->get_targetID();
			int damage = unit->get_damage();
			id = IDmaker();
			Object_::all.emplace(id, new SkillDirectSplash(*dynamic_cast<SkillDBdata*>(Object_::DBmanager.get_Object_DBdata(createID)), id, gx, gy, targetID, damage, level));
		
		}else if(TYPE(createID) == SKILL_APPROACH){
			int targetID = unit->get_targetID();
			int damage = unit->get_damage();
			int range = unit->get_range();
			id = IDmaker();
			Object_::all.emplace(id, new SkillApproach(*dynamic_cast<SkillDBdata*>(Object_::DBmanager.get_Object_DBdata(createID)), id, gx, gy, targetID, damage, level, range));
		
		}else if (TYPE(createID) == SLOW){
			int targetID = unit->get_id();
			int damage = 0;
			id = IDmaker();
			Object_::all.emplace(id, new Slow(*dynamic_cast<MesmerizeDBdata*>(Object_::DBmanager.get_Object_DBdata(createID)), id, gx, gy, targetID, damage, level));

		}else if (TYPE(createID) == POISON){
			int targetID = unit->get_id();
			int damage = 0;
			id = IDmaker();
			Object_::all.emplace(id, new Poison(*dynamic_cast<MesmerizeDBdata*>(Object_::DBmanager.get_Object_DBdata(createID)), id, gx, gy, targetID, damage, level));

		}else if (TYPE(createID) == STUN){
			int targetID = unit->get_id();
			int damage = 0;
			id = IDmaker();
			Object_::all.emplace(id, new Stun(*dynamic_cast<MesmerizeDBdata*>(Object_::DBmanager.get_Object_DBdata(createID)), id, gx, gy, targetID, damage, level));

		}else {
			EXCEPTION2("not valid ID!(in SKILL)",createID);
		}
	//MAP
	}else if (OBJECT(createID) == MAP){
		int id = 0;
		int struct_DB_ID;
		int struct_x, struct_y;

		if (TYPE(createID) == MAP_COMMON){
			MapDBdata maptemp = *dynamic_cast<MapDBdata*>(Object_::DBmanager.get_Object_DBdata(createID));
			id = IDmaker();
			Object_::all.emplace(id, new Map_(maptemp, id));
			
			for (auto e : maptemp.struct_data){
				id = IDmaker();
				struct_DB_ID = e.first;
				struct_y = e.second.first;
				struct_x = e.second.second;
				Object_::all.emplace(id, new StructureCommon(*dynamic_cast<StructureDBdata*>(Object_::DBmanager.get_Object_DBdata(struct_DB_ID)), id, struct_x, struct_y));
				if (struct_DB_ID == 6010999){		//potal이면
					targetID = id;
				}
			}


			for (int i = 0; i<BOARD_Y; i++){
				for (int j = 0; j<BOARD_X; j++){
					if (maptemp.road_board[i][j] <= 0)
						Object_::board[i][j] = 0;
					else
						Object_::board[i][j] = maptemp.road_board[i][j];
				}
			}

		}else{
			EXCEPTION2("not valid ID!(in STRUCTURE)", createID);
		}
	//STRUCTURE
	}else if(OBJECT(createID) == STRUCTURE){
		if (Object_::board[x][y] <= 0){
			EXCEPTION("board already has Object!");
		}else if(TYPE(createID) == STRUCTURE_COMMON){
			id = IDmaker();
			Object_::all.emplace(id, new StructureCommon(*dynamic_cast<StructureDBdata*>(Object_::DBmanager.get_Object_DBdata(createID)), id, x, y));
		}else{
			EXCEPTION2("not valid ID!(in STRUCTURE)",createID);
		}

	//TOWER
	}else if(OBJECT(createID) == TOWER){
		if (Object_::board[y][x] <=	0){
			EXCEPTION("board already has Object!");
		}else if (TYPE(createID) == TOWER_COMMON){
			TowerDBdata towerData = *dynamic_cast<TowerDBdata*>(Object_::DBmanager.get_Object_DBdata(createID));
			if (this->gold < towerData.cost){
				EXCEPTION("not enough gold!");
				return;
			}
			id = IDmaker();
			Object_::all.emplace(id, new TowerCommon(towerData, id, x, y, 0));
			goldValUpdate(this->gold - towerData.cost);
		}else{
			EXCEPTION2("not valid ID!(in TOWER)",createID);
		}

	//ITEM
	}else if(OBJECT(createID) == ITEM){
		
	}else{
		EXCEPTION2("not valid ID!",createID);
	}
}


void GameController::decodeMSG(int fromID, int toID, CONTROLLER msg){
	if (msg == CONTROLLER::CREATE){
		createObject_(toID, fromID, 0, 0);

	}else if (msg == CONTROLLER::DELETE){
		deleteObject_(toID, CONTROLLER::DELETE);					//대상을 삭제

	}else if (msg == CONTROLLER::ARRIVED){
		deleteObject_(toID, CONTROLLER::ARRIVED);					//대상을 삭제

	}else if (msg == CONTROLLER::SELLED){
		deleteObject_(toID, CONTROLLER::SELLED);					//대상을 삭제

	}else if (msg == CONTROLLER::TOWER_LEVELUP){					//tower upgrade시 event
		auto iter = Object_::all.find(toID);
		if (iter == Object_::all.end()){
			EXCEPTION2("no Id", toID)
		}else{
			if (OBJECT(iter->second->get_DB_ID()) == TOWER){	//label 갱신
				auto tower = dynamic_cast<Tower*>(iter->second);
				nameInfoUpdate(tower->get_name());
				hpInfoUpdate(tower->get_hp(), tower->get_maxhp());
				powerInfoUpdate(tower->get_damage());
				speedInfoUpdate(tower->get_speed());
				levelInfoUpdate(tower->get_level());
				rangeInfoUpdate(tower->get_range());
			}
		}
	}else if (msg == CONTROLLER::CHARACTER_DAMAGED){				//character 타격 시 event
		auto iter = Object_::all.find(toID);
		if (iter == Object_::all.end()){
			EXCEPTION2("no Id", toID)
		}else{
			if (OBJECT(iter->second->get_DB_ID()) == CHARACTER && toID == current_clickID){		//label 갱신
				auto character = dynamic_cast<Character*>(iter->second);
				nameInfoUpdate(character->get_name());
				hpInfoUpdate(character->get_hp(), character->get_maxhp());
				powerInfoUpdate(character->get_damage());
				speedInfoUpdate(character->get_speed());
				levelInfoUpdate(character->get_level());
				rangeInfoUpdate(character->get_range());
			}
		}
	}
}

int GameController::IDmaker(){
	int id = -1;
	if(!ID_making_queue.empty()){
		id = ID_making_queue.front();
		ID_making_queue.pop();
		ID_making_queue.push(id);
	}
	return id;
}
void GameController::makeEnemy(int stageID)
{
	MapDBdata* stage = dynamic_cast<MapDBdata*>(Object_::DBmanager.get_Object_DBdata(stageID));

	static int totalCnt = 0;
	static int index = 0;
	static int currentCnt = 0;

	if (stage->enemyID_List.size() - 1 > index)
	{
		if (currentCnt >= stage->enemyID_List[index].second * ((float)currentWave / 2))  // 특정 enemy의 갯수만큼
		{
			index++;
			currentCnt = 0;
		}
		int scatterx = P(0, 2) - 1;
		int scattery = P(0, 2) - 1;
		createObject_(stage->enemyID_List[index].first, 1, stage->startX + scatterx, stage->startY + scattery);
		totalCnt++;
		currentCnt++;
		enemyCountValUpdate(currentEnemyCount + 1);   // 현재 맵에 있는 적 수
	}
	else  // enemy들을 모두 출력했을 때
	{
		dwStartTick = GetTickCount();
		startFlag = false;
		totalCnt = 0;
		index = 0;
		currentCnt = 0;
	}
}


Unit* GameController::click(int x, int y, PANEL panel){
	if (panel == PANEL::IN1){
		Unit *unit = nullptr;
		float xsize,ysize;

		for (auto e : Object_::all){
			if (OBJECT(e.second->get_DB_ID()) == TOWER || OBJECT(e.second->get_DB_ID()) == CHARACTER){
				unit = dynamic_cast<Unit*>(e.second);
				xsize = (unit->get_sprite()->getBoundingBox().getMaxX() - unit->get_sprite()->getBoundingBox().getMinX())*SCALE_OF_OBJECT_LAYER_WIDTH;
				ysize = (unit->get_sprite()->getBoundingBox().getMaxY() - unit->get_sprite()->getBoundingBox().getMinY())*SCALE_OF_OBJECT_LAYER_HEIGHT;

				if ((x >= unit->get_sprite()->getBoundingBox().getMinX()*SCALE_OF_OBJECT_LAYER_WIDTH
					&&x <= unit->get_sprite()->getBoundingBox().getMinX()*SCALE_OF_OBJECT_LAYER_WIDTH + xsize + SIZE_OF_BOARD_CELL_X / 2)
					&&
					(y >= unit->get_sprite()->getBoundingBox().getMinY()*SCALE_OF_OBJECT_LAYER_HEIGHT + SIZE_OF_GLWIN_HEIGHT*(1 - SCALE_OF_OBJECT_LAYER_HEIGHT) + ysize*(1 - SCALE_OF_OBJECT_LAYER_HEIGHT)
					&& y <= unit->get_sprite()->getBoundingBox().getMinY()*SCALE_OF_OBJECT_LAYER_HEIGHT + SIZE_OF_GLWIN_HEIGHT*(1 - SCALE_OF_OBJECT_LAYER_HEIGHT) + ysize + SIZE_OF_BOARD_CELL_Y / 2)){
					break;
				}
				unit = nullptr;
			}
		}
		if (unit){
			current_clickID = unit->get_id();
			unit->get_sprite()->setColor(cocos2d::Color3B(150, 150, 150));
			if (OBJECT(unit->get_DB_ID()) == TOWER){
				drawTowerRange(unit, 0, true);
				upgradeInfoUpdate();
			}
		}
		return unit;
	}else if (panel == PANEL::IN3){
		return nullptr;
	}else if (panel == PANEL::IN4){
		return nullptr;
	}else if (panel == PANEL::IN5){
		return nullptr;
	}else if (panel == PANEL::IN6){
		return nullptr;
	}else if (panel == PANEL::IN7){
		return nullptr;
	}else{
		return nullptr;
	}
}

Unit* GameController::rightClick(int x, int y, PANEL panel){
	if (panel == PANEL::IN1){
		Unit *unit = nullptr;
		float xsize, ysize;

		for (auto e : Object_::all){
			if (OBJECT(e.second->get_DB_ID()) == TOWER || OBJECT(e.second->get_DB_ID()) == CHARACTER){
				unit = dynamic_cast<Unit*>(e.second);
				xsize = (unit->get_sprite()->getBoundingBox().getMaxX() - unit->get_sprite()->getBoundingBox().getMinX())*SCALE_OF_OBJECT_LAYER_WIDTH;
				ysize = (unit->get_sprite()->getBoundingBox().getMaxY() - unit->get_sprite()->getBoundingBox().getMinY())*SCALE_OF_OBJECT_LAYER_HEIGHT;

				if ((x >= unit->get_sprite()->getBoundingBox().getMinX()*SCALE_OF_OBJECT_LAYER_WIDTH
					&&x <= unit->get_sprite()->getBoundingBox().getMinX()*SCALE_OF_OBJECT_LAYER_WIDTH + xsize + SIZE_OF_BOARD_CELL_X / 2)
					&&
					(y >= unit->get_sprite()->getBoundingBox().getMinY()*SCALE_OF_OBJECT_LAYER_HEIGHT + SIZE_OF_GLWIN_HEIGHT*(1 - SCALE_OF_OBJECT_LAYER_HEIGHT) + ysize*(1 - SCALE_OF_OBJECT_LAYER_HEIGHT)
					&& y <= unit->get_sprite()->getBoundingBox().getMinY()*SCALE_OF_OBJECT_LAYER_HEIGHT + SIZE_OF_GLWIN_HEIGHT*(1 - SCALE_OF_OBJECT_LAYER_HEIGHT) + ysize + SIZE_OF_BOARD_CELL_Y / 2)){
					break;
				}
				unit = nullptr;
			}
		}
		
		return unit;
	}
	else if (panel == PANEL::IN3){
		return nullptr;
	}
	else if (panel == PANEL::IN4){
		return nullptr;
	}
	else if (panel == PANEL::IN5){
		return nullptr;
	}
	else if (panel == PANEL::IN6){
		return nullptr;
	}
	else if (panel == PANEL::IN7){
		return nullptr;
	}
	else{
		return nullptr;
	}
}

void GameController::clickMove(int x, int y, PANEL panel){
	if (panel == PANEL::IN1){
		//std::cout << "move game1";
	}else if (panel == PANEL::IN3){
	}else if (panel == PANEL::IN4){
	}else if (panel == PANEL::IN5){
	}else if (panel == PANEL::IN6){
	}else if (panel == PANEL::IN7){
	}else{
	}
}

void GameController::clickRelease(int x, int y, PANEL panel){
	if (panel == PANEL::IN1){
		auto unit = Object_::all.find(current_clickID);
		if (unit == Object_::all.end()){
			EXCEPTION2("NONE OBJECT CLICKED", current_clickID)
		}else{
			unit->second->get_sprite()->setColor(cocos2d::Color3B::WHITE);
		}
		drawTowerRange(nullptr, CIRCLE_RANGE_ID, false);
	}
	else if (panel == PANEL::IN3){
	}
	else if (panel == PANEL::IN4){
	}
	else if (panel == PANEL::IN5){
	}
	else if (panel == PANEL::IN6){
	}
	else if (panel == PANEL::IN7){
	}
	else{
	}
}

void GameController::goldValUpdate(int gold){		//User Value Update
	this->gold = gold;
	char buffer[LABEL_RADIX];
	_itoa_s(gold, buffer, LABEL_RADIX);
	auto temp = dynamic_cast<PlayScene*>(this->view);
	temp->get_ti_gold()->setString(buffer);
}
void GameController::lifeValUpdate(int life){
	this->life = life;
	char buffer[LABEL_RADIX];
	_itoa_s(life, buffer, LABEL_RADIX);
	auto temp = dynamic_cast<PlayScene*>(this->view);
	temp->get_ti_life()->setString(buffer);
}
void GameController::enemyCountValUpdate(int enemyCount){
	this->currentEnemyCount = enemyCount;
	char buffer[LABEL_RADIX];
	_itoa_s(enemyCount, buffer, LABEL_RADIX);
	auto temp = dynamic_cast<PlayScene*>(this->view);
	temp->get_ti_enemy()->setString(buffer);
}
void GameController::stageValUpdate(int stage){
	this->currentStage = stage;
	char buffer[LABEL_RADIX];
	_itoa_s(stage, buffer, LABEL_RADIX);
	auto temp = dynamic_cast<PlayScene*>(this->view);
	temp->get_ti_stage()->setString(buffer);
}
void GameController::waveValUpdate(int wave){
	this->currentWave = wave;
	char buffer[LABEL_RADIX];
	_itoa_s(wave, buffer, LABEL_RADIX);
	auto temp = dynamic_cast<PlayScene*>(this->view);
	waveValueLabel->setString(buffer);
}

void GameController::nameInfoUpdate(std::string name){		//Object info Update
	auto temp = dynamic_cast<PlayScene*>(this->view);
	temp->get_ch_name()->setString(name);
}
void GameController::hpInfoUpdate(int hp, int maxhp){
	char buffer[LABEL_RADIX];
	std::string hp_label;
	_itoa_s(hp, buffer, LABEL_RADIX);
	hp_label = buffer;
	_itoa_s(maxhp, buffer, LABEL_RADIX);
	hp_label = hp_label + "/" + buffer;
	auto temp = dynamic_cast<PlayScene*>(this->view);
	temp->get_ti_hp()->setString(hp_label);
}
void GameController::powerInfoUpdate(int power){
	char buffer[LABEL_RADIX];
	_itoa_s(power, buffer, LABEL_RADIX);
	auto temp = dynamic_cast<PlayScene*>(this->view);
	temp->get_ti_power()->setString(buffer);
}
void GameController::speedInfoUpdate(int speed){
	char buffer[LABEL_RADIX];
	_itoa_s(speed, buffer, LABEL_RADIX);
	auto temp = dynamic_cast<PlayScene*>(this->view);
	temp->get_ti_speed()->setString(buffer);
}
void GameController::levelInfoUpdate(int level){
	char buffer[LABEL_RADIX];
	_itoa_s(level, buffer, LABEL_RADIX);
	auto temp = dynamic_cast<PlayScene*>(this->view);
	temp->get_ti_level()->setString(buffer);
}
void GameController::rangeInfoUpdate(int range){
	char buffer[LABEL_RADIX];
	_itoa_s(range, buffer, LABEL_RADIX);
	auto temp = dynamic_cast<PlayScene*>(this->view);
	temp->get_ti_range()->setString(buffer);
}
void GameController::upgradeInfoUpdate(){
	if (current_clickID == -1)return;
	auto iter = Object_::all.find(current_clickID);
	if (iter == Object_::all.end()){
		EXCEPTION2("not valid id", current_clickID)
		return;
	}
	if (OBJECT(iter->second->get_DB_ID()) == TOWER){
		auto tower = dynamic_cast<Tower*>(iter->second);
		//tower
		char buffer[LABEL_RADIX];
		_itoa_s((tower->get_cost()*tower->get_level())/2, buffer, LABEL_RADIX);
		auto temp = dynamic_cast<PlayScene*>(this->view);
		temp->get_bt_upgrade()->setTitleText("UPGRADE (" + std::string(buffer) + ")");
	}
}

void GameController::stageChange(){

Director::getInstance()->pushScene(LoadingScene::createScene());

	waveValUpdate(1);

	LoginDBdata* userData = dynamic_cast<LoginDBdata*>(Object_::DBmanager.get_LoginDB().getCurrentUser());

	// stage 증가
	currentMapID++;
	stageValUpdate(currentStage + 1);

	userData->stage = currentStage;
	Object_::DBmanager.get_LoginDB().set_User_DBdata(userData->DB_ID,userData->stage);

	Object_::all.clear(); // 모든 객체 삭제
	Object_::objectLayer->removeAllChildrenWithCleanup(true);

	createObject_(currentMapID, -1, 0, 0);
	MapDBdata* stage = dynamic_cast<MapDBdata*>(Object_::DBmanager.get_Object_DBdata(currentMapID));
}

void GameController::unitUpgrade(int id){
	auto temp = Object_::all.find(id);
	if (temp == Object_::all.end()){
		EXCEPTION2("no id in hash", id)
	}else{
		if (OBJECT(temp->second->get_DB_ID()) == TOWER){
			auto tower = dynamic_cast<Tower*>(temp->second);
			tower->levelUp();
			upgradeInfoUpdate();
		}
	}
}

void GameController::drawTowerRange(Unit *unit, int id, bool how){
	if (how){
		cocos2d::DrawNode *circle = cocos2d::DrawNode::create();
		float sx = (float)unit->get_gx();
		float sy = (float)unit->get_gy();
		float r = unit->get_range();
		cocos2d::Color4F color = cocos2d::Color4F::WHITE;
		circle->drawCircle(Vec2(sx, sy), r, (float)(2 * M_PI), 40, false, color);

		Object_::objectLayer->addChild(circle);
		circle->setTag(CIRCLE_RANGE_ID);
	}else{
		Object_::objectLayer->removeChildByTag(id);
	}
}

void GameController::userLogin(std::string id){
	auto iter = Object_::DBmanager.get_LoginDB().get_loginDB().find(id);
	if (iter == Object_::DBmanager.get_LoginDB().get_loginDB().end()){
		EXCEPTION("no login id in hash")
	}
	currentMapID = MAP_COMMON + (*iter->second).stage;
	createObject_(currentMapID, -1, 0, 0);
	stageValUpdate((*iter->second).stage);
}