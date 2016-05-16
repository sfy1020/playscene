#ifndef __PLAYSCENE_H__
#define __PLAYSCENE_H__

#include "cocos2d.h"
#include "Object_.h"
#include "CharacterCommon.h"
#include "DBClass.h"
#include "GameController.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

class PlayScene : public cocos2d::Layer
{
public:
	~PlayScene();
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(PlayScene);
	void gameLogic(float dt);
	void click(int x, int y);
	void clickRelease(int x, int y);
	void clickMove(int x, int y);
	void rightClick(int x, int y);
	
	void touchedUpradeButton(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void touchedOptionButton(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void touchedScrollImg(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	static cocos2d::Layer* get_layer();

private:
	GameController* gamecontroller;
	cocos2d::Sprite* currentClickedTower;
	static cocos2d::Layer* thislayer;
	bool optionFlag;

	cocos2d::Node* rootNode;
	cocos2d::Node* panel1;
	cocos2d::ui::Button* b_setting;
	cocos2d::Node* panel3;
	cocos2d::ui::ImageView* char_img;
	cocos2d::Node* panel4;
	cocos2d::ui::Button* bt_upgrade;
	cocos2d::ui::Text* ch_name;
	cocos2d::ui::Text* t_hp;
	cocos2d::ui::Text* ti_hp;
	cocos2d::ui::Text* t_power;
	cocos2d::ui::Text* ti_power;
	cocos2d::ui::Text* t_speed;
	cocos2d::ui::Text* ti_speed;
	cocos2d::ui::Text* t_level;
	cocos2d::ui::Text* ti_level;
	cocos2d::ui::Text* t_range;
	cocos2d::ui::Text* ti_range;
	cocos2d::Node* panel5;
	cocos2d::ui::Text* t_stage;
	cocos2d::ui::Text* ti_stage;
	cocos2d::ui::Text* t_enemy;
	cocos2d::ui::Text* ti_enemy;
	cocos2d::Node* panel6;
	cocos2d::ui::ScrollView* scrollView;
	cocos2d::ui::ImageView* img[10];
	cocos2d::Node* panel7;
	cocos2d::ui::Text* t_user;
	cocos2d::ui::Text* t_life;
	cocos2d::ui::Text* ti_life;
	cocos2d::ui::Text* t_gold;
	cocos2d::ui::Text* ti_gold;
public:										//getter
	GameController*				get_gamecontroller();
	cocos2d::Sprite*			get_currentClickedTower();
	cocos2d::Node*				get_rootNode();
	cocos2d::Node*				get_panel1();
	cocos2d::ui::Button*		get_b_setting();
	cocos2d::Node*				get_panel3();
	cocos2d::ui::ImageView*		get_char_img();
	cocos2d::Node*				get_panel4();
	cocos2d::ui::Button*		get_bt_upgrade();
	cocos2d::ui::Text*			get_ch_name();
	cocos2d::ui::Text*			get_t_hp();
	cocos2d::ui::Text*			get_ti_hp();
	cocos2d::ui::Text*			get_t_power();
	cocos2d::ui::Text*			get_ti_power();
	cocos2d::ui::Text*			get_t_speed();
	cocos2d::ui::Text*			get_ti_speed();
	cocos2d::ui::Text*			get_t_level();
	cocos2d::ui::Text*			get_ti_level();
	cocos2d::ui::Text*			get_t_range();
	cocos2d::ui::Text*			get_ti_range();
	cocos2d::Node*				get_panel5();
	cocos2d::ui::Text*			get_t_stage();
	cocos2d::ui::Text*			get_ti_stage();
	cocos2d::ui::Text*			get_t_enemy();
	cocos2d::ui::Text*			get_ti_enemy();
	cocos2d::Node*				get_panel6();
	cocos2d::ui::ScrollView*	get_scrollView();
	cocos2d::ui::ImageView*		get_img(int i);
	cocos2d::Node*				get_panel7();
	cocos2d::ui::Text*			get_t_user();
	cocos2d::ui::Text*			get_t_life();
	cocos2d::ui::Text*			get_ti_life();
	cocos2d::ui::Text*			get_t_gold();
	cocos2d::ui::Text*			get_ti_gold();
	bool						get_optionFlag();
	void						set_optionFlag(bool optionFlag);
};

#endif // __HELLOWORLD_SCENE_H__
