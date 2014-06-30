#include "Buff.h"
#include "Gun.h"
#include "DataModelBase.h"

Buff::~Buff()
{
	delete _thisGun;
	_thisGun = nullptr;
}

Buff* Buff::createRandomGun()
{
	//@todo 改成数据表gun list

	Buff* buff = new Buff();
	Gun* gun = new Gun((int)(CCRANDOM_0_1() * 37));
	gun->getGun()->retain();
	buff->setGun(gun);
	return buff;
}

Buff* Buff::createRandomBuff()
{
	string buffs[3] = {"Buff/bon_nuke.jpg", "Buff/bon_shield.jpg", "Buff/bon_speed3.jpg"};

	Buff* buff = new Buff();
	buff->setGun(nullptr);
	buff->setSprite(createWithAssets(buffs[(int)CCRANDOM_0_1()*2]));
	return buff;
}
