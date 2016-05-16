#include "cocos2d.h" 
#include "Animation.h"

USING_NS_CC;

AnimationScene::AnimationScene()
{

}

AnimationScene::~AnimationScene()
{

}

bool AnimationScene::init()
{
	AnimationLayer * layer = AnimationLayer::create();
	this->addChild(layer);
	return true;
}      




///////////////////////////////////////////////////////////////////////////////////////
AnimationLayer::AnimationLayer()
{

}

AnimationLayer::~AnimationLayer()
{

}

bool AnimationLayer::init()
{
	
	Size s = Director::sharedDirector()->getWinSize();

	Sprite *sprite = Sprite::create("animations/grossini.png");
	sprite->setPosition(Vec2(s.width/2, s.height/2));

	Texture2D * texture = TextureCache::sharedTextureCache()->addImage("animations/grossini_dance_atlas.png");

	Animation * animation = Animation::create();
	animation->setDelayPerUnit(0.5f);
	animation->addSpriteFrameWithTexture(texture, Rect(0,0,85,121));
	animation->addSpriteFrameWithTexture(texture, Rect(85,0,85,121));
	animation->addSpriteFrameWithTexture(texture, Rect(85*2,0,85,121));
	animation->addSpriteFrameWithTexture(texture, Rect(85*3,0,85,121));
	animation->addSpriteFrameWithTexture(texture, Rect(85*4,0,85,121));

	sprite->runAction(Animate::create(animation));
	this->addChild(sprite);

	return true;
}