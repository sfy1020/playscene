#ifndef __OPTIONCLASS_H__
#define __OPTIONCLASS_H__

#include <iostream>
#include <iomanip>
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "DBClass.h"

class OptionLayer : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	void onCheck(Ref* sender,   cocos2d::ui::Widget::TouchEventType type);
	void onButton1(Ref* sender, cocos2d::ui::Widget::TouchEventType type);//continue
	void onButton2(Ref* sender, cocos2d::ui::Widget::TouchEventType type);//save
	void onButton3(Ref* sender,cocos2d::ui::Widget::TouchEventType type);//quit
	void onSlider1(Ref* sender,   cocos2d::ui::Widget::TouchEventType type);//music slider
	void onSlider2(Ref* sender,   cocos2d::ui::Widget::TouchEventType type);//sound slider
    // implement the "static create()" method manually
	CREATE_FUNC(OptionLayer);

private:	
	cocos2d::Node* panel2;	
	cocos2d::ui::Button* button1;//continue
	cocos2d::ui::Button* button2;//save
	cocos2d::ui::Button* button3;//quit
	cocos2d::ui::Slider* slider1;//music slider
	cocos2d::ui::Slider* slider2;//sound slider
};

#endif // __HELLOWORLD_SCENE_H__
