#pragma once
#include "cocos2d.h"
class AnimationScene :public cocos2d::CCScene
{
public:
	AnimationScene();
	virtual ~AnimationScene();
	virtual bool init();
	CREATE_FUNC(AnimationScene);
};

class AnimationLayer : public cocos2d::Layer
{
public:
	AnimationLayer();
	virtual ~AnimationLayer();
	virtual bool init();
	CREATE_FUNC(AnimationLayer);

};