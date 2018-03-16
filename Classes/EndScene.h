#pragma once
#include "cocos2d.h"
#include "CommonData.h"
#include "GameScene.h"
#include "StartScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

class EndScene : public Layer{
public:
	EndScene();
	static Scene* createScene(HERO_TYPE,int);
	virtual bool init(HERO_TYPE,int);
	static EndScene* create(HERO_TYPE,int);
	void update(float);
};