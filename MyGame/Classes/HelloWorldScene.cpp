#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
//#include "GameOverScene.h"
#include "HRocker.h"
#include <DataModelBase.h>
#include <algorithm>
#include <functional>  
#include <bmath.h>


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	#include <windows.h>
	#define KEY_DOWN(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 1 : 0)
	#define KEY_UP(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 0 : 1)
#endif

USING_NS_CC;
//using namespace CocosDenshion;
//using namespace cocos2d::ui;

HelloWorldHud *HelloWorld::_hud = NULL;
HRocker *HelloWorld::_movejoy = NULL;
HRocker *HelloWorld::_firejoy = NULL;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
	auto scene = Scene::create();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);  

    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
	//layer->setPhyWorld(scene->getPhysicsWorld());

	auto hud = HelloWorldHud::create();

	_hud = hud;
	_hud->setGameLayer(layer);


	Sprite *spRocker = createWithAssets("direction.png");//摇杆 
	Sprite *spRockerBG = createWithAssets("dir_back.png");//摇杆背景 
	HRocker *rocker = HRocker::HRockerWithCenter(ccp(spRockerBG->getContentSize().width / 2, spRockerBG->getContentSize().height / 2), 50.0f, spRocker, spRockerBG, false);//创建摇杆 
	rocker->setGameLayer(layer);
	_movejoy = rocker;
	scene->addChild(rocker, 10);//摇杆添加到layer中 
	//this 是个layer 

	//Sprite *spRocker2 = createWithAssets("direction.png");//摇杆 
	//Sprite *spRockerBG2 = createWithAssets("dir_back.png");//摇杆背景 
	//HRocker* rocker2 = HRocker::HRockerWithCenter(ccp(210.0f, 130.0f), 50.0f, spRocker2, spRockerBG2, true);//创建摇杆 
	//rocker2->setGameLayer(layer);
	//scene->addChild(rocker2, 10);//摇杆添加到layer中 

 //   // add layer as a child to scene
    scene->addChild(layer);
	scene->addChild(hud);

	//Sprite *spRocker = Sprite::create("pad_ground.png");//摇杆
 //   Sprite *spRockerBG = Sprite::create("CloseSelected.png");//摇杆背景
 //   HRocker *rocker = HRocker::HRockerWithCenter(ccp(150.0f, 130.0f), 50.0f, spRocker, spRockerBG, false);//创建摇杆
 //   scene->addChild(rocker);

    // return the scene

	 
    return scene;
}

void HelloWorld::addBoxBodyForSprite(Sprite* sprite)
{
	/*auto body = PhysicsBody::createBox(sprite->getContentSize());
	body->setDynamic(false);
	sprite->setPhysicsBody(body);*/
}

HelloWorld::~HelloWorld()
{
	//_player->release();
}

