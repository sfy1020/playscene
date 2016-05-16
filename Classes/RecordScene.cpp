#include "RecordScene.h"
#include "constant.h"
#include "Object_.h"
#include "LoginDB.h"
#include "ui\CocosGUI.h"
#include "LoginScene.h"
#include "PlayScene.h"
#include "LoadingScene.h"
USING_NS_CC;

Scene* RecordScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = RecordScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool RecordScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto nextButton = ui::Button::create();
	nextButton->setTouchEnabled(true);
	nextButton->setContentSize(cocos2d::Size(500, 150));
	nextButton->setTitleText("NEXT");
	nextButton->setTitleFontName(FONT);
	nextButton->setTitleFontSize(50);
	nextButton->setPosition(Point(1050, visibleSize.height - 700));
	nextButton->addTouchEventListener(CC_CALLBACK_2(RecordScene::TouchEnd, this));
	addChild(nextButton);

	auto label = cocos2d::Label::createWithSystemFont("High Scores", FONT, 70, cocos2d::Size(500, 150), cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::CENTER);
	label->setPosition(Vec2(visibleSize.width / 2 + 90, visibleSize.height - 80));
	this->addChild(label,1);


	auto sprite = cocos2d::Sprite::create("res\\RecordImage.png");

	sprite->setOpacity(50);
	sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(sprite);

	printRanking();		//랭킹 정렬 및 출력

	cocos2d::Sprite* pika = cocos2d::Sprite::create("res\\picapica.png");
	pika->setScale((float)0.5f);
	pika->setPosition(Vec2(visibleSize.width / 2 - 150, visibleSize.height - 700));
	this->addChild(pika);

	pika->setOpacity(0);
	FadeIn*  fadeOut = FadeIn::create(2.0f);
	pika->runAction(fadeOut);

	auto gameOverLabel = cocos2d::Label::createWithSystemFont("GAME OVER", FONT, 50, cocos2d::Size(500, 150), cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::CENTER);
	gameOverLabel->setPosition(Vec2(visibleSize.width / 2 + 200, visibleSize.height - 700));
	this->addChild(gameOverLabel, 1);

	gameOverLabel->setOpacity(0);
	fadeOut = FadeIn::create(2.0f);
	gameOverLabel->runAction(fadeOut);
	this->scheduleOnce(schedule_selector(RecordScene::run), SCHEDULE_TIME);
	return true;
}

void RecordScene::run(float dt){
	Object_::sound.run(2);
}

void RecordScene::printRanking()
{
	LoginDB* userData = &Object_::DBmanager.get_LoginDB(); 
		auto inform = userData->get_loginDB();
	std::pair < int, std::string> tempPair;

	std::vector< std::pair < int, std::string> > loginInform;

	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	FadeIn*  fadeOut = FadeIn::create(2.0f);

	int index = 0;
	for (auto i : inform)
	{
		tempPair.first = i.second->stage;
		tempPair.second = i.second->DB_ID;
		loginInform.push_back(tempPair);
	}

	sort(loginInform.rbegin(), loginInform.rend());

	auto IDLabel = cocos2d::Label::createWithSystemFont("     ID", FONT, 40, cocos2d::Size(500, 150), cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::CENTER);
	IDLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 180));

	auto stageLabel = cocos2d::Label::createWithSystemFont("STAGE", FONT, 40, cocos2d::Size(500, 150), cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::CENTER);
	stageLabel->setPosition(Vec2(visibleSize.width / 2 + 450, visibleSize.height - 180));

	this->addChild(IDLabel, 1);
	this->addChild(stageLabel, 1);

	IDLabel->setOpacity(0);
	fadeOut = FadeIn::create(2.0f);
	IDLabel->runAction(fadeOut);

	stageLabel->setOpacity(0);
	fadeOut = FadeIn::create(2.0f);
	stageLabel->runAction(fadeOut);

	int size = loginInform.size();
	if (size > 10)
		size = 10;

	for (int i = 0; i < size; i++)
	{
		rankingIDList[i] = cocos2d::Label::createWithSystemFont(loginInform[i].second, FONT, 30, cocos2d::Size(500, 150), cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::CENTER);
		rankingIDList[i]->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 240 - i*40));
		
		char s_rankingStageList[LABEL_RADIX];
		_itoa_s(loginInform[i].first, s_rankingStageList, LABEL_RADIX);
		rankingStageList[i] = cocos2d::Label::createWithSystemFont(s_rankingStageList, FONT, 30, cocos2d::Size(500, 150), cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::CENTER);
		rankingStageList[i]->setPosition(Vec2(visibleSize.width / 2 + 500, visibleSize.height - 240 - i * 40));


		this->addChild(rankingIDList[i], 1);
		this->addChild(rankingStageList[i], 1);

		rankingIDList[i]->setOpacity(0);
		fadeOut = FadeIn::create(2.0f);
		rankingIDList[i]->runAction(fadeOut);
		
		rankingStageList[i]->setOpacity(0);
		fadeOut = FadeIn::create(2.0f);
		rankingStageList[i]->runAction(fadeOut);

	}

}

void RecordScene::TouchEnd(Ref* pSender, ui::Widget::TouchEventType type){
	ui::Button* sender = (ui::Button*)pSender;
	if (type == ui::Widget::TouchEventType::BEGAN){
		auto director = Director::getInstance();

		//auto playscene = PlayScene::createScene();		
		//TransitionScene* play = TransitionFade::create(2.0f, playscene, Color3B::WHITE);
		//director->replaceScene(play);

		auto loadingscene = LoadingScene::createScene();
		director->pushScene(loadingscene);

		auto loginscene = LoginScene::createScene();
		TransitionScene* login = TransitionJumpZoom::create(2.0f, loginscene);
		director->pushScene(login);
	}
	else if (type == ui::Widget::TouchEventType::MOVED){
	}
	else if (type == ui::Widget::TouchEventType::ENDED){
	}
	else if (type == ui::Widget::TouchEventType::CANCELED){}
}


void RecordScene::menuCloseCallback(Ref* pSender)
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


