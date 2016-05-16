#include "PlayScene.h"
#include "OptionLayer.h"
USING_NS_CC;
using namespace cocostudio::timeline;

cocos2d::Layer* PlayScene::thislayer;
cocos2d::Scene* thisScene;

PlayScene::~PlayScene(){
	delete gamecontroller;
}

Scene* PlayScene::createScene(){
    auto scene = Scene::create();
    auto layer = PlayScene::create();
	thislayer = layer;
    scene->addChild(layer);
	thisScene = scene;
    return scene;
}

// on "init" you need to initialize your instance
bool PlayScene::init(){
	if (!Layer::init())
		return false;

	currentClickedTower = nullptr;
	optionFlag = false;

	rootNode = CSLoader::createNode("MainScene.csb");
	addChild(rootNode);
	rootNode->setTag(0);
	allPrint(rootNode);

	panel1 = rootNode->getChildByTag(44);
	b_setting = dynamic_cast<ui::Button*>(panel1->getChildByTag(60));

	panel1->removeChild(b_setting,false);		//option button
	b_setting->setLocalZOrder(BIG_INT+2);
	this->addChild(b_setting);
	b_setting->setPosition(Vec2(50,SIZE_OF_GLWIN_HEIGHT-50));
	b_setting->setTouchEnabled(true);
	b_setting->addTouchEventListener(CC_CALLBACK_2(PlayScene::touchedOptionButton,this));

	panel3 = rootNode->getChildByTag(52);
	char_img = dynamic_cast<ui::ImageView*>(panel3->getChildByTag(58));

	panel4 = rootNode->getChildByTag(53);
	bt_upgrade = dynamic_cast<ui::Button*>(panel4->getChildByTag(70));
	bt_upgrade->setTitleFontName(FONT);
	bt_upgrade->setPosition(Vec2(bt_upgrade->getPositionX()-10, bt_upgrade->getPositionY()));
	bt_upgrade->setTouchEnabled(true);					
	bt_upgrade->addTouchEventListener(CC_CALLBACK_2(PlayScene::touchedUpradeButton, this));

	ch_name = dynamic_cast<ui::Text*>(panel4->getChildByTag(66));
	ch_name->setFontName(FONT);
	ch_name->setTextColor(cocos2d::Color4B::WHITE);
	char_img->setContentSize(cocos2d::Size(110, 110));
	char_img->loadTexture("res\\window.png");

	t_hp = dynamic_cast<ui::Text*>(panel4->getChildByTag(79));
	t_hp->setFontName(FONT);
	t_hp->setTextColor(cocos2d::Color4B::WHITE);
	ti_hp = dynamic_cast<ui::Text*>(panel4->getChildByTag(80));
	ti_hp->setFontName(FONT);
	ti_hp->setTextColor(cocos2d::Color4B::WHITE);

	t_power = dynamic_cast<ui::Text*>(panel4->getChildByTag(77));
	t_power->setFontName(FONT);
	t_power->setTextColor(cocos2d::Color4B::WHITE);
	ti_power = dynamic_cast<ui::Text*>(panel4->getChildByTag(78));
	ti_power->setFontName(FONT);
	ti_power->setTextColor(cocos2d::Color4B::WHITE);

	t_speed = dynamic_cast<ui::Text*>(panel4->getChildByTag(75));
	t_speed->setFontName(FONT);
	t_speed->setTextColor(cocos2d::Color4B::WHITE);
	ti_speed = dynamic_cast<ui::Text*>(panel4->getChildByTag(76));
	ti_speed->setFontName(FONT);
	ti_speed->setTextColor(cocos2d::Color4B::WHITE);
	t_level = dynamic_cast<ui::Text*>(panel4->getChildByTag(73));
	t_level->setFontName(FONT);
	t_level->setTextColor(cocos2d::Color4B::WHITE);
	ti_level = dynamic_cast<ui::Text*>(panel4->getChildByTag(42));
	ti_level->setFontName(FONT);
	ti_level->setTextColor(cocos2d::Color4B::WHITE);

	t_range = dynamic_cast<ui::Text*>(panel4->getChildByTag(71));
	t_range->setFontName(FONT);
	t_range->setTextColor(cocos2d::Color4B::WHITE);
	ti_range = dynamic_cast<ui::Text*>(panel4->getChildByTag(72));
	ti_range->setFontName(FONT);
	ti_range->setTextColor(cocos2d::Color4B::WHITE);

	panel5 = rootNode->getChildByTag(62);
	t_stage = dynamic_cast<ui::Text*>(panel5->getChildByTag(61));
	t_stage->setFontName(FONT);
	t_stage->setTextColor(cocos2d::Color4B::WHITE);
	ti_stage = dynamic_cast<ui::Text*>(panel5->getChildByTag(62));
	ti_stage->setFontName(FONT);
	ti_stage->setTextColor(cocos2d::Color4B::WHITE);

	t_enemy = dynamic_cast<ui::Text*>(panel5->getChildByTag(63));
	t_enemy->setFontName(FONT);
	t_enemy->setTextColor(cocos2d::Color4B::WHITE);
	ti_enemy = dynamic_cast<ui::Text*>(panel5->getChildByTag(64));
	ti_enemy->setFontName(FONT);
	ti_enemy->setTextColor(cocos2d::Color4B::WHITE);
	
	panel6 = rootNode->getChildByTag(63);
	scrollView = dynamic_cast<ui::ScrollView*>(panel6->getChildByTag(49));

	for (int i = 0; i < 10; i++){
		img[i] = dynamic_cast<ui::ImageView*>(scrollView->getChildByTag(51+i));
	}

	int i = 1;
	for (auto e : scrollView->getChildren()){
		auto img = dynamic_cast<ui::ImageView*>(e);
		img->setTouchEnabled(true);					//scrollnview imageview 이벤트
		img->addTouchEventListener(CC_CALLBACK_2(PlayScene::touchedScrollImg, this));
		
		img->setTag(TOWER_COMMON + i);
		img->setContentSize(cocos2d::Size(110, 110));
		img->loadTexture("res\\window.png");

		GraphicDBdata gtemp = Object_::graphic.get_GraphicDBdata(Object_::DBmanager.get_Object_DBdata(img->getTag())->imgID);
		cocos2d::Sprite* sprite = cocos2d::Sprite::create(gtemp.filename, cocos2d::Rect(0, 0, gtemp.size_x, gtemp.size_y));
		img->addChild(sprite);
		sprite->setPosition(cocos2d::Vec2((img->getBoundingBox().getMaxX() - img->getBoundingBox().getMinX()) / 2, (img->getBoundingBox().getMaxY() - img->getBoundingBox().getMinY()) / 2));
		sprite->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
		sprite->setScale(0.75f, 0.75f);
		
		auto towerData = *dynamic_cast<TowerDBdata*>(Object_::DBmanager.get_Object_DBdata(img->getTag()));
		char buffer[30];
		_itoa_s(towerData.cost, buffer, LABEL_RADIX);
		auto label = cocos2d::Label::createWithSystemFont(buffer, "SF Action Man", 24, cocos2d::Size(50, 50), cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::CENTER);
		label->setPosition(Vec2(35, 25));
		label->setColor(cocos2d::Color3B::WHITE);
		img->addChild(label);
		i++;
	}

	panel7 = rootNode->getChildByTag(64);
	t_user = dynamic_cast<ui::Text*>(panel7->getChildByTag(68));
	t_user->setFontName(FONT);
	t_user->setTextColor(cocos2d::Color4B::WHITE);

	t_life = dynamic_cast<ui::Text*>(panel7->getChildByTag(67));
	t_life->setFontName(FONT);
	t_life->setTextColor(cocos2d::Color4B::WHITE);

	ti_life = dynamic_cast<ui::Text*>(panel7->getChildByTag(69));
	ti_life->setFontName(FONT);
	ti_life->setTextColor(cocos2d::Color4B::WHITE);

	t_gold = dynamic_cast<ui::Text*>(panel7->getChildByTag(66));
	t_gold->setFontName(FONT);
	t_gold->setTextColor(cocos2d::Color4B::WHITE);
	t_gold->setPosition(cocos2d::Vec2(t_life->getPositionX(), t_life->getPositionY() - 55));

	ti_gold = dynamic_cast<ui::Text*>(panel7->getChildByTag(65));
	ti_gold->setFontName(FONT);
	ti_gold->setTextColor(cocos2d::Color4B::WHITE);
	ti_gold->setPosition(cocos2d::Vec2(ti_life->getPositionX(), ti_life->getPositionY() - 55));

	///////////////////////////////////////////////////////////////////////event in objectLayer
	auto listener = cocos2d::EventListenerMouse::create();
	listener->onMouseDown = [this](cocos2d::Event* event){
		try {
			cocos2d::EventMouse* mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
			if (mouseEvent->getMouseButton() == 0){			//mouse left
				click(mouseEvent->getLocationInView().x, mouseEvent->getLocationInView().y);
			}
			else if (mouseEvent->getMouseButton() == 1){    //mouse right
				rightClick(mouseEvent->getLocationInView().x, mouseEvent->getLocationInView().y);
			}
			else if (mouseEvent->getMouseButton() == 2){    //mouse medien
			}
		}
		catch (std::bad_cast& e){return;}
	};

	listener->onMouseMove = [this](cocos2d::Event* event){
		try {
			cocos2d::EventMouse* mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
			if (mouseEvent->getMouseButton() == 0){			//mouse left
				clickMove(mouseEvent->getLocationInView().x, mouseEvent->getLocationInView().y);
			}
			else if (mouseEvent->getMouseButton() == 1){}	//mouse right
			else if (mouseEvent->getMouseButton() == 2){}	//mouse medien
		}catch (std::bad_cast& e){return;}
	};

	listener->onMouseUp = [this](cocos2d::Event* event){
		try {
			cocos2d::EventMouse* mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
			if (mouseEvent->getMouseButton() == 0){			//mouse left
				clickRelease(mouseEvent->getLocationInView().x, mouseEvent->getLocationInView().y);
			}
			else if (mouseEvent->getMouseButton() == 1){		//mouse right
			}
			else if (mouseEvent->getMouseButton() == 2){     //mouse medien
			}
		}
		catch (std::bad_cast& e){return;}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, Object_::objectLayer);	//ObjectLayer 이벤트
	Object_::objectLayer->setScaleX(SCALE_OF_OBJECT_LAYER_WIDTH);
	Object_::objectLayer->setScaleY(SCALE_OF_OBJECT_LAYER_HEIGHT);
	Object_::objectLayer->setPosition(Vec2(SIZE_OF_BOARD_CELL_X / 2, SIZE_OF_BOARD_CELL_Y / 2));
	panel1->addChild(Object_::objectLayer);

	this->gamecontroller = new GameController(this);
	this->schedule(schedule_selector(PlayScene::gameLogic), SCHEDULE_TIME);

	return true;
}

