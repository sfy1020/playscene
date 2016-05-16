#include "LoginScene.h"
#include "OptionLayer.h"
#include "TouchScene.h"
#include "PlayScene.h"
#include "cocostudio\CocoStudio.h"
#include "Object_.h"
#include <iostream>
#include <string>

using namespace cocostudio::timeline;
using namespace ui;
using namespace cocos2d;

cocos2d::Scene* OptionLayer::createScene()
{
    // 'scene' is an autorelease object
	auto scene = cocos2d::Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = OptionLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool OptionLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	auto rootNode = CSLoader::createNode("Setting.csb");
	
    addChild(rootNode);

	panel2 = rootNode->getChildByTag(49);	//3개의 자식

	button1 = dynamic_cast<Button*>(panel2->getChildByTag(34));//continue
	button2 = dynamic_cast<Button*>(panel2->getChildByTag(124));//save
	button3 = dynamic_cast<Button*>(panel2->getChildByTag(146));//quit

	slider1 = dynamic_cast<Slider*>(panel2->getChildByTag(33));//music slider
	slider2 = dynamic_cast<Slider*>(panel2->getChildByTag(32));//sound slider



	button1->addTouchEventListener(CC_CALLBACK_2(OptionLayer::onButton1,this));
	button2->addTouchEventListener(CC_CALLBACK_2(OptionLayer::onButton2,this));
	button3->addTouchEventListener(CC_CALLBACK_2(OptionLayer::onButton3,this));


	slider1->addTouchEventListener(CC_CALLBACK_2(OptionLayer::onSlider1,this));
	slider1->addTouchEventListener(CC_CALLBACK_2(OptionLayer::onSlider2,this));
	
    return true;
}

void OptionLayer::onCheck(Ref* sender,Widget::TouchEventType type){
	//터치 이벤트 실행시 프로그램 종료
	switch (type){
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
		Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
		break;
	case Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void OptionLayer::onButton1(Ref* sender,Widget::TouchEventType type){
	//터치 이벤트 실행시 프로그램 종료
	switch (type){
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:	
		this->removeFromParentAndCleanup(true);		
		dynamic_cast<PlayScene*>(PlayScene::get_layer())->set_optionFlag(false);
		Director::getInstance()->getRunningScene()->getScheduler()->resumeTarget(PlayScene::get_layer());
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
		break;
	case ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void OptionLayer::onButton2(Ref* sender,Widget::TouchEventType type){
	//터치 이벤트 실행시 프로그램 종료
	LoginDBdata* nuserData = nullptr;
	switch (type){
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:

		nuserData = dynamic_cast<LoginDBdata*>(Object_::DBmanager.get_LoginDB().getCurrentUser());
		
		Object_::DBmanager.get_LoginDB().set_User_DBdata(nuserData->DB_ID,nuserData->stage);
	
		Object_::DBmanager.get_LoginDB().saveDB();
	
		break;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
		break;
	case ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void OptionLayer::onButton3(Ref* sender,Widget::TouchEventType type){
	//터치 이벤트 실행시 프로그램 종료
	LoginDBdata* userData = nullptr;
	switch (type){
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
		userData = dynamic_cast<LoginDBdata*>(Object_::DBmanager.get_LoginDB().getCurrentUser());
		Object_::DBmanager.get_LoginDB().set_User_DBdata(userData->DB_ID,userData->stage);
		Object_::DBmanager.get_LoginDB().saveDB();

		Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
		break;
	case ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}


void OptionLayer::onSlider1(Ref* sender,Widget::TouchEventType type){
	//터치 이벤트 실행시 프로그램 종료
	switch (type){
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
		Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
		break;
	case ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}


void OptionLayer::onSlider2(Ref* sender,Widget::TouchEventType type){
	//터치 이벤트 실행시 프로그램 종료
	switch (type){
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
		Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
		break;
	case ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}
