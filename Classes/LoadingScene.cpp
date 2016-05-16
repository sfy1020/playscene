#include "LoadingScene.h"
#include "constant.h"
USING_NS_CC;

Scene* LoadingScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LoadingScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool LoadingScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = cocos2d::Label::createWithSystemFont("Loading....", FONT, 100, cocos2d::Size(500, 150), cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::CENTER);
	label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(label,1);
	auto sprite = cocos2d::Sprite::create("res\\LoadingImage.png");
	sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(sprite);
	
	this->schedule(schedule_selector(LoadingScene::logic), SCHEDULE_TIME);

	return true;
}
void LoadingScene::logic(float dt){
	Sleep(2000);
	Director::getInstance()->popScene();
}

void LoadingScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}


