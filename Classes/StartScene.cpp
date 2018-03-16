#include "StartScene.h"
#include "cocos2d.h"
using namespace CocosDenshion;

StartScene::StartScene(){
	
}
Scene* StartScene::createScene()
{
	auto scene = Scene::create();//����һ����ͨ�ĳ���
	auto layer = StartScene::create();//�������ǵĲ�
	scene->addChild(layer);//�����ǵĲ�ӵ����������
	return scene;
}
StartScene* StartScene::create()//CREATE_FUNC(StartScene);
{
	StartScene* pRet = new StartScene();
	if(pRet && pRet->init())
	{
		pRet->autorelease();//����������Զ���ճ����棬�����Զ���գ�����Ҫ�����ֶ���delete
		return pRet;
	}else{
		delete pRet;
		pRet = nullptr; //NULL
		return nullptr;
	}
}
bool StartScene::init(){
	if(!Layer::init()){
		return false;
	}

	FileUtils::getInstance()->addSearchPath("bg"); //�ļ�·��
	FileUtils::getInstance()->addSearchPath("fonts");
	FileUtils::getInstance()->addSearchPath("mu");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("AllButton.plist");//��plist�ļ������������ȥ
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("hero.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("item.plist");
	m_keyBackFlag = false;  
		/*-----------------------------------*/
	//�������ؼ�
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(StartScene::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	


	/*-----------------------------------*/


	saveAnimation();
	saveSound();
	srand(time(0));
	
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.29);
	SimpleAudioEngine::getInstance()->playBackgroundMusic("main.mp3", true);


	
	auto bg1 = Sprite::create("WelcomeScene.jpg");
	bg1->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	bg1->setScaleX(VISIBLE_SIZE.width/bg1->getBoundingBox().size.width);
	bg1->setScaleY(VISIBLE_SIZE.height/bg1->getBoundingBox().size.height);
	bg1->setVisible(true);
	this->addChild(bg1, 1, 19001);
	auto bg2 = Sprite::create("select.jpg");
	bg2->setScaleX(VISIBLE_SIZE.width/bg2->getBoundingBox().size.width);
	bg2->setScaleY(VISIBLE_SIZE.height/bg2->getBoundingBox().size.height);
	bg2->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	bg2->setVisible(false);
	this->addChild(bg2, 1, 19002);

	auto st = Sprite::createWithSpriteFrameName("ok1.png");
	st->setScale(0.0001);
	st->setTextureRect(Rect(0,0,VISIBLE_SIZE.width,VISIBLE_SIZE.width*0.6));
	auto menuItemStart = MenuItemSprite::create(st,st,CC_CALLBACK_1(StartScene::chooseStart,this));
	menuItemStart->setAnchorPoint(Point::ANCHOR_MIDDLE);
	menuItemStart->setPosition(VISIBLE_SIZE.width*0.5,VISIBLE_SIZE.height*0.382);
	menuItemStart->setTag(20001);
	menuItemStart->setVisible(true);
	auto hero1 = Sprite::createWithSpriteFrameName("ok1.png");

	auto menuItemChooseHero1 = MenuItemSprite::create(hero1,hero1,CC_CALLBACK_1(StartScene::chooseHero1,this));
	menuItemChooseHero1->setAnchorPoint(Point::ANCHOR_MIDDLE);
	menuItemChooseHero1->setPosition(VISIBLE_SIZE.width*0.25,VISIBLE_SIZE.height*0.3);
	menuItemChooseHero1->setTag(20011);
	menuItemChooseHero1->setVisible(false);
	menuItemChooseHero1->setScale(0.4);
	auto hero2 = Sprite::createWithSpriteFrameName("ok2.png");

	auto menuItemChooseHero2 = MenuItemSprite::create(hero2,hero2,CC_CALLBACK_1(StartScene::chooseHero2,this));
	menuItemChooseHero2->setAnchorPoint(Point::ANCHOR_MIDDLE);
	menuItemChooseHero2->setPosition(VISIBLE_SIZE.width*0.75,VISIBLE_SIZE.height*0.3);
	menuItemChooseHero2->setTag(20012);
	menuItemChooseHero2->setVisible(false);
	menuItemChooseHero2->setScale(0.4);
	auto backToMainMenu = Sprite::createWithSpriteFrameName("menu1.png");

	auto menuItembackToMainMenu = MenuItemSprite::create(backToMainMenu,backToMainMenu,CC_CALLBACK_1(StartScene::chooseBackToMainMenu,this));
	menuItembackToMainMenu->setAnchorPoint(Point::ANCHOR_MIDDLE);
	menuItembackToMainMenu->setPosition(VISIBLE_SIZE.width*0.5,VISIBLE_SIZE.height*0.1);
	menuItembackToMainMenu->setTag(20013);
	menuItembackToMainMenu->setScale(0.4);
	menuItembackToMainMenu->setVisible(false);
	
	allMenu = Menu::create(menuItemStart,menuItemChooseHero1,menuItemChooseHero2,menuItembackToMainMenu,NULL);
	allMenu->setPosition(Point::ZERO);
	allMenu->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	this->addChild(allMenu,2,45001);

	this->scheduleUpdate();
	return true;
}
void StartScene::chooseStart(Ref*){
	auto am = this->getChildByTag(45001);
	auto st = am->getChildByTag(20001);
	auto h1 = am->getChildByTag(20011);
	auto h2 = am->getChildByTag(20012);
	auto bm = am->getChildByTag(20013);
	auto bg1= this->getChildByTag(19001);
	auto bg2= this->getChildByTag(19002);
	st->setVisible(false);
	h1->setVisible(true);
	h2->setVisible(true);
	bm->setVisible(true);
	bg1->setVisible(false);
	bg2->setVisible(true);
}
void StartScene::chooseHero1(Ref*){
	chosenHero = BIRD;
	log("hero1");
	auto callFunc = CallFunc::create([this](){
			auto scene = GameScene::createScene(BIRD,true);
			Director::getInstance()->replaceScene(scene);
	});
	this->runAction(Sequence::create(callFunc,NULL));
}
void StartScene::chooseHero2(Ref*){
	chosenHero = FIRE;
	auto callFunc = CallFunc::create([this](){
			auto scene = GameScene::createScene(FIRE,true);
			Director::getInstance()->replaceScene(scene);
	});
	this->runAction(Sequence::create(callFunc,NULL));
	log("hero2");
}
void StartScene::chooseBackToMainMenu(Ref*){
	auto am = this->getChildByTag(45001);
	auto st = am->getChildByTag(20001);
	auto h1 = am->getChildByTag(20011);
	auto h2 = am->getChildByTag(20012);
	auto bm = am->getChildByTag(20013);
	auto bg1= this->getChildByTag(19001);
	auto bg2= this->getChildByTag(19002);
	st->setVisible(true);
	h1->setVisible(false);
	h2->setVisible(false);
	bm->setVisible(false);
	bg1->setVisible(true);
	bg2->setVisible(false);
}
void StartScene::saveAnimation(){
	auto animation1 = Animation::create();//��Ӷ���
	auto animation2 = Animation::create();//��Ӷ���
	animation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero1_miss.png"));//����ЩͼƬ���붯��
	animation2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero1_miss.png"));    
	animation2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero1.png"));    
	
	animation1->setDelayPerUnit(IMMUNE_TIME);//�л���Ƶ�� ��λ��
	animation1->setLoops(1);//�л��������� -1Ϊ����
	animation2->setDelayPerUnit(0.15f);//�л���Ƶ�� ��λ��
	animation2->setLoops(10);//�л��������� -1Ϊ����
	AnimationCache::getInstance()->addAnimation(animation1, "hero1Immune");//��Ϊ��������ִ�У��������ڶ��������л�������
	AnimationCache::getInstance()->addAnimation(animation2, "hero1ReadyToOutImmune");//��Ϊ��������ִ�У��������ڶ��������л�������

	animation1 = Animation::create();
	animation2 = Animation::create();
	animation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero2_miss.png"));//����ЩͼƬ���붯��
	animation2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero2_miss.png"));    
	animation2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero2.png"));    
	animation1->setDelayPerUnit(IMMUNE_TIME);//�л���Ƶ�� ��λ��
	animation1->setLoops(1);//�л��������� -1Ϊ����
	animation2->setDelayPerUnit(0.15f);//�л���Ƶ�� ��λ��
	animation2->setLoops(10);//�л��������� -1Ϊ����
	AnimationCache::getInstance()->addAnimation(animation1, "hero2Immune");//��Ϊ��������ִ�У��������ڶ��������л�������
	AnimationCache::getInstance()->addAnimation(animation2, "hero2ReadyToOutImmune");//��Ϊ��������ִ�У��������ڶ��������л�������

	auto animation = Animation::create();
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero1_down1.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero1_down2.png"));
	animation->setDelayPerUnit(0.3);//�л���Ƶ�� ��λ��
	animation->setLoops(1);//�л��������� -1Ϊ����
	AnimationCache::getInstance()->addAnimation(animation, "hero1GameOver");

	animation = Animation::create();
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero2_down1.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero2_down2.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero2_down3.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero2_down4.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero2_down5.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero2_down6.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero2_down7.png"));
	animation->setDelayPerUnit(0.1);//�л���Ƶ�� ��λ��
	animation->setLoops(1);//�л��������� -1Ϊ����
	AnimationCache::getInstance()->addAnimation(animation, "hero2GameOver");
}
void StartScene::saveSound(){
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("main.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("hero1.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("hero2.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("hero1gameover.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("getextralife.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("getshield.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("getcoin.mp3");
	
	SimpleAudioEngine::getInstance()->preloadEffect("hero2gameover.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("lostextralife.mp3");
}
void StartScene::update(float){

}

void StartScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) 
{     
 if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE ||keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE)  
    {  
        if (!m_keyBackFlag)// �ڹ�ȥ��1����֮��û�������ؼ�����ʾ��Ϣ�ٰ�һ��  
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
                1.0f//1��֮������������ؼ�����ôm_keyBackFlag��������  
            );  
        }  
        else//�ڹ�ȥ��1����֮�������·��ؼ������ڰ����ǵڶ���  
        {  
            Director::getInstance()->end();  
        }  
    }  
}

void StartScene::change_m_keyBackFlag(float)
{

	 this->m_keyBackFlag = false; 
}