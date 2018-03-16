#include "GameScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

GameScene::GameScene(){
	srand(time(0));
	isGameOver = 0;
	isPaused = false;
	totalPoint = 0;
//	horiCount = vertCount = horiRandomCount = vertRandomCount = 0;
	floatBarrierDistance = 0;
}
Scene* GameScene::createScene(HERO_TYPE ty,bool playNewBGM)
{
	auto scene = Scene::create();//创建一个普通的场景
	auto layer = GameScene::create(ty,playNewBGM);//创建我们的层
	scene->addChild(layer);//将我们的层加到这个场景中
	return scene;
}
GameScene* GameScene::create(HERO_TYPE ty,bool playNewBGM)//CREATE_FUNC(GameScene);
{
	GameScene* pRet = new GameScene();
	if(pRet && pRet->init(ty,playNewBGM))
	{
		pRet->autorelease();//将对象放入自动清空池里面，它会自动清空，不需要我们手动的delete
		return pRet;
	}else{
		delete pRet;
		pRet = nullptr; //NULL
		return nullptr;
	}
}
bool GameScene::init(HERO_TYPE ty,bool playNewBGM){
	if(!Layer::init()){
		return false;
	}
	beganFlag=LRflag=0;
	m_keyBackFlag=false;

	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	createHero(ty);
	createBackground();
	createTouchListener();
	createScoreBoard();
	switch(hero->getType()){
	case BIRD:
		if(playNewBGM){
			SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.3);
			SimpleAudioEngine::getInstance()->playBackgroundMusic("hero1.mp3",true);
		}
		break;
	case FIRE:
		if(playNewBGM){
			SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.3);
			SimpleAudioEngine::getInstance()->playBackgroundMusic("hero2.mp3",true);
		}
		break;
	}
	

	this->schedule(schedule_selector(GameScene::createItemCoin),2);
	this->schedule(schedule_selector(GameScene::createItemSlowspeed),51.3,-1,30.6);
	this->schedule(schedule_selector(GameScene::createItemExtraLife),98.2,-1,46.2);
	this->schedule(schedule_selector(GameScene::createItemImmune),73.2,-1,61.8);
	this->schedule(schedule_selector(GameScene::createRoute),0.01f);
	this->schedule(schedule_selector(GameScene::createFloatBarrierUpdate),0.1f);
	this->schedule(schedule_selector(GameScene::createVerticalBarrierUpdate),0.001f,-1,0.01);


	this->scheduleUpdate();//调用当前层的定时器，该定时器与FPS有关
	return true;
}

