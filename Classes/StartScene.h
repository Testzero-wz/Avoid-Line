#pragma once
#include "cocos2d.h"
#include "CommonData.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

using namespace cocos2d;

class StartScene : public Layer{
public:
	bool m_keyBackFlag;
	void change_m_keyBackFlag(float);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	StartScene();
	static Scene* createScene();
	virtual bool init();
	static StartScene* create();
	void update(float);

	void chooseStart(Ref *);
	HERO_TYPE chosenHero;
	void chooseHero1(Ref *);
	void chooseHero2(Ref *);
	void chooseBackToMainMenu(Ref *);

	Menu* allMenu;

	void saveAnimation();
	void saveSound();
};