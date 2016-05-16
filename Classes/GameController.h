#ifndef WIN_CONTROLLER_GL_H
#define WIN_CONTROLLER_GL_H

#include "GraphicClass.h"
#include "Unit.h"
#include "SoundClass.h"
#include "GraphicClass.h"
#include "DBClass.h"
#include "cocos2d.h"


class GameController{
private:
	cocos2d::Layer* view;	//PlayScene
	std::queue<int> ID_making_queue;			//ID 생성 큐
	int targetID;			//적의 타겟 id
	int current_clickID;	//현재 클릭중인 ID

	DWORD dwStartTick;		// 적 소환 간격시간 관련
	bool enemyCreateFlag;

	int gold;				// gold 관련
	int life;				// 라이프 관련
	bool startFlag;			// 스테이지 관련
	int currentMapID;
	int currentEnemyCount;
	int currentStage;
	int currentWave;		// wave 관련
	cocos2d::Label* waveValueLabel;

public:			//constructor & destructor
	GameController(cocos2d::Layer* view);
    ~GameController();

public:			//own method		
	void run();										//모든 게임 진행
	int IDmaker();									//고유 id 생성
	void deleteObject_(int deleteID, CONTROLLER dieType);	//대상 삭제
	void createObject_(int createID, int madeID, int x, int y);		//대상 생성
	void decodeMSG(int fromID, int toID, CONTROLLER msg);	//command 해석
	void makeEnemy(int stageID);					//적 생성

	Unit* click(int x, int y, PANEL panel);			//click 시 gameController에서의 작업
	void clickMove(int x, int y, PANEL panel);
	void clickRelease(int x, int y, PANEL panel);
	Unit* rightClick(int x, int y, PANEL panel);			//rightclick 시 gameController에서의 작업

	void goldValUpdate(int gold);					//User value
	void lifeValUpdate(int life);
	void enemyCountValUpdate(int enemyCount);
	void stageValUpdate(int stage);
	void waveValUpdate(int wave);

	void nameInfoUpdate(std::string name);			//Object info
	void hpInfoUpdate(int hp, int maxhp);
	void powerInfoUpdate(int power);
	void speedInfoUpdate(int speed);
	void levelInfoUpdate(int level);
	void rangeInfoUpdate(int range);
	void upgradeInfoUpdate();

	void stageChange();				//stage 변경
	void unitUpgrade(int id);		//unit upgrade
	void userLogin(std::string);	//load login data
	void drawTowerRange(Unit *unit, int id, bool how);	//tower 범위 표시

public:		
	//getter & setter
};


#endif
