#pragma once
#include "cocos2d.h"
#include "CommonData.h"	//���ú�/enum
#include "StartScene.h"	//��ʼ����
#include "EndScene.h"	//��������
#include "Hero.h"		//���
#include "Item.h"		//����
#include "Route.h"		//·�߼�¼
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
	void moveBackground(); //����

	Hero* hero;
	void createHero(HERO_TYPE);
	void createTouchListener();
	void moveHero();	//���
	void speedUp();

	float backgroundSpeed;
	float getBackgroundSpeed();
	void setBackgroundSpeed(float);//���������ٶ�


/*-----------------------------------------------------------*/
//�ϰ���
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

	

	Vector<Item*>	allItem;	//ȫ������
	void createItemCoin(float);
	void createItemImmune(float);
	void createItemSlowspeed(float);
	void createItemExtraLife(float);
	void createItemByType(ITEM_TYPE);
	void moveItem();

	Vector<Route*>	allRoute;	//ȫ��·�߼�¼
	void createRoute(float);
	void moveRoute();
	
	void pause(Ref *);
	void resume(Ref *);
	bool paused; //��ͣ

	float totalPoint;
	void createScoreBoard();
	void updateScoreBoard();	//�ܷ� ���·���

	int isGameOver;
	bool isPaused;

	bool m_keyBackFlag;
	void change_m_keyBackFlag(float);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);


};