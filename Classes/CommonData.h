#pragma once

#define VISIBLE_SIZE (Director::getInstance()->getVisibleSize())
#define BORN_X (Director::getInstance()->getVisibleSize().width/2-10)
#define BORN_Y (Director::getInstance()->getVisibleSize().height*0.2)
#define HERO_TAG 10
#define SCOREBOARD_TAG 10000
#define IMMUNE_TIME 5
#define MAX_HERO_SPEED 8
#define SLOWSPEED_TIME 10
enum HERO_TYPE{BIRD,FIRE}; //玩家类型
enum BARRIER_TYPE{HORI,VERT}; //障碍类型
enum ITEM_TYPE{IMMUNE,SLOWSPEED,COIN,EXTRALIFE}; //道具类型

#define  BarrierLayer  40
#define  BarrierTag    666
#define	 RANDOM        ((float)(rand()%100))/100
#define  MINDISTANCE   120
#define  RANDOMDISTANCE   100


#define CION  "glod.png"

#define  BARRIER_1    "barrier.png"
#define  BARRIER_2    "barrier1.png"
