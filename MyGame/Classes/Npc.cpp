#include "Npc.h"
#include "NpcManager.h"
#include <Buff.h>
#include <bmath.h>
#include <Character.h>
#include <sstream>

Npc::Npc() 
{
	npc_init();
}

Buff* Npc::dropBuff(int killedNpcs)
{
	if (killedNpcs == 1 || CCRANDOM_0_1() < 0.005)
		return dropGun();
	else
	{
		//@todo 伪随机
		//		每个Npc有个掉落列表
		if (CCRANDOM_0_1() < 0.03)
		{
			return dropBuff();
		}
		return nullptr;
	}
	
}

Buff* Npc::dropBuff()
{
	Buff* buff = Buff::createRandomBuff();
	return buff;
}

Buff* Npc::dropGun()
{
	Buff* gun_buff = Buff::createRandomGun();
	return gun_buff;
}

void Npc::npc_init()
{
	_faceAngle = -1;
	_hp = 2;
	_rotateSpd = 1;
	_rotateStep = 1;
	_moveSpd = 20;
	_moveStep = 1;
	_rotateAngle = 20;
}

Npc::Npc(Sprite* tex): _npc_sprite(nullptr)
{
	_npc_sprite = tex;
	_npc_sprite->retain();
	npc_init();
	this->addChild(_npc_sprite);
}

void Npc::beAttack(Character* player, Layer* layer)
{
	string filename = "blood/";
	float distance = _npc_sprite->getPosition().distanceSquared(player->getPosition());
	float power = player->getGun()->getPower();

	if (distance < 1) distance = 1;
	float blood = power / distance;

	int bloodCount = 0;
	if (blood >= 0.01) filename += "3";
	else if (blood < 0.1 && blood >= 0.004) filename += "2";
	else if (blood < 0.004) filename += "1";
	//filename += bloodCount;

	int spdCount = 0;
	if (player->getGun()->getBulletSpd() > 1500)
		filename += "/3/";
	else if (player->getGun()->getBulletSpd() >= 1000)
		filename += "/2/";
	else
		filename += "/1/";

	//filename += "/" + spdCount;

	for(int i = 0; i < 3 + CCRANDOM_0_1()*2; i ++)
	{
		int rndFileName = 5;//(int)(CCRANDOM_0_1() * 12) + 1;
		CCString *ns = CCString::createWithFormat("%d", rndFileName);
		string rndfile = filename +ns->_string + ".png";
		Sprite* blood = Sprite::create(rndfile);
		
		float angle = CCRANDOM_0_1() * 365;
		blood->setRotation(angle);
		Vec2 diff = Vec2(bcos(-angle) * CCRANDOM_0_1() * _npc_sprite->getContentSize().width,
			bsin(-angle) * CCRANDOM_0_1() * _npc_sprite->getContentSize().height);
		blood->setPosition(_npc_sprite->getPosition() + diff);
		layer->addChild(blood, -2);
		blood->runAction(
			Sequence::create(
				FadeOut::create(30),
				CallFuncN::create([&](Ref* sender){
					((Sprite*)sender)->removeFromParentAndCleanup(true);}
				),
				NULL
			)
		);
	}


	_hp -= power;
}

const string& Npc::int2str(const int &int_temp)  
{  
        stringstream stream;  
        stream<<int_temp;  
        return stream.str();   //此处也可以用 stream>>string_temp  
}  

void Npc::move(float durationMod)
{
	

	//_npc_sprite->setPosition(getPosition());
	_npc_sprite->runAction(getMoveAction(durationMod));
	/*_npcSprite->runAction(Sequence::create(
		mov,
		CallFuncN::create(CC_CALLBACK_0(Npc::moveFinished, this)),NULL));*/
}

MoveTo* Npc::getMoveAction(float durationMod)
{
	// Create the actions
	auto position = getPosition();
	position.x += bcos(_faceAngle*3.14159 / 180) * _moveSpd * durationMod;
	position.y += bsin(_faceAngle*3.14159 / 180) * _moveSpd * durationMod;

	if (position.x < 0) position.x = 0;
	if (position.y < 0) position.y = 0;

	if (position.x > _moveRegion.width) position.x = _moveRegion.width;
	if (position.y > _moveRegion.height) position.y = _moveRegion.height;

	auto mov = MoveTo::create(_moveStep * durationMod,  position);

	return mov;
}

void Npc::rotateSchedule()
{
	/*_faceToPlayerAngle = owner->angleWithPlayer(this);
	auto action = rotateWithAction(_faceToPlayerAngle);
	_npc_sprite->runAction(Sequence::create(
		action,
		CallFuncN::create([&](Node* sender) {
		rotateSchedule(); }
	), NULL));*/
}
void Npc::moveSchedule()
{
	/*auto action = getMoveAction();
	_npc_sprite->runAction(Sequence::create(
		action,
		CallFuncN::create([&](Node* sender) {
		moveSchedule(); }
		), NULL));*/
}

void Npc::rotate(float cocosAngle, float durationMod)
{
	//_npcSprite->setRotation(angle);

	_faceToPlayerAngle = cocosAngle;
	_npc_sprite->runAction(rotateWithAction(cocosAngle));
	/*_npcSprite->runAction(Sequence::create(
		action,
		CallFuncN::create(CC_CALLBACK_0(Npc::roteateFinished, this)), NULL));*/
}

RotateTo* Npc::rotateWithAction(float cocosAngle, float durationMod, bool execute)
{
	int old_angle = _faceAngle;
	int angle = p_rotate(cocosAngle);
	if(abs(old_angle - abs(angle)) > 90)
	{
		int a = 0;
	}

	if (_faceAngle >= 360) _faceAngle -= 360;
	if (_faceAngle < 0) _faceAngle += 360;

	if (execute)
	{
		auto action = RotateTo::create(getRotateSpd(), angle);
		return action;
	}
	else
		return nullptr;
}


int Npc::p_rotate(int cocosAngle)
{
	int old_angle = _faceAngle;

	if (_faceAngle == -1 || abs(_faceAngle - cocosAngle) < _rotateAngle)
		_faceAngle = cocosAngle;
	else
	{
		if ((_faceAngle - cocosAngle <= 180 && _faceAngle - cocosAngle > 0) ||
			(_faceAngle + 360 - cocosAngle <= 180 && _faceAngle + 360 - cocosAngle > 0))
		{
			_faceAngle -= _rotateAngle;
		}
		else
		{
			_faceAngle += _rotateAngle;
		}
	}

	if (_faceAngle < -180)
		return 360 - _faceAngle;
	else
		return -_faceAngle;

	//_npcSprite->setRotation(-_angleFace2Player);
}



void Npc::attack(const Vec2& pos)
{}

void Npc::died()
{}


