#pragma once
#include <cocos2d.h>
#include <Npc.h>
using namespace cocos2d;
using namespace std;


class Gun;
class Character : public Npc
{
public:
	Character();
	//摇杆传进来的x,y
	void walkTo(const Vec2& pos, float velocity = 1, float intensity = 1) { walkTo(pos.x, pos.y, velocity, intensity); }
	//摇杆传进来的x,y
	void walkTo(int x, int y, float velocity = 1, float intensity = 1);
	//void setPosition(const Vec2& pos);
	void addToNode(Layer* layer);

	CC_SYNTHESIZE(Gun* , _gun, Gun);

	void setRotation(float angle);
	//float getRotation() {return this->_npc_sprite->getRotation();}
	void changeGun(int gunType);
	void shoot(const Vec2&);
	//static int getRotation(const Vec2& pos);
private:
	~Character();
	void initGun();
	Sprite* _dirSprite;
	int _currFrame;
	Vector<SpriteFrame*> _splitAniFrame;
	SpriteFrame* _shootframe;
	//Vector<SpriteFrame*> _gunFireFrame;
};