void PlayScene::gameLogic(float dt){
	gamecontroller->run();
}

void PlayScene::click(int x, int y){
	if (panel1->getBoundingBox().containsPoint(Vec2(x, y))){		//panel1 내부

		auto clickedUnit = gamecontroller->click(x, y, PANEL::IN1);
		if (clickedUnit){
			for (auto e : char_img->getChildren()){		//이전에 있던 모든 character image를 제거
				e->removeFromParentAndCleanup(true);
			}
			GraphicDBdata gtemp = Object_::graphic.get_GraphicDBdata(clickedUnit->get_imgID());		//새로운 이미지를 찾아서 보여준다.
			cocos2d::Sprite* sprite = cocos2d::Sprite::create(gtemp.filename, cocos2d::Rect(0, 0, gtemp.size_x, gtemp.size_y));
			char_img->addChild(sprite);
			sprite->setPosition(cocos2d::Vec2((char_img->getBoundingBox().getMaxX() - char_img->getBoundingBox().getMinX()) / 2, (char_img->getBoundingBox().getMaxY() - char_img->getBoundingBox().getMinY()) / 2));
			sprite->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
			sprite->setScale(0.75f, 0.75f);
			sprite->setTag(clickedUnit->get_id());

			gamecontroller->nameInfoUpdate(clickedUnit->get_name());
			gamecontroller->hpInfoUpdate(clickedUnit->get_hp(), clickedUnit->get_maxhp());
			gamecontroller->powerInfoUpdate(clickedUnit->get_damage());
			gamecontroller->speedInfoUpdate(clickedUnit->get_speed());
			gamecontroller->levelInfoUpdate(clickedUnit->get_level());
			gamecontroller->rangeInfoUpdate(clickedUnit->get_range());
		}

	}else if (panel3->getBoundingBox().containsPoint(Vec2(x, y))){		//panel3 내부

	}else if (panel4->getBoundingBox().containsPoint(Vec2(x, y))){		//panel4 내부

	}else if (panel5->getBoundingBox().containsPoint(Vec2(x, y))){		//panel5 내부

	}else if (panel6->getBoundingBox().containsPoint(Vec2(x, y))){		//panel6 내부

	}else if (panel7->getBoundingBox().containsPoint(Vec2(x, y))){		//panel7 내부

	}else{}
}

