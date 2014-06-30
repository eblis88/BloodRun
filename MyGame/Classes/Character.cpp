#include "Character.h"
#include "DataModelBase.h"
#include <Npc.h>
#include <Gun.h>
#include <bmath.h>

Character::Character() : _dirSprite(nullptr)
{
	// 走路动画
	{
		SpriteFrameCache* cache = SpriteFrameCache::getInstance();
		if (cache->getSpriteFrameByName("Player.00.png") == nullptr)
			cache->addSpriteFramesWithFile("assets.plist", "assets.png");

		_shootframe = SpriteFrameCache::getInstance()->getSpriteFrameByName("PlayerShoot.png");

		_splitAniFrame.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Player03.png"));
		_splitAniFrame.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Player04.png"));
		_splitAniFrame.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Player03.png"));
		_splitAniFrame.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Player02.png"));
		_splitAniFrame.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Player01.png"));
		_splitAniFrame.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Player02.png"));

		_currFrame = 0;
	}

	Vector<SpriteFrame*> _gunFireFrame;
	// 射击光效
	{
		_gunFireFrame.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("gunfire00.png"));
		_gunFireFrame.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("gunfire02.png"));
		_gunFireFrame.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("gunfire01.png"));
		_gunFireFrame.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("gunfire03.png"));/*
		_gunFireFrame.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("gunfire04.png"));
		_gunFireFrame.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("gunfire05.png"));*/
	}

	Animation* gunFireAnimation = Animation::createWithSpriteFrames(_gunFireFrame, 0.05);

	auto ani_cache = AnimationCache::getInstance();
	ani_cache->addAnimation(gunFireAnimation, "gunFire");

	/*_animation = cache->getAnimation("Player");
	_animation->setDelayPerUnit(2.8/14);
	_animation->setRestoreOriginalFrame(true);*/

	_npc_sprite = createWithAssets("Player02.png");
	_npc_sprite->setAnchorPoint(Vec2(0.25,0.5));


	_dirSprite = createWithAssets("Arrow1.png");
	_dirSprite->setAnchorPoint(Vec2(0, 0.5));

	this->addChild(_npc_sprite);
	this->addChild(_dirSprite, 2);

	npc_init();

	_faceAngle = 0;
	_rotateAngle = 10;
	_rotateSpd = 0.1;
	_moveStep = 0.1;
	_moveSpd = 2;

	/*PhysicsBody* body = PhysicsBody::createBox(_charSprite->getContentSize());
	_charSprite->setPhysicsBody(body);*/

	initGun();
}

void Character::initGun()
{
	_gun = new Gun(23);
}

void Character::changeGun(int type)
{
	if (_gun != nullptr)
		delete _gun;
	_gun = new Gun(type);
}


//void Character::addToNode(Layer* layer)
//{
//	layer->addChild(_npc_sprite);
//	layer->addChild(_dirSprite);
//}

void Character::walkTo(int x, int y, float velocity, float intensity)
{
	float angleRadians = batan2((float)y, (float)x);
	float angleDegrees = CC_RADIANS_TO_DEGREES(angleRadians);
	float cocosAngle = angleDegrees;
	/*if (x < 0){
		cocosAngle = 180 + cocosAngle;
	}*/
	if (cocosAngle >= 360) cocosAngle -= 360;
	if (cocosAngle < 0) cocosAngle += 360;

#if(CC_TARGET_PLATFORM != CC_PLATFORM_WIN32) 
	_dirSprite->stopAllActions();
	_npc_sprite->stopAllActions();
#endif

	rotateWithAction(cocosAngle, 1, false);
	_dirSprite->setRotation(-_faceAngle-this->getRotation());

	auto moveTo = getMoveAction();
/*
	auto ani_cache = AnimationCache::getInstance();
	auto aniTo = Animate::create(ani_cache->getAnimation("Player_Walk"));*/
	this->_currFrame ++;
	if (_currFrame >= _splitAniFrame.size()*12)
		_currFrame = 0;

	//@todo 将脚的帧和上半身帧独立得拆开
	//@todo 后座力只影响上半身
	_npc_sprite->setSpriteFrame(_splitAniFrame.at((int)((float)_currFrame/12)));
	
	//_dirSprite->runAction(rotateTo);
	this->runAction(moveTo);
}

Character::~Character()
{
	delete _gun;
}

void Character::setRotation(float angle)
{
	this->Node::setRotation(angle);
	_dirSprite->setRotation(-_faceAngle - angle);
}

//void Character::setPosition(const Vec2& pos)
//{
//	_npc_sprite->setPosition(pos);
//	_dirSprite->setPosition(pos);
//}

void Character::shoot(const Vec2& shootAngle)
{
	// 产生后座力
	Vector<SpriteFrame*> fireFrame;
	_shootframe->setOffset(-_gun->getRecoilDiff() * Vec2(1,0));

	fireFrame.pushBack(_shootframe);
	//fireFrame.pushBack(_npc_sprite->getSpriteFrame());
	auto ani_action = Animation::createWithSpriteFrames(fireFrame,0.2);
	ani_action->setRestoreOriginalFrame(true);

	_npc_sprite->runAction(Animate::create(ani_action));

	// 枪口喷火
	auto ani_cache = AnimationCache::getInstance()->getAnimation("gunFire");
	auto aniTo = Animate::create(ani_cache);

	Sprite* gun_fire = createWithAssets("gunfire00.png");
	addChild(gun_fire,1);
	gun_fire->setPosition(Vec2(28,-1));

	//gun_fire->setPosition();
	gun_fire->runAction(
		Sequence::create(
			aniTo,
			CallFuncN::create([&](Ref* sender){
					((Sprite*)sender)->removeFromParentAndCleanup(true);}),
			NULL
		)
	);

					
	_gun->setLeftBullets(_gun->getLeftBullets() - 1);
}