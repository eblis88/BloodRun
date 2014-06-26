#pragma once
#include <cocos2d.h>
#include <math.h>

using namespace std;
using namespace cocos2d;

class Buff;
class NpcManager;
class Character;

class Npc : public Node
{
public:
	Npc();
	~Npc() {};
	Npc(Sprite* sprite);

	CC_SYNTHESIZE(int, _hp, HP);
	CC_SYNTHESIZE(float, _rotateSpd, RotateSpd);
	CC_SYNTHESIZE(float, _moveSpd, MoveSpd);

	CC_SYNTHESIZE(float, _moveStep, MoveStep);
	CC_SYNTHESIZE(float, _rotateStep, RotateStep);
	CC_SYNTHESIZE(float, _attackStep, AttackStep);
	CC_SYNTHESIZE(int, _rotateAngle, RotateAngle);

	const Size& getSize() { if (_npc_sprite != nullptr) return _npc_sprite->getContentSize(); else return Size(); }
	virtual Sprite* getSprite() { return _npc_sprite; }
	const Size& getMoveRegion() { return _moveRegion; }
	void setMoveRegion(const Size& size) { _moveRegion = size; }

	virtual void move(float durationMod = 1);
	virtual void rotate(float angle, float durationMod = 1);
	virtual void attack(const Vec2& pos);
	virtual void died();
	virtual void beAttack(Character* , Layer*);

	const string& int2str(const int &int_temp);

	//const Vec2& getPosition() { return _npc_sprite->getPosition(); }
	//virtual void setPosition(const Vec2& pos) { _npc_sprite->setPosition(pos); }
	MoveTo* getMoveAction(float durationMod = 1);
	RotateTo* rotateWithAction(float angle, float durationMod = 1, bool execute = true);
	int _faceAngle;

	void npc_init();
	Sprite* _npc_sprite;
	Animation* _animation;

	float getFaceToPlayerAngle() { return _faceToPlayerAngle; }

	Buff* dropBuff(int killedNpcs);
	NpcManager* owner;

	// test method
	void rotateSchedule();
	void moveSchedule();

	int getBoundingRadius() {
		return min(_npc_sprite->getContentSize().width, _npc_sprite->getContentSize().height);
	}
private:
	virtual int p_rotate(int cocosAngle);
	Size _moveRegion;
	float _faceToPlayerAngle;

protected:
	Buff* dropBuff();
	Buff* dropGun();
};