void PlayScene::rightClick(int x, int y)
{
	if (panel1->getBoundingBox().containsPoint(Vec2(x, y))){		//panel1 내부

		auto clickedUnit = gamecontroller->rightClick(x, y, PANEL::IN1);
		if (clickedUnit != NULL && OBJECT(clickedUnit->get_DB_ID()) == TOWER){
			clickedUnit->damaged(0, BIG_INT);
		}
	}
	else if (panel3->getBoundingBox().containsPoint(Vec2(x, y))){		//panel3 내부

	}
	else if (panel4->getBoundingBox().containsPoint(Vec2(x, y))){		//panel4 내부

	}
	else if (panel5->getBoundingBox().containsPoint(Vec2(x, y))){		//panel5 내부

	}
	else if (panel6->getBoundingBox().containsPoint(Vec2(x, y))){		//panel6 내부

	}
	else if (panel7->getBoundingBox().containsPoint(Vec2(x, y))){		//panel7 내부

	}
	else{}
}

void PlayScene::clickMove(int x, int y){
	if (!panel1->getBoundingBox().containsPoint(Vec2(x, y))){			//panel1이 아닌경우
		if (currentClickedTower)currentClickedTower->setPosition(Vec2(-100, -100));
	}

	if (panel1->getBoundingBox().containsPoint(Vec2(x, y))){
		if (currentClickedTower){
			int towerX = x / (SIZE_OF_BOARD_CELL_X*SCALE_OF_OBJECT_LAYER_WIDTH);
			int towerY = (y - panel1->getBoundingBox().getMinY()) / (SIZE_OF_BOARD_CELL_Y*SCALE_OF_OBJECT_LAYER_WIDTH);
			if (Object_::board[towerY][towerX] > 0)currentClickedTower->setColor(Color3B(150, 150, 150));
			else  currentClickedTower->setColor(Color3B::RED);
			currentClickedTower->setPosition(Vec2(x, y));
		}
		gamecontroller->clickMove(x, y, PANEL::IN1);
	}else if (panel3->getBoundingBox().containsPoint(Vec2(x, y))){		//panel3 내부
		gamecontroller->clickMove(x, y, PANEL::IN3);
	}else if (panel4->getBoundingBox().containsPoint(Vec2(x, y))){		//panel4 내부
		gamecontroller->clickMove(x, y, PANEL::IN4);
	}else if (panel5->getBoundingBox().containsPoint(Vec2(x, y))){		//panel5 내부
		gamecontroller->clickMove(x, y, PANEL::IN5);
	}else if (panel6->getBoundingBox().containsPoint(Vec2(x, y))){		//panel6 내부
		gamecontroller->clickMove(x, y, PANEL::IN6);
	}else if (panel7->getBoundingBox().containsPoint(Vec2(x, y))){		//panel7 내부
		gamecontroller->clickMove(x, y, PANEL::IN7);
	}else{}
}

