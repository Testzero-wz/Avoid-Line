#pragma once
#include "cocos2d.h"
#include "CommonData.h"

using namespace cocos2d;

class Item: public Sprite{
public:
	Item();
	static Item* create(ITEM_TYPE);
	virtual bool init(ITEM_TYPE);
	ITEM_TYPE type;
	ITEM_TYPE getType();
	void setType(ITEM_TYPE);
};