void HelloWorld::onEnter()  
{  
    Layer::onEnter();  
    

	//auto listener = EventListenerTouchOneByOne::create();
	////lambda expression: advanced feature in C++ 11
	//listener->onTouchBegan = [&](Touch *touch, Event *unused_event)->bool { 
	//	_shootPoint = this->convertToNodeSpace(touch->getLocation()) - _player->getPosition();
	//	_player->setRotation(getCocosAngle(_shootPoint));
	//	_isShooting = true;
	//	return true; 
	//};
	//listener->onTouchMoved = [&](Touch *touch, Event *unused_event) {
	//	_shootPoint = this->convertToNodeSpace(touch->getLocation()) - _player->getPosition();
	//	_player->setRotation(getCocosAngle(_shootPoint));
	//};
	//listener->onTouchEnded = [&](Touch *touch, Event *unused_event) { 
	//	_isShooting = false;};
	//	//CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	//this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	/*auto listener_keyboard = EventListenerKeyboard::create();
	listener_keyboard->onKeyPressed = CC_CALLBACK_2(HelloWorld::onPressKey, this);
	listener_keyboard->onKeyReleased = CC_CALLBACK_2(HelloWorld::onPressReleased, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener_keyboard, this);*/


	/*auto Physi_listener = EventListenerPhysicsContact::create();
	Physi_listener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithFixedPriority(Physi_listener, 10);*/


    //Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener,10); //第二个参数是优先级，10是随意写的  
}  

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	this->_isShooting = false;
	this->_isReloading = false;
	this->_rederNpcIndex = 0;

	
	/*_hud->maxSprite(doc[1]["type"].GetInt());*/

	//SimpleAudioEngine::getInstance()->preloadEffect("reload.wav");
	//SimpleAudioEngine::getInstance()->playBackgroundMusic("battle_music.mp3", true);

	std::string file = "TileMap.tmx";
	auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
	_tileMap = TMXTiledMap::createWithXML(str->getCString(),"");

	/*TMXObjectGroup *objects = _tileMap->getObjectGroup("Objects");
	CCASSERT(NULL != objects, "'Objects' object group not found");
	auto spawnPoint = objects->getObject("SpawnPoint");
	CCASSERT(!spawnPoint.empty(), "SpawnPoint object not found");*/
	int x = _tileMap->getContentSize().width / 2;
	int y = _tileMap->getContentSize().height / 2;

	_player = new Character();
	_player->setPosition(Vec2(x, y));
	_player->setMoveRegion(_tileMap->getContentSize());
	this->addChild(_player);

	//_hud->numCollectedChanged(_player->getGun()->getGunName());

	setViewPointCenter(_player->getPosition());

	addChild(_tileMap, -3);

	_enemies = new NpcManager();
	_enemies->setTarget(_player);
	_enemies->setSceneSize(this->_tileMap->getContentSize());

	/*for (auto& eSpawnPoint : objects->getObjects()) {
		ValueMap& dict = eSpawnPoint.asValueMap();
		if (dict["Enemy"].asInt() == 1) {
			x = dict["x"].asInt();
			y = dict["y"].asInt();
			this->addEnemyAtPos(Point(x,y));
		}
	}*/

	_numCollected = 0;
    
	this->schedule(schedule_selector(HelloWorld::hitTest));
	//this->schedule(schedule_selector(HelloWorld::characterHitTest));
	this->schedule(schedule_selector(HelloWorld::addEnemy), 0.1f);
	this->schedule(schedule_selector(HelloWorld::npcMove), 1/60);
	//this->schedule(schedule_selector(HelloWorld::renderProjectile));
	this->scheduleUpdate();

	initjoystick();

    return true;
}

//void HelloWorld::renderProjectile(float dt)
//{
//	for (Sprite* sprite : _projectiles)
//	{
//		/*auto distance_vec = sprite->getPosition() - _player->getPosition();
//		if (abs(distance_vec.x) + abs(distance_vec.y) > 400)
//			sprite->setVisible(true);
//		else
//		{*/
//			sprite->setVisible(true);
//		//}
//	}
//}


void HelloWorld::npcMove(float dt)
{
	//@todo 把这个for拆开
		_enemies->rotate(1, _rederNpcIndex, dt * 60);
		_enemies->move(1, _rederNpcIndex,1);// dt * 60);
		_rederNpcIndex++;

	if (_rederNpcIndex >= 60)
		_rederNpcIndex = 0;

	//if (dt < 0.017)
	//this->_hud->numCollectedChanged(_enemies->getNpcs().size());
}


void HelloWorld::initjoystick()
{
	
}

void HelloWorld::addEnemy(float dt)
{/*
	if (_enemies->getNpcs().size() >= 1)
		return;*/

	Point pos;
	if (CCRANDOM_0_1() < 0.25)
		pos = Point(CCRANDOM_0_1() * _tileMap->getContentSize().width, 1);
	else if (CCRANDOM_0_1() < 0.5)
		pos = Point(CCRANDOM_0_1() * _tileMap->getContentSize().width, _tileMap->getContentSize().height - 1);
	else if (CCRANDOM_0_1() < 0.75)
		pos = Point(1, CCRANDOM_0_1() * _tileMap->getContentSize().height);
	else
		pos = Point(_tileMap->getContentSize().width - 1, CCRANDOM_0_1() * _tileMap->getContentSize().height);
		
	addEnemyAtPos(pos);

}