void GameScene::update(float){
	if(isGameOver == 1){
		isGameOver = 2;
		Animation* animation;
		switch (hero->getType())
		{
		case BIRD:
			SimpleAudioEngine::getInstance()->setEffectsVolume(0.1);
			SimpleAudioEngine::getInstance()->playEffect("hero1gameover.mp3");
			animation = AnimationCache::getInstance()->getAnimation("hero1GameOver");
			break;
		case FIRE:
			SimpleAudioEngine::getInstance()->setEffectsVolume(0.1);
			SimpleAudioEngine::getInstance()->playEffect("hero2gameover.mp3");
			animation = AnimationCache::getInstance()->getAnimation("hero2GameOver");
			break;
		}
		auto animate = Animate::create(animation);
		auto callFunc = CallFunc::create([this](){
			auto scene = EndScene::createScene(hero->getType(),this->totalPoint+1);
			Director::getInstance()->replaceScene(scene);
		});
		hero->stopAllActions();
		MoveBy* move1;
		MoveBy* move2;
		MoveBy* move3;
		MoveBy* move4;
		switch (hero->getType())
		{
		case BIRD:
			move1 = MoveBy::create(0.1f,Vect(0,10));
			move2 = MoveBy::create(0.1f,Vect(0,-10));
			move3 = MoveBy::create(0.3f,Vect(0,-BORN_Y/4));
			move4 = MoveBy::create(0.3f,Vect(0,-3*BORN_Y/4));
			move4 = MoveBy::create(0.3f,Vect(0,-5*BORN_Y/4));
			move4 = MoveBy::create(0.3f,Vect(0,-7*BORN_Y/4));
			hero->runAction(Sequence::create(move1,move2,move1,move2,move1,move2,animate,move3,move4,callFunc, NULL));
			break;
		case FIRE:
			move4 = MoveBy::create(0.3f,Vect(0,0));
			hero->runAction(Sequence::create(animate,move4,callFunc, NULL));
			break;
		}
	}
	else if(!isGameOver){
		moveBackground();
		moveHero();
		moveBarrier();
		moveItem();
		moveRoute();
		judgeHeroAndBarrier();
		updateScoreBoard();
		speedUp();
	}
}
void GameScene::createBackground(){
	backgroundSpeed = 0;
	std::string backgroundName;
	switch (hero->getType())
	{
	case BIRD:
		backgroundName = "bg1.jpg";
		break;
	case FIRE:
		backgroundName = "bg2.jpg";
		break;
	}

	auto bg1 = Sprite::create(backgroundName);
	
	bg1->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);//设置锚
	bg1->setPosition(0,0);
	bg1->getTexture()->setAliasTexParameters();//抗锯齿
	bg1->setScaleX(VISIBLE_SIZE.width/bg1->getTextureRect().size.width);
	
	this->addChild(bg1,1,1);//将精灵加入该层里面


	auto bg2 = Sprite::create(backgroundName);
	
	bg2->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);//设置锚
	bg2->setPosition(0, bg1->getTextureRect().size.height);
	bg2->getTexture()->setAliasTexParameters();//抗锯齿
	bg2->setScaleX(VISIBLE_SIZE.width/bg2->getTextureRect().size.width);
	this->addChild(bg2,1,2);//将精灵加入该层里面
}

void GameScene::createHero(HERO_TYPE ty){
	hero = Hero::create(ty);
	Animation* animation;
	switch (hero->getType())
	{
	case BIRD:
		animation = AnimationCache::getInstance()->getAnimation("hero1ReadyToOutImmune");
		break;
	case FIRE:
		animation = AnimationCache::getInstance()->getAnimation("hero2ReadyToOutImmune");
		break;
	}
	auto animate=Animate::create(animation);
	hero->runAction(animate);
	this->addChild(hero,9999,HERO_TAG);
}
void GameScene::createTouchListener(){
	//添加触摸事件
	//创建单点触摸事件监听器
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch *touch, Event *event){ //开始事件
//		log("start");
		return !isGameOver && !isPaused;
	};
	listener->onTouchMoved = [](Touch *touch, Event *event){ //移动事件 只在开始事件true时调用

	};
	listener->onTouchEnded = [this](Touch *touch, Event *event){//结束事件 只在开始事件true时调用
//		log("end");
		hero->setToRight(-hero->isToRight());
	};
	//为场景绑定移动事件
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);	
}
void GameScene::createScoreBoard(){
	FileUtils::getInstance()->addSearchPath("fonts");
	auto lblScoreNumber = Label::createWithSystemFont("Score:00000000", "msyh.ttc", 24);
	lblScoreNumber->setPosition(10 , VISIBLE_SIZE.height-10);
	lblScoreNumber->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
	lblScoreNumber->setColor(Color3B::WHITE);
	this->addChild(lblScoreNumber, 99, SCOREBOARD_TAG);
}

