//#include "HRocker.h"
//
//void HRocker::updatePos(float dt){
//    jsSprite->setPosition(
//            ccpAdd(
//                jsSprite->getPosition(), 
//                ccpMult(
//                        ccpSub(currentPoint, jsSprite->getPosition()), 0.5
//                    )
//            )
//        );
//}
//
////����ҡ��
//void HRocker::Active()
//{
//    if (!active) {
//        active = true;
//        schedule(schedule_selector(HRocker::updatePos));//���ˢ�º���
//		this->_eventDispatcher->addEventListener(this);//��Ӵ���ί��
//    }else {
//        //
//    }
//}
//
////���ҡ��
//void   HRocker::Inactive()
//{
//    if (active) {
//        active = false;
//        this->unschedule(schedule_selector(HRocker::updatePos));//ɾ��ˢ��
//        CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);//ɾ��ί��
//    }else {
//        //
//    }
//}
//
////ҡ�˷�λ
//CCPoint HRocker::getDirection()
//{
//    return ccpNormalize(ccpSub(centerPoint, currentPoint));
//}
//
////ҡ������
//float HRocker::getVelocity()
//{
//    return ccpDistance(centerPoint, currentPoint);
//}
//
//
///* ʹ�÷���
// *    ��һ������aPoint��ҡ�����ĵ������
// *    �ڶ�������aRadius: ҡ�˵İ뾶
// *    ������������aJsSprite :ҡ�˵�ͼƬ��Դ����
// *    ���ĸ�������aJsBg: ҡ�˱���ͼƬ��Դ����
// *    �����������isFollowRole���Ƿ���ҡ����Զ�����û������㣨Himi����ӵĹ��ܣ�
// */
//HRocker* HRocker:: HRockerWithCenter(CCPoint aPoint, float aRadius, CCSprite* aJsSprite, CCSprite* aJsBg, bool _isFollowRole)
//{
//	HRocker *jstick = HRocker::create();
//    jstick->initWithCenter(aPoint, aRadius, aJsSprite, aJsBg, _isFollowRole);
//    return jstick;
//}
//
//bool HRocker::ccTouchBegan(CCTouch* touch, CCEvent* event)
//{
//    if (!active)
//    {
//        return false;
//    }
//	this->setVisible(true);
//	CCPoint touchPoint = touch->getLocationInView();
//	//touch->locationInView(touch->view());
//    touchPoint = CCDirector:: sharedDirector()->convertToGL(touchPoint);
//    if(!isFollowRole){
//        if (ccpDistance(touchPoint, centerPoint) > radius){
//            return false;
//        }
//    }
//    currentPoint = touchPoint;
//    if(isFollowRole){
//        centerPoint = currentPoint;
//        jsSprite->setPosition(currentPoint);
//        this->getChildByTag(88)->setPosition(currentPoint);
//    }
//    return true;
//}
//
//void  HRocker::ccTouchMoved(CCTouch* touch, CCEvent* event)
//{
//	CCPoint touchPoint = touch->getLocationInView();
//	//touch->locationInView(touch->view());
//    touchPoint = CCDirector:: sharedDirector()->convertToGL(touchPoint);
//    if (ccpDistance(touchPoint, centerPoint) > radius)
//    {
//        currentPoint = ccpAdd(centerPoint, ccpMult(ccpNormalize(ccpSub(touchPoint, centerPoint)), radius));
//    }else {
//        currentPoint = touchPoint;
//    }
//}
//void  HRocker::ccTouchEnded(CCTouch* touch, CCEvent* event)
//{
//    currentPoint = centerPoint;
//    if(isFollowRole){
//		this->setVisible(false);
//    }
//}
//
//
///* ��ʼ������
// *    ��һ������aPoint��ҡ�����ĵ������
// *    �ڶ�������aRadius: ҡ�˵İ뾶
// *    ������������aJsSprite :ҡ�˵�ͼƬ��Դ����
// *    ���ĸ�������aJsBg: ҡ�˱���ͼƬ��Դ����
// *    �����������isFollowRole���Ƿ���ҡ����Զ�����û������㣨Himi����ӵĹ��ܣ�
// */
//HRocker* HRocker::initWithCenter(CCPoint aPoint, float aRadius, CCSprite* aJsSprite, CCSprite* aJsBg, bool _isFollowRole)
//{
//    isFollowRole =_isFollowRole;
//    active = false;
//    radius = aRadius;
//    if(!_isFollowRole){
//        centerPoint = aPoint;
//    }else{
//        centerPoint = ccp(0,0);
//    }
//
//    currentPoint = centerPoint;
//    jsSprite = aJsSprite;
//    jsSprite->setPosition(centerPoint);
//    aJsBg->setPosition(centerPoint);
//    aJsBg->setTag(88);
//    this->addChild(aJsBg);
//    this->addChild(jsSprite);
//    if(isFollowRole){
//		this->setVisible(false);
//    }
//    this->Active();//����ҡ��
//    return this;
//}