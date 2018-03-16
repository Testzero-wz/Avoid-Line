#pragma once
#include "cocos2d.h"
#include "CommonData.h"

using namespace cocos2d;

class Route: public Sprite{
public:
	Route();
	static Route* create(HERO_TYPE,int,int);
	virtual bool init(HERO_TYPE,int,int);
};