void GameScene::createItemSlowspeed(float){
	createItemByType(SLOWSPEED);
}
void GameScene::createItemImmune(float){
	createItemByType(IMMUNE);
}
void GameScene::createItemExtraLife(float){
	createItemByType(EXTRALIFE);
}
void GameScene::createItemCoin(float){
	createItemByType(COIN);
}
void GameScene::createItemByType(ITEM_TYPE ty){
	if(isGameOver)	return;
	int x;
	bool flag=false;
	auto item = Item::create(ty);
	do{
		x=rand()%(int)(VISIBLE_SIZE.width-10)+10;
		item = Item::create(ty);
		item->setPosition(x,VISIBLE_SIZE.height+item->getBoundingBox().size.height);
		flag = false;

		for(auto e:vFloatBarrier){
			if(e->getBoundingBox().intersectsRect(item->getBoundingBox()))
				flag = true;
		}
		for(auto e:vVerticalBarrier){
			if(e->getBoundingBox().intersectsRect(item->getBoundingBox()))
				flag = true;
		}
		
	}while(flag);
	
	this->addChild(item,20);
	allItem.pushBack(item);
}
void GameScene::createRoute(float){
	if(isGameOver || isPaused) return;
	auto route = Route::create(hero->getType(),hero->getPositionX(),hero->getPositionY());
	this->addChild(route,13);
	allRoute.pushBack(route);
}
//---------------------------------------------------------------------------------------
void GameScene::moveHero(){//移动玩家 判定玩家是否出界
	if(hero->haveExtraLife()){
		auto p = this->getChildByTag(201);
		p->setPositionX(hero->getPositionX() + hero->isToRight() * hero->getSpeed());
		if(hero->getType() == FIRE){
			p->setPositionX(p->getPositionX() + hero->isToRight()*10);
			p->setPositionY(hero->getPositionY()+10);
		}
	}
	hero->setPositionX(hero->getPositionX() + hero->isToRight() * hero->getSpeed());
	hero->setRotation(hero->isToRight()*45);
	switch (hero->getType())
	{
	case BIRD:
		hero->setScaleX(-hero->isToRight()*0.45);
		break;
	case FIRE:
		hero->setScaleX(-hero->isToRight()*0.2);
		break;
	}
	
	if(hero->getPositionX()< 0 || hero->getPositionX() > VISIBLE_SIZE.width){
		isGameOver = 1;
		log("Game Over");
	}
	if(hero->getSlowSpeedTime()){
		if(hero->getSlowSpeedTime() > (SLOWSPEED_TIME+2)*60){
			hero->setSpeed(hero->getSpeed() - 0.012);
		}
		if(hero->getSlowSpeedTime() < 2*60){
			hero->setSpeed(hero->getSpeed() + 0.012);
		}
		hero->setSlowSpeedTime(hero->getSlowSpeedTime()-1);
	}
	if(hero->getImmuneTime()){
		hero->setImmuneTime(hero->getImmuneTime()-1);
	}
}
void GameScene::moveBackground(){//移动背景
	auto bg1 = this->getChildByTag(1);
	auto bg2 = this->getChildByTag(2);
	setBackgroundSpeed(hero->getSpeed()*0.15);

	bg1->setPositionY(bg1->getPositionY() - backgroundSpeed);
	bg2->setPositionY(bg1->getPositionY()+bg1->getContentSize().height);
	if(bg2->getPositionY() < 0)
	{
		bg1->setPositionY(0);

	}
}

