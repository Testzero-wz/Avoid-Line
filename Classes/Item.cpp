#include "Item.h"

Item::Item(){//���캯��

}
Item* Item::create(ITEM_TYPE ty){
	Item* pRet = new Item();
	if(pRet && pRet->init(ty))
	{
		pRet->autorelease();//����������Զ���ճ����棬�����Զ���գ�����Ҫ�����ֶ���delete
		return pRet;
	}else{
		delete pRet;
		pRet = nullptr; //NULL
		return nullptr;
	}
}
bool Item::init(ITEM_TYPE ty){
	bool isSuccess = false;
	this->type = ty;
	switch (ty)
	{
	case SLOWSPEED:
		isSuccess = Sprite::initWithSpriteFrameName("slowspeed.png");
		this->setScale(0.4);
		break;
	case COIN:
		isSuccess = Sprite::initWithSpriteFrameName("coin.png");
		this->setScale(0.4);
		break;
	case IMMUNE:
		isSuccess = Sprite::initWithSpriteFrameName("shield.png");
		this->setScale(0.35);
		break;
	case EXTRALIFE:
		isSuccess = Sprite::initWithSpriteFrameName("protect.png");
		this->setScale(0.35);
	default:
		break;
	}
	this->setAnchorPoint(Point::ANCHOR_MIDDLE);
	return isSuccess;
}
ITEM_TYPE Item::getType(){
	return type;
}
void Item::setType(ITEM_TYPE ty){
	type = ty;
}