void HelloWorld::update(float dt)
{
	

	//this->_hud->maxSprite(_player->getGun()->getGunName());

	clock_t end = clock();

	if (_isReloading && (float)(end - _reloadTime) / 1000 > _player->getGun()->getReloadTime())
	{
		_isReloading = false;
		//this->_hud->numCollectedChanged("");
	}

	if (!_isReloading & _isShooting && (float)(end - _lastShootTime) / 1000 > _player->getGun()->getOneShopStep())
	{	
		shoot(_shootPoint);
		_lastShootTime = end;

		if (_player->getGun()->getLeftBullets() <= 0)
		{
			_reloadTime = clock();
			_isReloading = true;
			_player->getGun()->reload();
			//this->_hud->numCollectedChanged("RELOADING!!!");
			//SimpleAudioEngine::playEffect("reload.wav");
		}
	}

	#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) 
	auto new_pos = _player->getPosition();

	if(KEY_DOWN('W') ) new_pos.y += 2;
	if(KEY_DOWN('S') ) new_pos.y -= 2;
	if(KEY_DOWN('A') ) new_pos.x -= 2;
	if(KEY_DOWN('D') ) new_pos.x += 2;

	trySetPlayerPos(new_pos);

	//this->_hud->maxSprite(_enemies->getNpcs().size());
	#endif

	trySetPlayerPos(_player->getPosition() + _movejoy->getRockerAction() *2);

	
	_hud->numCollectedChanged(100000*(int)_movejoy->getRockerAction().x + (int)_movejoy->getRockerAction().y);
}

void HelloWorld::trySetPlayerPos(const Point& pos)
{
    
	Point new_pos = pos;
	if (pos.x < _player->getContentSize().width / 2) new_pos.x = _player->getContentSize().width / 2;
	if (pos.x > _tileMap->getContentSize().width - _player->getContentSize().width / 2)
		new_pos.x = _tileMap->getContentSize().width - _player->getContentSize().width / 2;

	if (pos.y < _player->getContentSize().height / 2) new_pos.y = _player->getContentSize().height;
	if (pos.y > _tileMap->getContentSize().height - _player->getContentSize().height)
		new_pos.y = _tileMap->getContentSize().height - _player->getContentSize().height;

	if (new_pos != _player->getPosition())
	{
		_player->walkTo(new_pos - _player->getPosition());
		this->setViewPointCenter(_player->getPosition());
	}
     
}

void HelloWorld::win()
{
	//GameOverScene *gameOverScene = GameOverScene::create();
	//gameOverScene->getLayer()->getLabel()->setString("You Win!");
	//Director::getInstance()->replaceScene(gameOverScene);
}

void HelloWorld::lose()
{
	//GameOverScene *gameOverScene = GameOverScene::create();
	//gameOverScene->getLayer()->getLabel()->setString("You Lose!");
	//Director::getInstance()->replaceScene(gameOverScene);
}

void HelloWorld::getFuncY(const Point& touch, const Point& player, Point& end, Point& bullet_left_end, float scatterAngle = 0)
{
	// Determine where we wish to shoot the projectile to
	float intersect_x = -1;
	float intersect_y = -1;

	// Are we shooting to the left or right?
	auto diff = touch;
	//this->_player->setRotation(diff);

	if (diff.x > 0)
		intersect_x = _tileMap->getContentSize().width;
	else if (diff.x < 0)
		intersect_x = 0;

	if (diff.y < 0)
		intersect_y = 0;
	else
		intersect_y = _tileMap->getContentSize().height;


	float realY;
	float realX;

	if (diff.x == 0)
	{
		// x = touch.y
		end.x = player.x;
		end.y = intersect_y;
	}
	else
	{
		float scatter_tan = 0;
		float k = diff.y / diff.x;
		if (scatterAngle != 0)
		{
			scatter_tan = bsin(scatterAngle) / bcos(scatterAngle);
			k = (diff.y / diff.x + scatter_tan) / (1 - scatter_tan * diff.y / diff.x);
		}

		if (intersect_x != -1)
		{
			realY = k * (intersect_x - player.x) + player.y;
			if (realY > 0 && realY < _tileMap->getContentSize().height)
			{
				end.x = intersect_x;
				end.y = realY;
			}
		}
		if (intersect_y != -1)
		{
			realX = 1 / k * (intersect_y - player.y) + player.x;
			if (realX > 0 && realX < _tileMap->getContentSize().width)
			{
				end.x = realX;
				end.y = intersect_y;
			}
		}
	}
}