/*void GameScene::moveBarrier(){//移动障碍物 判定玩家是否碰到障碍物
	Vector<Barrier*> delBarrier;
	float step = hero->getSpeed();
	for(auto e:allBarrier){
		e->setPositionY(e->getPositionY() - step);
		if(e->getPositionY() < -20){
			delBarrier.pushBack(e);	
			this->removeChild(e);	
		}
		if(e->getBoundingBox().containsPoint(hero->getPosition())){
			if(hero->getImmuneTime() > 0){
				delBarrier.pushBack(e);	
				this->removeChild(e);
			}
			else if(hero->haveExtraLife()){
				hero->setExtraLife(false);
				delBarrier.pushBack(e);	
				this->removeChild(e);
			}
			else{
				isGameOver = true;
				log("Game Over");
			}
		}
	}
	for(auto e : delBarrier)
		this->allBarrier.eraseObject(e);	
}*/
void GameScene::moveItem(){//移动道具 判定玩家是否吃到道具
	Vector<Item*> delItem;
	float step = hero->getSpeed();
	Animation* animation1;
	Animation* animation2;
	Animate* action1;
	Animate* action2;
	for(auto e:allItem){
		e->setPositionY(e->getPositionY() - step);
		if(e->getBoundingBox().containsPoint(hero->getPosition())){
			ITEM_TYPE ty = e->getType();
			switch (ty)
			{
			case IMMUNE:
				hero->setImmuneTime((IMMUNE_TIME + 3) * 60); // 3秒恢复预备
				switch (hero->getType())
				{
				case BIRD:
					animation1 = AnimationCache::getInstance()->getAnimation("hero1Immune");
					animation2 = AnimationCache::getInstance()->getAnimation("hero1ReadyToOutImmune");
					break;
				case FIRE:
					animation1 = AnimationCache::getInstance()->getAnimation("hero2Immune");
					animation2 = AnimationCache::getInstance()->getAnimation("hero2ReadyToOutImmune");
					break;
				}
				action1 = Animate::create(animation1);//将动画转换为动作
				action2 = Animate::create(animation2);//将动画转换为动作hero1gameover.mp3
				hero->stopAllActions();
				hero->runAction(Sequence::create(action1, action2, NULL));//执行动作
				SimpleAudioEngine::getInstance()->setEffectsVolume(0.1);
				SimpleAudioEngine::getInstance()->playEffect("getshield.mp3");
				break;
			case SLOWSPEED:
				if(hero->getSlowSpeedTime() == 0)
					hero->setSlowSpeedTime((SLOWSPEED_TIME + 4) * 60); // 2秒前摇 2秒恢复预备
				else
					hero->setSlowSpeedTime((SLOWSPEED_TIME + 2) * 60); // 2秒恢复预备
				SimpleAudioEngine::getInstance()->setEffectsVolume(0.1);
				SimpleAudioEngine::getInstance()->playEffect("hero1gameover.mp3");
				break;
			case COIN:
				hero->setCoin(hero->getCoin()+1);
				totalPoint += 200;
				SimpleAudioEngine::getInstance()->setEffectsVolume(0.2);
				SimpleAudioEngine::getInstance()->playEffect("getcoin.mp3");
				break;
			case EXTRALIFE:
				if(hero->haveExtraLife() == false){
					hero->setExtraLife(true);
					auto sp1 = Sprite::createWithSpriteFrameName("protect.png");
					sp1->setScale(0.5);
					sp1->setPosition(hero->getPositionX(),hero->getPositionY());
					sp1->setAnchorPoint(Point::ANCHOR_MIDDLE);
					this->addChild(sp1,13,201);
					SimpleAudioEngine::getInstance()->setEffectsVolume(0.2);
					SimpleAudioEngine::getInstance()->playEffect("getextralife.mp3");
				}
				break;
			}
			delItem.pushBack(e);	
			this->removeChild(e);
		}
		if(e->getPositionY() < -100){
			delItem.pushBack(e);	
			this->removeChild(e);	
		}
	}
	for(auto e : delItem)
		this->allItem.eraseObject(e);	
}
void GameScene::moveRoute(){//移动路线
	Vector<Route*> delRoute;
	float step = hero->getSpeed();
	for(auto e:allRoute){
		e->setPositionY(e->getPositionY() - step);
		if(e->getPositionY() < -20){
			delRoute.pushBack(e);	
			this->removeChild(e);	
		}
		e->setScale(e->getPositionY()/BORN_Y*0.5+0.3);
	}
	for(auto e : delRoute)
		this->allRoute.eraseObject(e);	
}

void GameScene::updateScoreBoard(){
	totalPoint += hero->getSpeed()*0.1;
	auto score = (Label *) this->getChildByTag(SCOREBOARD_TAG);
	score->setString(StringUtils::format("Score:%08.0f", this->totalPoint));
}
void GameScene::speedUp(){
	if(hero->getSpeed() < MAX_HERO_SPEED && hero->getSlowSpeedTime() == 0)
		hero->setSpeed(hero->getSpeed()+0.0003);
}
//---------------------------------------------------------------------------------------
float GameScene::getBackgroundSpeed(){
	return backgroundSpeed;
}
void GameScene::setBackgroundSpeed(float x){
	backgroundSpeed = x;
}

