#pragma once
#include <cocos2d.h>
#include <Gun.h>
using namespace cocos2d;
using namespace std;

class Buff : public Node
{
protected:
	
	Sprite* _sprite;
	Gun* _thisGun;
public:
	~Buff();

	Gun* getGun() {return _thisGun;}
	void setGun(Gun* gun) {_thisGun = gun;}
	static Buff* createRandomGun();
	static Buff* createRandomBuff();
	Sprite* getSprite() {
		if (_thisGun != nullptr)
			return _thisGun->getGun();
		else
			return _sprite;}
	void setSprite(Sprite* sprite) {_sprite = sprite;}
};

