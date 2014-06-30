#include "NpcManager.h"
#include <Character.h>
#include "DataModelBase.h"
#include <Npc.h>
#include <bmath.h>

Npc* NpcManager::createNpc(const Point& pos, int type)
{
	//@todo 根据type找到对应的enemy
	string npcCode = "enemy1.png";
	
	auto sprite = createWithAssets(npcCode);
	Npc* newNpc = new Npc(sprite);
	newNpc->setPosition(pos);
	newNpc->setMoveRegion(_sceneSize);
	_npcs.pushBack(newNpc);
	newNpc->owner = this;

	return newNpc;
	/*int cocosAngle = AngleWithPlayer();

	_npcSprite->setRotation(cocosAngle);
	_angleFace2Player = cocosAngle;*/
}

void NpcManager::rotate(int time, int renderIndex, float durationMod)
{
	Vector<Npc*>::iterator iter = _npcs.end();
	if (_npcs.size() >= renderIndex)
	{
		for (iter = _npcs.begin() + renderIndex;;)
		{
			if (iter != _npcs.end())
			{
				if ((*iter)->getRotateStep() == time)
					(*iter)->rotate(angleWithPlayer(*iter), durationMod);
				if (_npcs.getIndex(*iter) + 60 < _npcs.size()) iter += 60;
				else return;
			}
			else
				return;
		}
	}
}

Buff* NpcManager::removeNpc(Npc* npc)
{
	_killedNpcs++;
	auto buff = npc->dropBuff(_killedNpcs);
	npc->stopAllActions();
	npc->removeFromParentAndCleanup(true);
	_npcs.eraseObject(npc);
	//delete npc;
	return buff;
}

void NpcManager::move(int time, int renderIndex, float durationMod)
{
	Vector<Npc*>::iterator iter = _npcs.end();
	if (_npcs.size() > renderIndex)
	{
		for (iter = _npcs.begin() + renderIndex;;)
		{
			if (iter != _npcs.end())
			{
				if ((*iter)->getRotateStep() == time)
				{
					//(*iter)->getSprite()->stopAllActions();
					(*iter)->rotate(angleWithPlayer(*iter), durationMod);
					(*iter)->move(durationMod);
				}
				if (_npcs.getIndex(*iter) + 60 < _npcs.size()) iter += 60;
				else return;
			}
			else
				return;
		}
	}
}

void NpcManager::attack(int time, int index)
{
	for (auto npc : _npcs)
	{
		if (npc->getAttackStep() == time)
			npc->attack(_target->getPosition());
	}
}

NpcManager::NpcManager() : _target(nullptr) , _killedNpcs(0)
{
}

NpcManager::~NpcManager()
{
	if (_npcs.size() > 0)
	{
		for (Npc* npc : _npcs)
		{
			npc->release();
		}
		_npcs.clear();
	}
}

Vector<Npc*> NpcManager::getNpcsVectorClone(const Vec2& vec)
{
	float angleRadians = batan2((float)vec.y , (float)vec.x);
	float angleDegrees = CC_RADIANS_TO_DEGREES(angleRadians);
	float cocosAngle = angleDegrees;
	/*if (vec.x < 0){
		cocosAngle = 180 + cocosAngle;
	}*/
	if (cocosAngle >= 360) cocosAngle -= 360;
	if (cocosAngle < 0) cocosAngle += 360;

	Vector<Npc*> tmp;
	for (Npc* npc : _npcs)
	{
		if (abs(npc->getFaceToPlayerAngle() - cocosAngle) < 5)
		{
			tmp.pushBack(npc);
		}
	}
	return tmp;
}

Vector<Npc*> NpcManager::getNpcsVectorClone(float minAngle, float maxAngle)
{
	Vector<Npc*> tmp;
	for (Npc* npc : _npcs)
	{
		if (npc->getFaceToPlayerAngle() > maxAngle + 5 && 
			npc->getFaceToPlayerAngle() < minAngle - 5)
		{
			tmp.pushBack(npc);
		}
	}
	return tmp;
}

float NpcManager::angleWithPlayer(Npc* npc)
{
	auto diff = _target->getPosition() - npc->getPosition();
	float angleRadians = batan2((float)diff.y , (float)diff.x);
	float angleDegrees = CC_RADIANS_TO_DEGREES(angleRadians);
	float cocosAngle = angleDegrees;
	/*if (diff.x < 0){
		cocosAngle = 180 + cocosAngle;
	}*/

	if (cocosAngle > 360) cocosAngle -= 360;
	if (cocosAngle < 0) cocosAngle += 360;

	return cocosAngle;
}