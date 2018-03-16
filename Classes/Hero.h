#pragma once
#include "cocos2d.h"
#include "CommonData.h"

using namespace cocos2d;

class Hero: public Sprite{
public:
	Hero(HERO_TYPE);
	static Hero* create(HERO_TYPE);
	virtual bool init(HERO_TYPE);

	HERO_TYPE type;
	HERO_TYPE getType();
	void setType(HERO_TYPE);

	int toRight; //-1向左 1向右
	int isToRight();
	void setToRight(int);

	float speed;//速度
	float getSpeed();
	void setSpeed(float);

	int slowSpeedTime;//减速时间
	int getSlowSpeedTime();
	void setSlowSpeedTime(int);

	int coin;
	int getCoin();
	void setCoin(int);

	int immuneTime; //无敌时间
	int getImmuneTime();
	void setImmuneTime(int);

	bool extraLife;//额外生命
	bool haveExtraLife();
	void setExtraLife(bool);
};