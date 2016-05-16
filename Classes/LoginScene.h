#ifndef __LOGINSCENE_H__
#define __LOGINSCENE_H__

#include <iostream>
#include <iomanip>
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "DBClass.h"

class LoginScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	void onCheck(Ref* sender,   cocos2d::ui::Widget::TouchEventType type);
	void onButton1(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void onButton2(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void onText1(Ref* sender,   cocos2d::ui::Widget::TouchEventType type);
	void onText2(Ref* sender,   cocos2d::ui::Widget::TouchEventType type);
    // implement the "static create()" method manually
    CREATE_FUNC(LoginScene);

private:
	cocos2d::ui::TextField* current_clicked_textfield;

	cocos2d::ui::ImageView* image;
	cocos2d::Node* panel1;	//3개의 자식
	cocos2d::Node* panel2;	//3개의 자식

	cocos2d::ui::CheckBox* check;	//1개의 자식
	cocos2d::ui::Button* button1;//login
	cocos2d::ui::Button* button2;//logout

	cocos2d::ui::TextField* text1;//id
	cocos2d::ui::TextField* text2;//pw
public:
	//getter & setter
	cocos2d::ui::TextField* get_current_clicked_textfield();
	void set_current_clicked_textfield(cocos2d::ui::TextField* current_clicked_textfield);
};

#endif // __HELLOWORLD_SCENE_H__