void PlayScene::clickRelease(int x, int y){
	if (!panel1->getBoundingBox().containsPoint(Vec2(x, y))){			//panel1이 아닌경우
		if (currentClickedTower){
			currentClickedTower->removeFromParentAndCleanup(true);
			currentClickedTower = nullptr;
		}
	}
	
	if (panel1->getBoundingBox().containsPoint(Vec2(x, y))){
		if (currentClickedTower){
			int towerX = x / (SIZE_OF_BOARD_CELL_X*SCALE_OF_OBJECT_LAYER_WIDTH);
			int towerY = (y - panel1->getBoundingBox().getMinY()) / (SIZE_OF_BOARD_CELL_Y*SCALE_OF_OBJECT_LAYER_WIDTH);
			gamecontroller->createObject_(currentClickedTower->getTag(), -1, towerX, towerY);
			currentClickedTower->removeFromParentAndCleanup(true);
			currentClickedTower = nullptr;
		}
		gamecontroller->clickRelease(x, y, PANEL::IN1);
	}else if (panel3->getBoundingBox().containsPoint(Vec2(x, y))){		//panel3 내부
		gamecontroller->clickRelease(x, y, PANEL::IN3);
	}else if (panel4->getBoundingBox().containsPoint(Vec2(x, y))){		//panel4 내부
		gamecontroller->clickRelease(x, y, PANEL::IN4);
	}else if (panel5->getBoundingBox().containsPoint(Vec2(x, y))){		//panel5 내부
		gamecontroller->clickRelease(x, y, PANEL::IN5);
	}else if (panel6->getBoundingBox().containsPoint(Vec2(x, y))){		//panel6 내부
		gamecontroller->clickRelease(x, y, PANEL::IN6);
	}else if (panel7->getBoundingBox().containsPoint(Vec2(x, y))){		//panel7 내부
		gamecontroller->clickRelease(x, y, PANEL::IN7);
	}else{}
}

