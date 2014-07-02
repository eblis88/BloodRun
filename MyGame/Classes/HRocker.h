// 
//  HRocker.h 
//  RockerPro 
// 
//  Created by Himi on 12-3-30. 
//  Copyright (c) 2012年 Himi. All rights reserved. 
// 
  
#ifndef RockerPro_HRocker_h 
#define RockerPro_HRocker_h 
  
#ifndef HRocker_H 
#define HRocker_H 
#include "cocos2d.h" 
#include "HelloWorldScene.h"
  
using namespace cocos2d; 
  
class HRocker :public Layer { 
  
public : 
    //初始化 aPoint是摇杆中心 aRadius是摇杆半径 aJsSprite是摇杆控制点 aJsBg是摇杆背景 
    static HRocker*  HRockerWithCenter(CCPoint aPoint ,float aRadius ,CCSprite* aJsSprite,CCSprite* aJsBg,bool _isFollowRole); 
  
    //启动摇杆 
    void Active(); 
  
    //解除摇杆 
    void Inactive(); 


	CC_SYNTHESIZE(HelloWorld *, _gameLayer, GameLayer);
  
private: 
    HRocker * initWithCenter(CCPoint aPoint ,float aRadius ,CCSprite* aJsSprite,CCSprite* aJsBg,bool _isFollowRole); 
  
    CCPoint centerPoint;//摇杆中心 
  
    CCPoint currentPoint;//摇杆当前位置 
  
    bool active;//是否激活摇杆 
  
    float radius;//摇杆半径 
  
    CCSprite *jsSprite; 
  
    bool isFollowRole;//是否跟随用户点击 
  
    CCPoint getDirection(); 
  
    float getVelocity(); 
  
    void  updatePos(float dt); 
  
    CREATE_FUNC(HRocker); 

	void onEnter() override;

	void onExit() override
	{
		_eventDispatcher->removeEventListener(_listener);
		Layer::onExit();
	};

private:
	EventListener* _listener;
}; 
#endif 
  
#endif 