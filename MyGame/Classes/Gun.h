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

	// 剩余子弹数
	CC_SYNTHESIZE(int, _leftBullets, LeftBullets);
	CC_SYNTHESIZE(string, _gunName, GunName);
	// 枪类型
	CC_SYNTHESIZE(int, _type, Type);

	// 子弹飞行速度
	// 单位：像素
	CC_SYNTHESIZE(int, _bulletSpd, BulletSpd);
	// 散射角度
	// 单位：弧度
	CC_SYNTHESIZE(float, _scatterAngle, ScatterAngle);
	// 并发子弹数
	CC_SYNTHESIZE(int, _oneSpawnBullets, OneSpawnBullets);
	// 单发子弹威力
	CC_SYNTHESIZE(int, _power, Power);
	// 换弹时间
	// 单位：秒
	CC_SYNTHESIZE(float, _reloadTime, ReloadTime);
	//// 点击一次几发子弹
	//CC_SYNTHESIZE(int, _oneClickBllets, OneClickBullets);
	// 子弹动画尺寸
	CC_SYNTHESIZE(int, _bulletLineLength, BulletLineLength);/*
	CC_SYNTHESIZE(int, _bulletLineWidth, BulletLineWidth);*/
	// 弹夹数量
	CC_SYNTHESIZE(int, _bulletClip, BulletClip);
	// 单发间隔
	CC_SYNTHESIZE(float, _oneShotStep, OneShopStep);
	// 子弹伤害范围
	// 单位：像素
	CC_SYNTHESIZE(int, _bulletDmgWidth, BulletDmgWidth);
	// 是否是穿透弹
	CC_SYNTHESIZE(bool, _isPenetrate, IsPenetrate);
	// 子弹最远飞行距离
	// 单位：像素
	CC_SYNTHESIZE(int, _maxLength, MaxLength);
	// 子弹射偏半径
	// 单位：像素
	CC_SYNTHESIZE(float, _offsetDiameter, OffsetDiameter);
	// 子弹射偏概率
	CC_SYNTHESIZE(float, _offsetProbability, OffsetProbability);
	// 后座力
	// 单位：像素
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
	// func 击中效果
	// func 携带时的特殊效果
protected:
	string _weaponCode;
	string _bulletCode;

	Sprite* _bulletSprite;
	Sprite* _weaponSprite;
	ParticleSystemQuad* _bulletPartile;
};

