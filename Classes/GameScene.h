#pragma once
#include "cocos2d.h"
#include "CommonData.h"	//公用宏/enum
#include "StartScene.h"	//开始场景
#include "EndScene.h"	//结束场景
#include "Hero.h"		//玩家
#include "Item.h"		//道具
#include "Route.h"		//路线记录
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

class GameScene : public Layer{
public:
	GameScene();
	static Scene* createScene(HERO_TYPE,bool);
	virtual bool init(HERO_TYPE,bool);
	static GameScene* create(HERO_TYPE,bool);
	void update(float);

	void createBackground();
	void moveBackground(); //背景

	Hero* hero;
	void createHero(HERO_TYPE);
	void createTouchListener();
	void moveHero();	//玩家
	void speedUp();

	float backgroundSpeed;
	float getBackgroundSpeed();
	void setBackgroundSpeed(float);//背景下落速度


/*-----------------------------------------------------------*/
//障碍物
	bool beganFlag;

	bool LRflag;
	Vector <Sprite *> vVerticalBarrier;
	Vector <Sprite *> vFloatBarrier;
	float floatBarrierDistance;
	Vector <Sprite *> vRemoveBarrier;
	//Vector <Sprite *> vRemoveFloatBarrier;

	void createVerticalBarrierUpdate(float);
	void createFloatBarrierUpdate(float);


	void moveBarrier();
	bool judgeHeroAndBarrier();

	Sprite * createVerticalBarrier(float,float);
	Sprite * createFloatBarrier(float,float);

/*-----------------------------------------------------------*/

	

	Vector<Item*>	allItem;	//全部道具
	void createItemCoin(float);
	void createItemImmune(float);
	void createItemSlowspeed(float);
	void createItemExtraLife(float);
	void createItemByType(ITEM_TYPE);
	void moveItem();

	Vector<Route*>	allRoute;	//全部路线记录
	void createRoute(float);
	void moveRoute();
	
	void pause(Ref *);
	void resume(Ref *);
	bool paused; //暂停

	float totalPoint;
	void createScoreBoard();
	void updateScoreBoard();	//总分 更新分数

	int isGameOver;
	bool isPaused;

	bool m_keyBackFlag;
	void change_m_keyBackFlag(float);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);


};