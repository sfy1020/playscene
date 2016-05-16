#include "DBClass.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
DBClass::DBClass(){
	characterDB_init();
	towerDB_init();
	skillDB_init();
	mapDB_init();
	structureDB_init();
}

DBClass::~DBClass(){
	for (auto e : objectDB){
		delete (e.second);
	}
}

void DBClass::characterDB_init(){
	std::ifstream characterDBtxt("characterDB.txt");
	std::string str;

	
	int DB_ID, maxhp, maxmp, damage, speed, range, gold,
		imgID, attack_frame, skill_frame, attack_imgID, skill_imgID, attack_soundID, skill_soundID,
	    die_frame, move_frame, die_imgID, move_imgID, die_soundID, move_soundID;
	std::string name;

	std::getline(characterDBtxt, str);	//盖 拉临 力芭
	while(1){
		characterDBtxt>>str;
		DB_ID = atoi(str.c_str());
		if(characterDBtxt.eof())break;

		characterDBtxt >> name >> maxhp >> maxmp >> damage >> speed >> range >> gold >> attack_frame >> skill_frame >> die_frame >> move_frame >> imgID >> attack_imgID >> skill_imgID >> die_imgID >> move_imgID >> attack_soundID >> skill_soundID >> die_soundID >> move_soundID;
		if(TYPE(DB_ID) == CHARACTER_COMMON){
			objectDB.emplace(DB_ID, new CharacterDBdata(DB_ID, name, maxhp, maxmp, damage, speed, range, gold, imgID, attack_frame, skill_frame, attack_imgID, skill_imgID, attack_soundID, skill_soundID, die_frame, move_frame, die_imgID, move_imgID, die_soundID, move_soundID));
		}else if(TYPE(DB_ID) == CHARACTER_FLY){
			objectDB.emplace(DB_ID, new CharacterDBdata(DB_ID, name, maxhp, maxmp, damage, speed, range, gold, imgID, attack_frame, skill_frame, attack_imgID, skill_imgID, attack_soundID, skill_soundID, die_frame, move_frame, die_imgID, move_imgID, die_soundID, move_soundID));
		}else{
		}
	}
	characterDBtxt.close();
	
}

void DBClass::towerDB_init(){
	std::ifstream towerDBtxt("towerDB.txt");
	std::string str;

	int DB_ID, maxhp, maxmp, damage, speed, range, cost, imgID,
		attack_frame, skill_frame, attack_imgID, skill_imgID, attack_soundID, skill_soundID,
		die_frame, die_imgID, die_soundID, attackID, skillID;
	std::string name;

	std::getline(towerDBtxt, str);	//盖 拉临 力芭
	while(1){
		towerDBtxt>>str;
		DB_ID = atoi(str.c_str());
		if(towerDBtxt.eof())break;

		towerDBtxt >> name >> maxhp >> maxmp >> damage >> speed >> range >> cost >> attack_frame >> skill_frame >> die_frame >> imgID >> attack_imgID >> skill_imgID >> die_imgID >> attack_soundID >> skill_soundID >> die_soundID >> attackID >> skillID;
		if(TYPE(DB_ID) == TOWER_COMMON){
			objectDB.emplace(DB_ID, new TowerDBdata(DB_ID, name, maxhp, maxmp, damage, speed, range, cost, imgID, attack_frame, skill_frame, die_frame, attack_imgID, skill_imgID, die_imgID, attack_soundID, skill_soundID, die_soundID, attackID, skillID));
		}else{
		}
	}
	towerDBtxt.close();
}

void DBClass::skillDB_init(){
	std::ifstream skillDBtxt("skillDB.txt");
	std::string str;

	int DB_ID, speed, range, imgID, move_frame, move_imgID, move_soundID, damagedEffectID, speed_control, wait_control, continue_damage, life_time;
	std::string name;

	std::getline(skillDBtxt, str);	//盖 拉临 力芭
	while(1){
		skillDBtxt>>str;
		DB_ID = atoi(str.c_str());
		if(skillDBtxt.eof())break;

		skillDBtxt >> name >> speed >> range>> move_frame >> imgID >> move_imgID >> move_soundID >> damagedEffectID;
		if(TYPE(DB_ID) == SKILL_BASE){
			objectDB.emplace(DB_ID, new SkillDBdata(DB_ID, name, speed, range, imgID, move_frame, move_imgID, move_soundID, damagedEffectID));
		}else if(TYPE(DB_ID) == DAMGED_EFFECT){
			objectDB.emplace(DB_ID, new SkillDBdata(DB_ID, name, speed, range, imgID, move_frame, move_imgID, move_soundID, damagedEffectID));
		}else if(TYPE(DB_ID) == SKILL_DIRECT){
			objectDB.emplace(DB_ID, new SkillDBdata(DB_ID, name, speed, range, imgID, move_frame, move_imgID, move_soundID, damagedEffectID));
		}else if(TYPE(DB_ID) == SKILL_SPLASH){
			objectDB.emplace(DB_ID, new SkillDBdata(DB_ID, name, speed, range, imgID, move_frame, move_imgID, move_soundID, damagedEffectID));
		}else if(TYPE(DB_ID) == SKILL_DIRECTSPLASH){
			objectDB.emplace(DB_ID, new SkillDBdata(DB_ID, name, speed, range, imgID, move_frame, move_imgID, move_soundID, damagedEffectID));
		}else if(TYPE(DB_ID) == SKILL_APPROACH){
			objectDB.emplace(DB_ID, new SkillDBdata(DB_ID, name, speed, range, imgID, move_frame, move_imgID, move_soundID, damagedEffectID));
		}else if (TYPE(DB_ID) == SLOW){
			skillDBtxt >> speed_control >> wait_control >> continue_damage >> life_time;
			objectDB.emplace(DB_ID, new MesmerizeDBdata(DB_ID, name, speed, range, imgID, move_frame, move_imgID, move_soundID, damagedEffectID, speed_control, wait_control, continue_damage, life_time));
		}else if (TYPE(DB_ID) == POISON){
			skillDBtxt >> speed_control >> wait_control >> continue_damage >> life_time;
			objectDB.emplace(DB_ID, new MesmerizeDBdata(DB_ID, name, speed, range, imgID, move_frame, move_imgID, move_soundID, damagedEffectID, speed_control, wait_control, continue_damage, life_time));
		}else if (TYPE(DB_ID) == STUN){
			skillDBtxt >> speed_control >> wait_control >> continue_damage >> life_time;
			objectDB.emplace(DB_ID, new MesmerizeDBdata(DB_ID, name, speed, range, imgID, move_frame, move_imgID, move_soundID, damagedEffectID, speed_control, wait_control, continue_damage, life_time));
		}
	}
	skillDBtxt.close();
}


