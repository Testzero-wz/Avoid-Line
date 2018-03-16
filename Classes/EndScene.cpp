#include "EndScene.h"
#include"SimpleAudioEngine.h"
using namespace CocosDenshion;

EndScene::EndScene(){
	
}
Scene* EndScene::createScene(HERO_TYPE ty,int pt)
{
	auto scene = Scene::create();//创建一个普通的场景
	auto layer = EndScene::create(ty,pt);//创建我们的层
	scene->addChild(layer);//将我们的层加到这个场景中
	return scene;
}
EndScene* EndScene::create(HERO_TYPE ty,int pt)//CREATE_FUNC(EndScene);
{
	EndScene* pRet = new EndScene();
	if(pRet && pRet->init(ty,pt))
	{
		pRet->autorelease();//将对象放入自动清空池里面，它会自动清空，不需要我们手动的delete
		return pRet;
	}else{
		delete pRet;
		pRet = nullptr; //NULL
		return nullptr;
	}
}
bool EndScene::init(HERO_TYPE ty,int pt){
	if(!Layer::init()){
		return false;
	}
	Sprite* bg;
	//背景
	switch (ty)
	{
	case BIRD:
		bg = Sprite::create("GameOver1.jpg");
		break;
	case FIRE:
		bg = Sprite::create("GameOver2.jpg");
		break;
	}
	bg->setScaleX(VISIBLE_SIZE.width/bg->getBoundingBox().size.width);
	bg->setScaleY(VISIBLE_SIZE.height/bg->getBoundingBox().size.height);
	bg->setPosition(0,0);
	bg->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	this->addChild(bg, -1);
	//显示分数
	auto lblScore = Label::createWithSystemFont(StringUtils::format("%08d", pt),"msyhbd.ttc",48);
	lblScore->setPosition(VISIBLE_SIZE.width - 20, VISIBLE_SIZE.height*0.545); //0.645
	lblScore->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	lblScore->setColor(Color3B::WHITE);
	this->addChild(lblScore);

	//读取文件 获得最高分
	auto highScore = UserDefault::getInstance()->getIntegerForKey("AVOIDLINEHIGHSCORE", 0);
	auto lblHighScore = Label::createWithSystemFont(StringUtils::format("%08d", highScore),"msyhbd.ttc",48);
	lblHighScore->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	lblHighScore->setPosition(VISIBLE_SIZE.width - 20, VISIBLE_SIZE.height*0.345); //0.445
	this->addChild(lblHighScore);
	lblHighScore->setColor(Color3B::WHITE);

	//如果读取到的最高分没有当前的得分值高。那么，更新最高得分且写入到配置文件中
	if (highScore < pt)
	{
		highScore = pt;
		UserDefault::getInstance()->setIntegerForKey("AVOIDLINEHIGHSCORE", highScore);

		lblHighScore->setString(StringUtils::format("%08d", highScore));

		auto highScorepic = Sprite::createWithSpriteFrameName("newRecord1.png");
		highScorepic->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		highScorepic->setPosition(VISIBLE_SIZE.width - 10, VISIBLE_SIZE.height*0.27);
		highScorepic->setScale(0.3);
		this->addChild(highScorepic,13);

		auto scaleIn = ScaleTo::create(0.5f, 0.6);
		auto scaleOut = ScaleTo::create(0.5f, 0.4);
		highScorepic->runAction(Sequence::create(scaleIn, scaleOut, NULL));
	}
	//重玩游戏
	Sprite* back;
	Sprite* mainMenu;
	switch (ty)
	{
	case BIRD:
		back = Sprite::createWithSpriteFrameName("again1.png");
		mainMenu = Sprite::createWithSpriteFrameName("menu1.png");
		break;
	case FIRE:
		back = Sprite::createWithSpriteFrameName("again2.png");
		mainMenu = Sprite::createWithSpriteFrameName("menu2.png");
		break;
	}

	auto menuItemRestart = MenuItemSprite::create(back, back, [ty](Ref *){
		auto scene = GameScene::createScene(ty,false);
		Director::getInstance()->replaceScene(scene);
	});
	menuItemRestart->setPosition(20,20);
	menuItemRestart->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	menuItemRestart->setScale(0.4);
	auto menu = Menu::create(menuItemRestart, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);
	//返回主菜单
	
	auto menuItemMainMenu = MenuItemSprite::create(mainMenu, mainMenu, [](Ref *){
		auto scene = StartScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});
	menuItemMainMenu->setPosition(VISIBLE_SIZE.width-20,20);
	menuItemMainMenu->setAnchorPoint(Point::ANCHOR_BOTTOM_RIGHT);
	menuItemMainMenu->setScale(0.4);
	menu = Menu::create(menuItemMainMenu, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	return true;
}
void EndScene::update(float){
	
}