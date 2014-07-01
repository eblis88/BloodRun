#pragma once
#include <cocos2d.h>
#include <string>

using namespace cocos2d;
using namespace std;

class Gun
{
public:
	Gun(int type);
	~Gun();

	//bool UTF8ToGB(string &szOut ,string str);

	//  £”‡◊”µØ ˝
	CC_SYNTHESIZE(int, _leftBullets, LeftBullets);
	CC_SYNTHESIZE(string, _gunName, GunName);
	// «π¿‡–Õ
	CC_SYNTHESIZE(int, _type, Type);

	// ◊”µØ∑…––ÀŸ∂»
	// µ•Œª£∫œÒÀÿ
	CC_SYNTHESIZE(int, _bulletSpd, BulletSpd);
	// …¢…‰Ω«∂»
	// µ•Œª£∫ª°∂»
	CC_SYNTHESIZE(float, _scatterAngle, ScatterAngle);
	// ≤¢∑¢◊”µØ ˝
	CC_SYNTHESIZE(int, _oneSpawnBullets, OneSpawnBullets);
	// µ•∑¢◊”µØÕ˛¡¶
	CC_SYNTHESIZE(int, _power, Power);
	// ªªµØ ±º‰
	// µ•Œª£∫√Î
	CC_SYNTHESIZE(float, _reloadTime, ReloadTime);
	//// µ„ª˜“ª¥Œº∏∑¢◊”µØ
	//CC_SYNTHESIZE(int, _oneClickBllets, OneClickBullets);
	// ◊”µØ∂Øª≠≥ﬂ¥Á
	CC_SYNTHESIZE(int, _bulletLineLength, BulletLineLength);/*
	CC_SYNTHESIZE(int, _bulletLineWidth, BulletLineWidth);*/
	// µØº– ˝¡ø
	CC_SYNTHESIZE(int, _bulletClip, BulletClip);
	// µ•∑¢º‰∏Ù
	CC_SYNTHESIZE(float, _oneShotStep, OneShopStep);
	// ◊”µØ…À∫¶∑∂Œß
	// µ•Œª£∫œÒÀÿ
	CC_SYNTHESIZE(int, _bulletDmgWidth, BulletDmgWidth);
	//  «∑Ò «¥©Õ∏µØ
	CC_SYNTHESIZE(bool, _isPenetrate, IsPenetrate);
	// ◊”µØ◊Ó‘∂∑…––æ‡¿Î
	// µ•Œª£∫œÒÀÿ
	CC_SYNTHESIZE(int, _maxLength, MaxLength);
	// ◊”µØ…‰∆´∞Îæ∂
	// µ•Œª£∫œÒÀÿ
	CC_SYNTHESIZE(float, _offsetDiameter, OffsetDiameter);
	// ◊”µØ…‰∆´∏≈¬ 
	CC_SYNTHESIZE(float, _offsetProbability, OffsetProbability);
	// ∫Û◊˘¡¶
	// µ•Œª£∫œÒÀÿ
	CC_SYNTHESIZE(float, _recoilDiff, RecoilDiff);

	Sprite* getBullet() {return _bulletSprite;}
	Sprite* getGun() {return _weaponSprite;}

	void addToNode(Layer*);
	void setPosition(const Point&);
	Sprite* createBullet();

	void reload();

	void runAction(Action* act);
	void setRotation(float rot) {
		_bulletSprite->setRotation(rot);}
		//_bulletPartile->setAngle(-180 - rot);}
	// func ª˜÷––ßπ˚
	// func –Ø¥¯ ±µƒÃÿ ‚–ßπ˚
protected:
	string _weaponCode;
	string _bulletCode;

	Sprite* _bulletSprite;
	Sprite* _weaponSprite;
	//ParticleSystemQuad* _bulletPartile;
};

