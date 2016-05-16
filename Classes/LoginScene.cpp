#include "LoginScene.h"
#include "LoadingScene.h"
#include "TouchScene.h"
#include "PlayScene.h"
#include "cocostudio\CocoStudio.h"
#include "Object_.h"
#include <iostream>
#include <string>

using namespace cocostudio::timeline;
using namespace ui;
using namespace cocos2d;

cocos2d::Scene* LoginScene::createScene()
{
    // 'scene' is an autorelease object
	auto scene = cocos2d::Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = LoginScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LoginScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	current_clicked_textfield = nullptr;

	auto rootNode = CSLoader::createNode("Scene.csb");
	
	allPrint(rootNode);
	
    addChild(rootNode);
		
	image = dynamic_cast<ui::ImageView*>(rootNode->getChildByTag(92));	//3개의 자식
	
	panel1  = rootNode->getChildByTag(95);	//3개의 자식
	panel2  = rootNode->getChildByTag(99);	//3개의 자식

	check = dynamic_cast<CheckBox*>(rootNode->getChildByTag(103));	//1개의 자식
	button1 = dynamic_cast<Button*>(image->getChildByTag(93));//login
	button2 = dynamic_cast<Button*>(image->getChildByTag(94));//logout

	text1 = (TextField*)(panel1->getChildByTag(98));//id
	text2 = (TextField*)(panel2->getChildByTag(102));//pw

	check->addTouchEventListener(CC_CALLBACK_2(LoginScene::onCheck, this));
	check->setPosition(Vec2(check->getPositionX()-250, check->getPositionY()));
	auto checklabel = check->getChildByTag(104);
	checklabel->setColor(Color3B::WHITE);

	button1->addTouchEventListener(CC_CALLBACK_2(LoginScene::onButton1, this));
	button2->addTouchEventListener(CC_CALLBACK_2(LoginScene::onButton2, this));

	text1->addTouchEventListener(CC_CALLBACK_2(LoginScene::onText1, this));
	text2->addTouchEventListener(CC_CALLBACK_2(LoginScene::onText2, this));
	
	Object_::sound.run(1);
    return true;
}

void LoginScene::onCheck(Ref* sender, Widget::TouchEventType type){
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

void LoginScene::onButton1(Ref* sender,Widget::TouchEventType type){
	//터치 이벤트 실행시 프로그램 종료
	std::string id;
	std::string pw;
	LoginDBdata* userData = nullptr;

	switch (type){
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
		std::cout<<"id: "<<text1->getString()<<std::endl;
		id = text1->getString();
		std::cout<<"pw: "<<text2->getString()<<std::endl;
		pw = text2->getString();

		if (id==""||pw=="")
			break;

		userData = dynamic_cast<LoginDBdata*>(Object_::DBmanager.get_LoginDB().get_User_DBdata(id, pw));
		
		if (userData!=nullptr){
			Object_::DBmanager.get_LoginDB().setCurrentUser(userData);
			Director::getInstance()->popScene();
			auto playscene = dynamic_cast<PlayScene*>(PlayScene::get_layer());
			playscene->get_gamecontroller()->userLogin(text1->getString());
		}
		break;
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

void LoginScene::onButton2(Ref* sender, Widget::TouchEventType type){
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

void LoginScene::onText1(Ref* sender, Widget::TouchEventType type){
	auto textfield = dynamic_cast<TextField*> (sender);
	switch (type){
	case Widget::TouchEventType::BEGAN:
		if (current_clicked_textfield){
			current_clicked_textfield->setColor(Color3B::WHITE);
		}
		current_clicked_textfield = textfield;
		textfield->setColor(Color3B(150, 150, 150));
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
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

void LoginScene::onText2(Ref* sender, Widget::TouchEventType type){
	auto textfield = dynamic_cast<TextField*> (sender);
	switch (type){
	case Widget::TouchEventType::BEGAN:
		if (current_clicked_textfield){
			current_clicked_textfield->setColor(Color3B::WHITE);
		}
		current_clicked_textfield = textfield;
		textfield->setColor(Color3B(150, 150, 150));
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:

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


cocos2d::ui::TextField* LoginScene::get_current_clicked_textfield(){
	return current_clicked_textfield;
}

void LoginScene::set_current_clicked_textfield(cocos2d::ui::TextField* current_clicked_textfield){
	this->current_clicked_textfield = current_clicked_textfield;
}