#include "TouchScene.h"
#include <hash_map>

cocos2d::Scene* TouchScene::createScene()
{
    auto scene = cocos2d::Scene::create();
    auto layer = TouchScene::create();
    scene->addChild(layer);
	scene->addChild(Object_::objectLayer);
	Object_::objectLayer->setScaleX(0.8f);
	Object_::objectLayer->setScaleY(0.8f);
	Object_::objectLayer->setPositionX(SIZE_OF_BOARD_CELL_X/2);
	Object_::objectLayer->setPositionY(SIZE_OF_GLWIN_HEIGHT*0.2 + SIZE_OF_BOARD_CELL_Y/2);
	return scene;
}

bool TouchScene::init()
{
     if ( !cocos2d::Layer::init() )
    {
        return false;
    }   
	
	DB =new DBClass();
	this->gamecontroller = new GameController(this, DB);
	this->schedule(schedule_selector(TouchScene::gameLogic), SCHEDULE_TIME);
	
	auto listener = cocos2d::EventListenerTouchOneByOne::create();
 
    // 핸들링된 터치 이벤트를 터치 이벤트 array에서 지우겠다는 의미이다.
     listener->setSwallowTouches(true);
 
     listener->onTouchBegan = CC_CALLBACK_2(TouchScene::onTouchBegan, this);
     listener->onTouchMoved = CC_CALLBACK_2(TouchScene::onTouchMoved, this);
     listener->onTouchCancelled = CC_CALLBACK_2(TouchScene::onTouchCancelled, this);
     listener->onTouchEnded = CC_CALLBACK_2(TouchScene::onTouchEnded, this);
 
    // 터치리스너의 우선순위를 (노드가) 화면에 그려진 순서대로 한다.
     _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//auto gold_l = cocos2d::Label::createWithSystemFont("GOLD: ", "Thonburi", 34, cocos2d::Size(150, 150), cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::CENTER);
	
   return true;
}


void TouchScene::gameLogic(float dt){
	gamecontroller->run();
}


bool TouchScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event){
	cocos2d::log("Mouse Began");
	return true;
}
void TouchScene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event){
	cocos2d::log("Mouse Moved");
}
void TouchScene::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event){
	cocos2d::log("Mouse Cancel");

}
void TouchScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event *unused_event){
	cocos2d::log("Mouse End");

}