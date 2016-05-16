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
	std::queue<int> ID_making_queue;			//ID ���� ť
	int targetID;			//���� Ÿ�� id
	int current_clickID;	//���� Ŭ������ ID

	DWORD dwStartTick;		// �� ��ȯ ���ݽð� ����
	bool enemyCreateFlag;

	int gold;				// gold ����
	int life;				// ������ ����
	bool startFlag;			// �������� ����
	int currentMapID;
	int currentEnemyCount;
	int currentStage;
	int currentWave;		// wave ����
	cocos2d::Label* waveValueLabel;

public:			//constructor & destructor
	GameController(cocos2d::Layer* view);
    ~GameController();

public:			//own method		
	void run();										//��� ���� ����
	int IDmaker();									//���� id ����
	void deleteObject_(int deleteID, CONTROLLER dieType);	//��� ����
	void createObject_(int createID, int madeID, int x, int y);		//��� ����
	void decodeMSG(int fromID, int toID, CONTROLLER msg);	//command �ؼ�
	void makeEnemy(int stageID);					//�� ����

	Unit* click(int x, int y, PANEL panel);			//click �� gameController������ �۾�
	void clickMove(int x, int y, PANEL panel);
	void clickRelease(int x, int y, PANEL panel);
	Unit* rightClick(int x, int y, PANEL panel);			//rightclick �� gameController������ �۾�

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

	void stageChange();				//stage ����
	void unitUpgrade(int id);		//unit upgrade
	void userLogin(std::string);	//load login data
	void drawTowerRange(Unit *unit, int id, bool how);	//tower ���� ǥ��

public:		
	//getter & setter
};


#endif