void DBClass::mapDB_init(){
	std::ifstream mapDBtxt("mapDB.txt");
	std::string str;

	std::string mapCountTemp;
	int mapCount;

	int DB_ID, imgID, bgmID;
	std::string name;

	int enemyTotalCount, enemyTypeCount, enemyIdTemp, enemyCountTemp;
	std::vector< std::pair<int, int> > enemyID_List;
	std::pair<int, int> enemyTemp;
	int startX, startY, endX, endY;

	std::vector<std::pair<int, std::pair<int, int> > > struct_data;
	std::pair<int, int> temp;
	int struct_DB_ID;
	int road_board[BOARD_Y][BOARD_X];

	mapDBtxt >> mapCountTemp >> mapCount;
	for (int c = 0; c < mapCount; c++)
	{
		std::getline(mapDBtxt, str);	//盖 拉临 力芭
		std::getline(mapDBtxt, str);	//盖 拉临 力芭
		mapDBtxt >> str;

		DB_ID = atoi(str.c_str());
		
		if (TYPE(DB_ID) == MAP_COMMON){
			mapDBtxt >> name >> imgID >> bgmID >> startX >> startY >> endX >> endY >> enemyTotalCount >> enemyTypeCount;
			for (int i = 0; i < enemyTypeCount; i++)
			{
				mapDBtxt >> enemyIdTemp >> enemyCountTemp;
				enemyTemp.first = enemyIdTemp;
				enemyTemp.second = enemyCountTemp;

				enemyID_List.push_back(enemyTemp);
			}

			mapDBtxt >> str;
			for (int i = 0; i<BOARD_Y; i++){
				for (int j = 0; j<BOARD_X; j++){
					mapDBtxt >> struct_DB_ID;
					if (struct_DB_ID != 0){
						temp.first = BOARD_Y - i - 1;
						temp.second = j;
						struct_data.emplace_back(struct_DB_ID + STRUCTURE_COMMON, temp);
					}
				}
			}

			mapDBtxt >> str;
			for (int i = 0; i<BOARD_Y; i++){
				for (int j = 0; j<BOARD_X; j++){
					mapDBtxt >> road_board[BOARD_Y - i - 1][j];
				}
			}
			objectDB.emplace(DB_ID, new MapDBdata(DB_ID, name, imgID, bgmID, startX, startY, endX, endY, enemyTotalCount, enemyTypeCount, enemyID_List, struct_data, road_board));
		}
		else{
			EXCEPTION("NOT MAP")
		}
		while (!struct_data.empty())struct_data.pop_back();
		while (!enemyID_List.empty())enemyID_List.pop_back();
	}
	mapDBtxt.close();
}


void DBClass::structureDB_init(){
	std::ifstream structureDBtxt("structureDB.txt");
	std::string str;

	int DB_ID, imgID;
	std::string name;

	std::getline(structureDBtxt, str);	//盖 拉临 力芭
	while(1){
		structureDBtxt>>str;
		DB_ID = atoi(str.c_str());
		if(structureDBtxt.eof())break;

		if(TYPE(DB_ID) == STRUCTURE_COMMON){
			structureDBtxt>> name >> imgID;
			objectDB.emplace(DB_ID, new StructureDBdata(DB_ID, name, imgID));
		
		}else{
		}
	}
	structureDBtxt.close();
}

ObjectDBdata* DBClass::get_Object_DBdata(int DB_ID){
	auto iter = objectDB.find(DB_ID);
	if(iter == objectDB.end()){
		EXCEPTION2("Object_ is not in hash",DB_ID);
		return nullptr;
	}else{
		return iter->second;
	}
}

LoginDB& DBClass::get_LoginDB(){
	return loginDB;
}