//---------------------------------------------------------------------------------------



//障碍生成

void GameScene::moveBarrier()
{
	floatBarrierDistance += hero->getSpeed();
	for(auto b :vVerticalBarrier)
	{
		b->setPositionY(b->getPositionY()-hero->getSpeed());
		if( b->getPositionY()<-b->getBoundingBox().size.height)
		{
			vRemoveBarrier.pushBack(b);
			removeChild(b,1);
		}
	}
	for(auto b : vRemoveBarrier)
	{
		vVerticalBarrier.eraseObject(b);
	}
	vRemoveBarrier.clear();

	for(auto b :vFloatBarrier)
	{
		b->setPositionY(b->getPositionY()-hero->getSpeed());
		if( b->getPositionY()<-b->getBoundingBox().size.height)
		{
			vRemoveBarrier.pushBack(b);
			removeChild(b,1);
		}
	}
	for(auto b : vRemoveBarrier)
	{
		vFloatBarrier.eraseObject(b);
	}
	vRemoveBarrier.clear();
}
Sprite * GameScene::createVerticalBarrier(float scales,float pointY)
{
	auto bg = Sprite::createWithSpriteFrameName("barrier.png");
//	auto bg =Sprite::createWithSpriteFrameName(BARRIER_1);
	bg->setScaleX(0.5);
	bg->setScaleY(scales<0.08?(scales*4+0.1):scales);
	bg->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
	bg->setPosition(VISIBLE_SIZE.width/2,pointY);
	this->addChild(bg,99);
	vVerticalBarrier.pushBack(bg);
	return bg;

}
void GameScene::createVerticalBarrierUpdate(float)
{  
	if(!(vVerticalBarrier.size()>0 && (*(vVerticalBarrier.end()-1))->getPositionY()+((*(vVerticalBarrier.end()-1))->getBoundingBox().size.height)>VISIBLE_SIZE.height))
	{
		if(!beganFlag)
		{
			createVerticalBarrier(RANDOM,0);
			beganFlag=1;
		}else
		{
			float y = (*(vVerticalBarrier.end()-1))->getPositionY()+((*(vVerticalBarrier.end()-1))->getBoundingBox().size.height);
			float x= RANDOM;
			createVerticalBarrier((x>0.6?(x-0.3):x),y+MINDISTANCE+RANDOMDISTANCE*RANDOM);
		}
	}
}
Sprite * GameScene::createFloatBarrier(float,float)
{
	auto b = Sprite::createWithSpriteFrameName("barrier1.png");
//	auto b =Sprite::createWithSpriteFrameName(BARRIER_2);
	float x=RANDOM;
	x = x<0.2?x+0.2:x;
	b->setScaleX(x>0.54?x-0.2:x);
	
	b->setScaleY(0.5);
	if(LRflag)
	{
		if(b->getScaleX()>=0.5) b->setPosition(RANDOM>0.5?b->getBoundingBox().size.width:VISIBLE_SIZE.width/2-b->getBoundingBox().size.width,VISIBLE_SIZE.height);
		else b->setPosition(rand()%((int)VISIBLE_SIZE.width/5)+VISIBLE_SIZE.width/8,VISIBLE_SIZE.height);
	LRflag=RANDOM>0.5?0:1;
	}
	else
		{
			if(b->getScaleX()>=0.5) b->setPosition(RANDOM>0.5?b->getBoundingBox().size.width+VISIBLE_SIZE.width/2:VISIBLE_SIZE.width-b->getBoundingBox().size.width,VISIBLE_SIZE.height);
			else b->setPosition(rand()%((int)VISIBLE_SIZE.width/5)+VISIBLE_SIZE.width*(6.3/8),VISIBLE_SIZE.height);
			LRflag=RANDOM>0.5?0:1;
	}
	this->addChild(b,99);
	return b;
	
}

