#include "Route.h"

Route::Route(){//���캯��

}
Route* Route::create(HERO_TYPE ty,int x,int y){
	Route* pRet = new Route();
	if(pRet && pRet->init(ty,x,y))
	{
		pRet->autorelease();//����������Զ���ճ����棬�����Զ���գ�����Ҫ�����ֶ���delete
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