void HelloWorld::shoot(const Point& touchDiffPos)
{
	// code to throw ninja stars will go here
	// Find where the touch is
	//auto touchLocation = touch->getLocation();
	
    
	auto pos = touchDiffPos;

	_player->shoot(touchDiffPos);
	// Create a projectile and put it at the player's location
	Gun* gun = _player->getGun();

	for (int multipleIter = 0; multipleIter < gun->getOneSpawnBullets(); multipleIter++)
	{
		Sprite* bullet = gun->createBullet();
		//gun->addToNode(this);
		this->addChild(bullet, -1);
		//bullet->setVisible(false);
		if (gun->getOffsetProbability() > 0)
		{
			float diffX = 0;
			float diffY = 0;
			float rnd = (CCRANDOM_0_1() * 2 - 1) / gun->getOffsetProbability();
			if (abs(rnd) <= 1)
			{
				diffX = rnd * gun->getOffsetDiameter();
				rnd = (CCRANDOM_0_1() * 2 - 1) / gun->getOffsetProbability();
				if (abs(rnd) <= 1)
					diffY = rnd * gun->getOffsetDiameter();
			}

			pos.x += diffX;
			pos.y += diffY;
		}

		// 初始点
		bullet->setPosition(_player->getPosition());

		Point realDest;
		Point bullet_leftDest;
		getFuncY(pos, _player->getPosition(), realDest, bullet_leftDest, CCRANDOM_0_1() * gun->getScatterAngle());
		auto end = realDest - _player->getPosition();

		float length = abs(end.x) + abs(end.y);
		if (gun->getMaxLength() != -1)
			length = gun->getMaxLength();
		float velocity = gun->getBulletSpd();
		float realMoveDuration = length / velocity;

		// Move projectile to actual endpoint
		auto actionMoveDone = CallFuncN::create(CC_CALLBACK_1(HelloWorld::projectileMoveFinished, this));
		auto moveTo = MoveTo::create(realMoveDuration, realDest);
		//@todo 转到45度角时，bulletline会被拉大1.414倍，需要做细微调整
		auto scaleTo = ScaleTo::create((float)gun->getBulletLineLength() / (float)gun->getBulletSpd() *2, gun->getBulletLineLength() / 10, 1);
		//bullet->stopAllActions();
		// 根据偏移调整后的角度
		bullet->setRotation(getCocosAngle(realDest - _player->getPosition()));
		bullet->runAction(Sequence::create(Spawn::createWithTwoActions(moveTo, scaleTo), actionMoveDone, NULL));


		_projectiles.pushBack(bullet);

		

		
		// 随机散射几发bullet
		Sprite* bullet_left = createWithAssets("bullet_left.png");
		this->addChild(bullet_left, -1);

		float bullet_left_angle = _player->getRotation() + (CCRANDOM_0_1()*120 - 60)/90;
		float bullet_move_dist = CCRANDOM_0_1() * 15 + 30;
		bullet_left->setRotation(bullet_left_angle);
		bullet_left->runAction(MoveBy::create(0.2, Vec2(bcos(bullet_left_angle), bsin(bullet_left_angle))*bullet_move_dist));
	}

	
}
void HelloWorld::characterHitTest(float dt)
{
    /*
	for (int i = 0; i < _buffs.size(); i ++)
	{
		Buff* buf = _buffs.at(i);
		if (abs(_player->getPosition().x - buf->getSprite()->getPosition().x) <= buf->getSprite()->getContentSize().width / 2 &&
			abs(_player->getPosition().y - buf->getSprite()->getPosition().y) <= buf->getSprite()->getContentSize().height / 2)
		{
			_buffs.eraseObject(buf);
			buf->getSprite()->removeFromParentAndCleanup(true);
			if (buf->getGun() != nullptr)
			{
				Gun* newGun = buf->getGun();
				_player->changeGun(newGun->getType());
				//this->_hud->maxSprite(_player->getGun()->getGunName());
			}
			delete buf;
			i++;
		}
	}
     */
}