void PlayScene::touchedScrollImg(Ref* pSender, ui::Widget::TouchEventType type){
	ui::ImageView* sender = (ui::ImageView*)pSender;
	if (type == ui::Widget::TouchEventType::BEGAN){

		GraphicDBdata gtemp = Object_::graphic.get_GraphicDBdata(Object_::DBmanager.get_Object_DBdata(sender->getTag())->imgID);
		currentClickedTower = cocos2d::Sprite::create(gtemp.filename, cocos2d::Rect(0, 0, gtemp.size_x, gtemp.size_y));
		currentClickedTower->setScaleX(SCALE_OF_OBJECT_LAYER_HEIGHT);	currentClickedTower->setScaleY(SCALE_OF_OBJECT_LAYER_WIDTH);
		currentClickedTower->setColor(Color3B(150, 150, 150));
		currentClickedTower->setPosition(Vec2(-100,-100));
		currentClickedTower->setAnchorPoint(Vec2(0.5f,0.0f));
		currentClickedTower->setTag(sender->getTag());
		currentClickedTower->setOpacity(128);
		this->addChild(currentClickedTower);
	
	}else if (type == ui::Widget::TouchEventType::MOVED){

	}else if (type == ui::Widget::TouchEventType::ENDED){

	}else if (type == ui::Widget::TouchEventType::CANCELED){

	}
}

void PlayScene::touchedUpradeButton(Ref* pSender, ui::Widget::TouchEventType type){
	ui::ImageView* sender = (ui::ImageView*)pSender;
	if (type == ui::Widget::TouchEventType::BEGAN){
		if (char_img->getChildrenCount() > 0){
			int id = char_img->getChildren().at(0)->getTag();
			gamecontroller->unitUpgrade(id);
		}else{
			EXCEPTION("no clicked unit")
		}
	}else if (type == ui::Widget::TouchEventType::MOVED){
	}else if (type == ui::Widget::TouchEventType::ENDED){
	}else if (type == ui::Widget::TouchEventType::CANCELED){}
}