void GameScene::createFloatBarrierUpdate(float)
{
	if(floatBarrierDistance < 300)	return;
	floatBarrierDistance = 0;
	if(!(vFloatBarrier.size()>0 && (*(vFloatBarrier.end()-1))->getPositionY()>VISIBLE_SIZE.height))
	{
		auto b = createFloatBarrier(0,0);
		vFloatBarrier.pushBack(b);
	}
}
bool  GameScene::judgeHeroAndBarrier()
{
	for (auto b : vVerticalBarrier){
		if(b->getBoundingBox().containsPoint(hero->getPosition())){
			if(hero->getImmuneTime()==0 && hero->haveExtraLife()){
				hero->setExtraLife(false);
				hero->setImmuneTime(2*60);
				auto sp1 = this->getChildByTag(201);
				this->removeChild(sp1);
				Animation* animation;
				switch (hero->getType())
				{
				case BIRD:
					animation = AnimationCache::getInstance()->getAnimation("hero1ReadyToOutImmune");
					break;
				case FIRE:
					animation = AnimationCache::getInstance()->getAnimation("hero2ReadyToOutImmune");
					break;
				}
				auto action = Animate::create(animation);//将动画转换为动作
				hero->runAction(action);//执行动作
				SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
				SimpleAudioEngine::getInstance()->playEffect("lostextralife.mp3");
			}
			else if(hero->getImmuneTime() <=0){
				isGameOver=1;
				return true;
			}
		}
	}
	for ( auto b : vFloatBarrier)
	{
		if(b->getBoundingBox().containsPoint(hero->getPosition())){
			if(hero->getImmuneTime()==0 && hero->haveExtraLife()){
				hero->setExtraLife(false);
				hero->setImmuneTime(2*60);
				auto sp1 = this->getChildByTag(201);
				this->removeChild(sp1);
				Animation* animation;
				switch (hero->getType())
				{
				case BIRD:
					animation = AnimationCache::getInstance()->getAnimation("hero1ReadyToOutImmune");
					break;
				case FIRE:
					animation = AnimationCache::getInstance()->getAnimation("hero2ReadyToOutImmune");
					break;
				}
				auto action = Animate::create(animation);//将动画转换为动作
				hero->runAction(action);//执行动作
				SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
				SimpleAudioEngine::getInstance()->playEffect("lostextralife.mp3");
			}
			else if(hero->getImmuneTime() <=0){
				isGameOver=1;
				return true;
			}
		}
	}
	return false;
}




void  GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) 
{     
 if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE ||keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE)  
    {  
        if (!m_keyBackFlag)// 在过去的1秒钟之内没按过返回键，提示信息再按一次  
        {  
            LabelTTF *pMessage = LabelTTF::create("Press again to exit the Avoid Line", "Consolas", 18);
			pMessage->setPosition(Point(VISIBLE_SIZE.width/2, 30));  
            this->addChild(pMessage,9292);  
  
            auto pMessageFadeOut = FadeOut::create(1.0f);  
            auto pMessageMoveBy = MoveBy::create(2.0f, Point(0, 25));  
            auto pSpawn = Spawn::create(pMessageMoveBy, pMessageFadeOut, nullptr);  
            pMessage->runAction(pSpawn);  
  
            m_keyBackFlag = true;  
  
			this->scheduleOnce(schedule_selector(StartScene::change_m_keyBackFlag),  
                1.2f//1秒之内如果不按返回键，那么m_keyBackFlag变量重置  
            );  
        }  
        else//在过去的1秒钟之内曾按下返回键，现在按的是第二下  
        {  
            Director::getInstance()->end();  
        }  
    }  
}

void GameScene::change_m_keyBackFlag(float)
{

	 this->m_keyBackFlag = false; 
}