void HelloWorld::hitTest(float dt)
{
	for (Sprite* bullet : _projectiles)
	{
		if (bullet != nullptr)
		{
			for (Npc* npc : _enemies->getNpcs())
			{
				float diffx = npc->getPosition().x - bullet->getPosition().x;
				float diffy = npc->getPosition().y - bullet->getPosition().y;
				float targetRadius = npc->getSize().width / 2 + _player->getGun()->getBulletDmgWidth();
				if (diffx * diffx + diffy * diffy < targetRadius * targetRadius)
				{
					// -1：continue
					// 1 : return
					// 0 : 不变
					int ret_flag = 0;

					npc->beAttack(_player, this);

					if (npc->getHP() > 0)
						ret_flag = -1;
					else
					{
						auto buff = _enemies->removeNpc(npc);
						if (buff != nullptr)
						{
							this->addChild(buff->getSprite(),-1);
							this->_buffs.pushBack(buff);
							buff->getSprite()->setPosition(bullet->getPosition());
							buff->getSprite()->runAction(
								Sequence::createWithTwoActions(
									FadeOut::create(10),
									CallFuncN::create(CC_CALLBACK_1(HelloWorld::buffFadeOut, this, buff))
								 )
							);
						}
					}
					if (_player->getGun()->getIsPenetrate() == false)
					{
						bullet->removeFromParentAndCleanup(true);
						_projectiles.eraseObject(bullet);
						ret_flag = 1;
					}

					if (ret_flag == 1)
						return;
					else if (ret_flag == -1)
						continue;
				}
			}
		}
	}
}

void HelloWorld::buffFadeOut(Ref* pSender, Buff* buf)
{
	Sprite *sprite = (Sprite *)pSender;
	this->removeChild(sprite);
	this->_buffs.eraseObject(buf);
}

void HelloWorld::projectileMoveFinished(Ref *pSender)
{
	Sprite *sprite = (Sprite *)pSender;
	_projectiles.eraseObject(sprite);
	this->removeChild(sprite);
}

void HelloWorld::setViewPointCenter(const Point& position) {
	auto winSize = Director::getInstance()->getWinSize();

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
	auto actualPosition = Point(x, y);

	auto centerOfView = Point(winSize.width / 2, winSize.height / 2);
	auto viewPoint = centerOfView - actualPosition;
	this->setPosition(viewPoint);
}

void HelloWorld::addEnemyAtPos(const Point& pos)
{
	
	Npc* newNpc = _enemies->createNpc(pos, 1);
	this->addChild(newNpc);
	//newNpc->rotateSchedule();
	//newNpc->moveSchedule();
	//this->animateEnemy(enemy);
}


void HelloWorldHud::projectileButtonTapped(Ref *pSender)
{
	/*if (_gameLayer->getMode() == 1) {
		_gameLayer->setMode(0);
	}
	else {
		_gameLayer->setMode(1);
	}*/
}

bool HelloWorldHud::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	label = Label::createWithTTF("0", "fonts//Marker Felt.ttf", 40, Size(50, 20), TextHAlignment::RIGHT);
	label->setColor(Color3B(0, 0, 0));
	anothor_label = Label::createWithTTF("0", "fonts//Marker Felt.ttf", 40, Size(50, 20), TextHAlignment::RIGHT);
	anothor_label->setColor(Color3B(0, 0, 0));
	int margin = 10;
	label->setPosition(visibleSize.width - (label->getDimensions().width / 2) - margin,
		visibleSize.height / 2);
	anothor_label->setPosition(visibleSize.width - (label->getDimensions().width / 2) - margin,
		label->getDimensions().height / 2 + margin + 20);
	this->addChild(label);
	this->addChild(anothor_label);

	return true;
}

void HelloWorldHud::numCollectedChanged(float numCollected)
{
	/*if (numCollected > _maxNum)
		_maxNum = numCollected;*/
	char showStr[20];
	sprintf(showStr, "%f", numCollected);
	label->setString(showStr);
}

void HelloWorldHud::maxSprite(const string& gunName)
{
	/*if (numCollected > _maxNum)
		_maxSprite = numCollected;*/

	char showStr[20];
	//sprintf(showStr, "", numCollected);
	anothor_label->setString(gunName.c_str());
}