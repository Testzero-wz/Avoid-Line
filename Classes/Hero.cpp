#include "Hero.h"

Hero::Hero(HERO_TYPE ty){//构造函数
	toRight = -1;
	speed = 2.5;
	slowSpeedTime = 0;
	immuneTime = 3*60;
	coin = 0;
	extraLife = 0;
	type = ty;
}
Hero* Hero::create(HERO_TYPE ty){
	Hero* pRet = new Hero(ty);
	if(pRet && pRet->init(ty))
	{
		pRet->autorelease();//将对象放入自动清空池里面，它会自动清空，不需要我们手动的delete
		return pRet;
	}else{
		delete pRet;
		pRet = nullptr; //NULL
		return nullptr;
	}
}
bool Hero::init(HERO_TYPE ty){
	bool isSuccess = false;
//	DrawNode* drawNode = DrawNode::create();
	switch(type){
	case BIRD:
//		isSuccess = Sprite::init();
//		drawNode->drawDot(Point(0,0),5,Color4F::WHITE);
//		this->addChild(drawNode);
		isSuccess = Sprite::initWithSpriteFrameName("hero1.png");
		this->setScale(0.45);
		break;
	case FIRE:
		isSuccess = Sprite::initWithSpriteFrameName("hero2.png");
		this->setScale(0.2);
		break;
	}
	this->setPosition(BORN_X,BORN_Y);
	return isSuccess;
}

HERO_TYPE Hero::getType(){
	return type;
}
void Hero::setType(HERO_TYPE d){
	type = d;
}

int Hero::isToRight(){
	return toRight;
}
void Hero::setToRight(int d){
	toRight = d;
}

float Hero::getSpeed(){
	return speed;
}
void Hero::setSpeed(float x){
	speed = x;
}

int Hero::getSlowSpeedTime(){
	return slowSpeedTime;
}
void Hero::setSlowSpeedTime(int x){
	slowSpeedTime = x;
}

int Hero::getCoin(){
	return coin;
}
void Hero::setCoin(int x){
	coin = x;
}

int Hero::getImmuneTime(){
	return immuneTime;
}
void Hero::setImmuneTime(int d){
	immuneTime = d;
}

bool Hero::haveExtraLife(){
	return extraLife;
}
void Hero::setExtraLife(bool d){
	extraLife = d;
}