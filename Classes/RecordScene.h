#pragma once
#ifndef __RECORD_SCENE_H__
#define __RECORD_SCENE_H__

#include "cocos2d.h"
#include "constant.h"
#include "ui\CocosGUI.h"

class RecordScene : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene();
	CREATE_FUNC(RecordScene);

	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);

	void printRanking();		//��ŷ ���� �� ���
	void TouchEnd(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void run(float dt);			//schedule�� �� �Լ�
private:
	cocos2d::Label* rankingIDList[LABEL_RADIX];
	cocos2d::Label* rankingStageList[LABEL_RADIX];
};

#endif // __LOADING_SCENE_H__
