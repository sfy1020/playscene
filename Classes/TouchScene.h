#pragma once
#include "cocos2d.h"
#include "Object_.h"
#include "CharacterCommon.h"
#include "DBClass.h"
#include "GameController.h"


class TouchScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
	void gameLogic(float dt);
    CREATE_FUNC(TouchScene);

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event *unused_event);
	

private:
	DBClass* DB;
	GameController* gamecontroller;
	cocos2d::Label* labelTouchInfo;

};