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

	int toRight; //-1���� 1����
	int isToRight();
	void setToRight(int);

	float speed;//�ٶ�
	float getSpeed();
	void setSpeed(float);

	int slowSpeedTime;//����ʱ��
	int getSlowSpeedTime();
	void setSlowSpeedTime(int);

	int coin;
	int getCoin();
	void setCoin(int);

	int immuneTime; //�޵�ʱ��
	int getImmuneTime();
	void setImmuneTime(int);

	bool extraLife;//��������
	bool haveExtraLife();
	void setExtraLife(bool);
};