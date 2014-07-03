// 
//  HRocker.cpp 
//  RockerPro 
// 
//  Created by Himi on 12-3-30. 
//  Copyright (c) 2012年 Himi. All rights reserved. 
// 
#include "HRocker.h" 
  
void HRocker::updatePos(float dt){ 
    jsSprite->setPosition(ccpAdd(jsSprite->getPosition(),ccpMult(ccpSub(currentPoint, jsSprite->getPosition()),0.5))); 
} 
//启动摇杆 
void HRocker::Active() 
{ 
    if (!active) { 
        active=true; 
        schedule(schedule_selector(HRocker::updatePos));//添加刷新函数 
        //Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(this, 0,false);//添加触摸委托 
    }else { 
    } 
} 
//解除摇杆 
void   HRocker::Inactive() 
{ 
    if (active) { 
        active=false; 
        this->unschedule(schedule_selector(HRocker::updatePos));//删除刷新 
        //CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);//删除委托 
    }else { 
    } 
} 
//摇杆方位 
CCPoint HRocker::getDirection() 
{ 
    return ccpNormalize(ccpSub(centerPoint, currentPoint)); 
} 
//摇杆力度 
float HRocker::getVelocity() 
{ 
    return ccpDistance(centerPoint, currentPoint); 
} 
HRocker* HRocker:: HRockerWithCenter(CCPoint aPoint ,float aRadius ,CCSprite* aJsSprite,CCSprite* aJsBg,bool _isFollowRole){ 
    HRocker *jstick=HRocker::create(); 
    jstick->initWithCenter(aPoint,aRadius,aJsSprite,aJsBg,_isFollowRole); 
    return jstick; 
} 
//bool HRocker::onTouchBegan(CCTouch* touch, CCEvent* event) 
//{ 
//  
//    if (!active) 
//        return false; 
//	this->setVisible(true);
//	CCPoint touchPoint = touch->getLocationInView();// locationInView(touch->view());
//    touchPoint = CCDirector:: sharedDirector()->convertToGL(touchPoint); 
//    if(!isFollowRole){ 
//        if (ccpDistance(touchPoint, centerPoint) > radius){ 
//            return false; 
//        } 
//    } 
//    currentPoint = touchPoint; 
//    if(isFollowRole){ 
//        centerPoint=currentPoint; 
//        jsSprite->setPosition(currentPoint); 
//        this->getChildByTag(88)->setPosition(currentPoint); 
//    } 
//    return true; 
//} 
//void  HRocker::onTouchMoved(CCTouch* touch, CCEvent* event) 
//{ 
//	CCPoint touchPoint = touch->getLocationInView();// (touch->view());
//    touchPoint = CCDirector:: sharedDirector()->convertToGL(touchPoint); 
//    if (ccpDistance(touchPoint, centerPoint) > radius) 
//    { 
//        currentPoint =ccpAdd(centerPoint,ccpMult(ccpNormalize(ccpSub(touchPoint, centerPoint)), radius)); 
//    }else { 
//        currentPoint = touchPoint; 
//    } 
//} 
//void  HRocker::onTouchEnded(CCTouch* touch, CCEvent* event) 
//{ 
//    currentPoint = centerPoint; 
//    if(isFollowRole){ 
//        this->setVisible(false); 
//    } 
//} 
// 
//void HRocker::onTouchCancelled(Touch *touch, Event *unused_event)
//{}
//  
HRocker* HRocker::initWithCenter(CCPoint aPoint ,float aRadius ,CCSprite* aJsSprite,CCSprite* aJsBg,bool _isFollowRole){ 
  
    isFollowRole =_isFollowRole; 
    active = false; 
    radius = aRadius; 
    if(!_isFollowRole){ 
        centerPoint =aPoint; 
    }else{ 
        centerPoint =ccp(0,0); 
    } 
  
    currentPoint = centerPoint; 
    jsSprite = aJsSprite; 
	bgSprite = aJsBg;
    jsSprite->setPosition(centerPoint); 
    aJsBg->setPosition(centerPoint); 
    aJsBg->setTag(88); 
    this->addChild(aJsBg); 
    this->addChild(jsSprite); 
    if(isFollowRole){ 
		this->setVisible(false);
    } 
    //this->onEnter();//激活摇杆 
    return this; 
} 

void HRocker::onEnter() {
	Layer::onEnter();
	auto listener = EventListenerTouchOneByOne::create();
	// OnTouchBegan吞没
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [=](Touch* touch, Event* event){
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point touchLoc = target->convertToNodeSpace(touch->getLocation());
		Size s = this->jsSprite->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(touchLoc))
		{
			//this->setVisible(false);
			return true;
		}
		return false;
	};

	listener->onTouchMoved = [=](Touch* touch, Event* event){
		//Rect rect = Rect(0, 0, bgSprite->getContentSize().width, bgSprite->getContentSize().height);
		Point touchPoint = this->jsSprite->getPosition() + touch->getDelta();
		//Point centerPoint = this->bgSprite->getPosition();
		//Point currPoint;
		if (ccpDistance(touchPoint, centerPoint) > radius)
		{ 
			currentPoint =ccpAdd(centerPoint,ccpMult(ccpNormalize(ccpSub(touchPoint, centerPoint)), radius)); 
		}else { 
			currentPoint = touchPoint; 
		} 

		this->jsSprite->setPosition(currentPoint);

		//this->_gameLayer
	};

	listener->onTouchEnded = [=](Touch* touch, Event* event){
		float cost_time = centerPoint.getDistance(currentPoint) / radius * 0.1;
		this->jsSprite->runAction(MoveTo::create(cost_time, centerPoint));
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, jsSprite);
}