void PlayScene::touchedOptionButton(Ref* pSender, ui::Widget::TouchEventType type){
	ui::ImageView* sender = (ui::ImageView*)pSender;
	if (type == ui::Widget::TouchEventType::BEGAN){
		if (!optionFlag){
			auto temp = new OptionLayer();
			temp->init();
			this->addChild(temp);
			Director::getInstance()->getScheduler()->pauseTarget(this);
			optionFlag = true;
		}
	}
	else if (type == ui::Widget::TouchEventType::MOVED){
	}
	else if (type == ui::Widget::TouchEventType::ENDED){
	}
	else if (type == ui::Widget::TouchEventType::CANCELED){}
}


//getter
GameController*				PlayScene::get_gamecontroller(){
	return gamecontroller;
}

cocos2d::Sprite*			PlayScene::get_currentClickedTower(){
	return currentClickedTower;
}
cocos2d::Node*				PlayScene::get_rootNode(){
	return rootNode;
}
cocos2d::Node*				PlayScene::get_panel1(){
	return panel1;
}
cocos2d::ui::Button*		PlayScene::get_b_setting(){
	return b_setting;
}
cocos2d::Node*				PlayScene::get_panel3(){
	return panel3;
}
cocos2d::ui::ImageView*		PlayScene::get_char_img(){
	return char_img;
}
cocos2d::Node*				PlayScene::get_panel4(){
	return panel4;
}
cocos2d::ui::Button*		PlayScene::get_bt_upgrade(){
	return bt_upgrade;
}
cocos2d::ui::Text*			PlayScene::get_ch_name(){
	return ch_name;
}
cocos2d::ui::Text*			PlayScene::get_t_hp(){
	return t_hp;
}
cocos2d::ui::Text*			PlayScene::get_ti_hp(){
	return ti_hp;
}
cocos2d::ui::Text*			PlayScene::get_t_power(){
	return t_power;
}
cocos2d::ui::Text*			PlayScene::get_ti_power(){
	return ti_power;
}
cocos2d::ui::Text*			PlayScene::get_t_speed(){
	return t_speed;
}
cocos2d::ui::Text*			PlayScene::get_ti_speed(){
	return ti_speed;
}
cocos2d::ui::Text*			PlayScene::get_t_level(){
	return t_level;
}
cocos2d::ui::Text*			PlayScene::get_ti_level(){
	return ti_level;
}
cocos2d::ui::Text*			PlayScene::get_t_range(){
	return t_range;
}
cocos2d::ui::Text*			PlayScene::get_ti_range(){
	return ti_range;
}
cocos2d::Node*				PlayScene::get_panel5(){
	return panel5;
}
cocos2d::ui::Text*			PlayScene::get_t_stage(){
	return t_stage;
}
cocos2d::ui::Text*			PlayScene::get_ti_stage(){
	return ti_stage;
}
cocos2d::ui::Text*			PlayScene::get_t_enemy(){
	return t_enemy;
}
cocos2d::ui::Text*			PlayScene::get_ti_enemy(){
	return ti_enemy;
}
cocos2d::Node*				PlayScene::get_panel6(){
	return panel6;
}
cocos2d::ui::ScrollView*	PlayScene::get_scrollView(){
	return scrollView;
}
cocos2d::ui::ImageView*		PlayScene::get_img(int i){
	return img[i];
}
cocos2d::Node*				PlayScene::get_panel7(){
	return panel7;
}
cocos2d::ui::Text*			PlayScene::get_t_user(){
	return t_user;
}
cocos2d::ui::Text*			PlayScene::get_t_life(){
	return t_life;
}
cocos2d::ui::Text*			PlayScene::get_ti_life(){
	return ti_life;
}
cocos2d::ui::Text*			PlayScene::get_t_gold(){
	return t_gold;
}
cocos2d::ui::Text*			PlayScene::get_ti_gold(){
	return ti_gold;
}


cocos2d::Layer*				PlayScene::get_layer(){
	return thislayer;
}
bool						PlayScene::get_optionFlag(){
	return optionFlag;
}
void						PlayScene::set_optionFlag(bool optionFlag){
	this->optionFlag = optionFlag;
}
