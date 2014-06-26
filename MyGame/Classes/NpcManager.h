#pragma once
#include <cocos2d.h>
using namespace cocos2d;
using namespace std;
//@todo singleton!

class Character;
class Buff;
class Npc;

class NpcManager : public Node
{
public:
	NpcManager();

	virtual Npc* createNpc(const Point& pos, int type);
	virtual void move(int time, int renderIndex, float durationMod);
	virtual void rotate(int time, int renderIndex, float durationMod);
	virtual void attack(int time, int renderIndex);


	Character* _target;
	Character* getTarget() {return _target;}
	void setTarget(Character* target){_target = target;}
	void setSceneSize(const Size& size){ _sceneSize = size; }
	Vector<Npc*> getNpcs(){ return _npcs; }
	//记得删Vector
	Vector<Npc*> getNpcsVectorClone(const Vec2& vec);
	//记得删Vector
	Vector<Npc*> getNpcsVectorClone(float minAngle, float maxAngle);
	Buff* removeNpc(Npc* npc);
private:
	Vector<Npc*> _npcs;
	Size _sceneSize;
	int _killedNpcs;

protected:
	~NpcManager();

public:
	float angleWithPlayer(Npc* npc);
};