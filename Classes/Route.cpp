#include "Route.h"

Route::Route(){//构造函数

}
Route* Route::create(HERO_TYPE ty,int x,int y){
	Route* pRet = new Route();
	if(pRet && pRet->init(ty,x,y))
	{
		pRet->autorelease();//将对象放入自动清空池里面，它会自动清空，不需要我们手动的delete
		return pRet;
	}else{
		delete pRet;
		pRet = nullptr; //NULL
		return nullptr;
	}
}
bool Route::init(HERO_TYPE ty,int x,int y){
	bool isSuccess = false;
	DrawNode* drawNode = DrawNode::create();
	switch (ty)
	{
	case BIRD:
		isSuccess = Sprite::init();
		drawNode->drawDot(Point(0,0),5,Color4F::WHITE);
		this->addChild(drawNode);
		break;
	case FIRE:
		isSuccess = Sprite::init();
		drawNode->drawDot(Point(0,0),3.5,Color4F(228/255.0,96/255.0,64/255.0,1));
		this->addChild(drawNode);
		break;
	}
	this->setPosition(x,y);
	return isSuccess;
}