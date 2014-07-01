#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <time.h>
#include <string.h>
//#include <json/document.h>
#include <Buff.h>

using namespace cocos2d;
using namespace std;

class HelloWorld;
class Character;
class NpcManager;

class HelloWorldHud : public Layer
{
public:
	void numCollectedChanged(float numCollected);
	void maxSprite(const string& numCollected);
	virtual bool init();
	CREATE_FUNC(HelloWorldHud);

	Label *label;
	Label *anothor_label;
	void projectileButtonTapped(Ref *pSender);
	CC_SYNTHESIZE(HelloWorld *, _gameLayer, GameLayer);
	int _maxNum;
	int _maxSprite;
};

class HelloWorld : public Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static Scene* createScene();
	~HelloWorld();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
	void shoot(const Point& pos);
	/*void onPressKey(EventKeyboard::KeyCode key, Event* even);
	void onPressReleased(EventKeyboard::KeyCode key, Event* even);*/
	
	void enemyMoveFinished(Ref *pSender);
	void projectileMoveFinished(Ref *pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void trySetPlayerPos(const Point& pos);
	void update(float dt);
	void animateEnemy(Sprite *enemy);
	//void testCollisions(float dt);
	void win();
	void lose();

	void addBoxBodyForSprite(Sprite* sprite);
	//CC_SYNTHESIZE(int, _mode, Mode);

	
	//rapidjson::Document doc;
private:
	TMXTiledMap *_tileMap;// = nullptr;
	Character *_player;// = nullptr;

	//TMXLayer *_meta;// = nullptr;
	int _numCollected;
	static HelloWorldHud *_hud;
	NpcManager* _enemies;// = nullptr;
	Vector<Sprite *> _projectiles;
	Vector<Buff* > _buffs;
	int _rederNpcIndex;

private:
	void setViewPointCenter(const Point& position);
	void addEnemy(float dt);
	void addEnemyAtPos(const Point& pos);
	void npcMove(float dt);
	void onEnter();
	bool onContactBegin(PhysicsContact& contact);
	void initjoystick();
	void buffFadeOut(Ref* pSender, Buff* buf);
	//void renderProjectile(float dt);

	void hitTest(float dt);
	void characterHitTest(float dt);
	void getFuncY(const Point&,const Point&, Point&, Point&, float);

	bool _isShooting;
	Point _shootPoint;
	clock_t _lastShootTime;
	clock_t _reloadTime;
	bool _isReloading;

	//HelloWorld() : _shootPoint(Point()) {};
};


#endif // __HELLOWORLD_SCENE_H__
