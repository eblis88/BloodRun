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

	// ʣ���ӵ���
	CC_SYNTHESIZE(int, _leftBullets, LeftBullets);
	CC_SYNTHESIZE(string, _gunName, GunName);
	// ǹ����
	CC_SYNTHESIZE(int, _type, Type);

	// �ӵ������ٶ�
	// ��λ������
	CC_SYNTHESIZE(int, _bulletSpd, BulletSpd);
	// ɢ��Ƕ�
	// ��λ������
	CC_SYNTHESIZE(float, _scatterAngle, ScatterAngle);
	// �����ӵ���
	CC_SYNTHESIZE(int, _oneSpawnBullets, OneSpawnBullets);
	// �����ӵ�����
	CC_SYNTHESIZE(int, _power, Power);
	// ����ʱ��
	// ��λ����
	CC_SYNTHESIZE(float, _reloadTime, ReloadTime);
	//// ���һ�μ����ӵ�
	//CC_SYNTHESIZE(int, _oneClickBllets, OneClickBullets);
	// �ӵ������ߴ�
	CC_SYNTHESIZE(int, _bulletLineLength, BulletLineLength);/*
	CC_SYNTHESIZE(int, _bulletLineWidth, BulletLineWidth);*/
	// ��������
	CC_SYNTHESIZE(int, _bulletClip, BulletClip);
	// �������
	CC_SYNTHESIZE(float, _oneShotStep, OneShopStep);
	// �ӵ��˺���Χ
	// ��λ������
	CC_SYNTHESIZE(int, _bulletDmgWidth, BulletDmgWidth);
	// �Ƿ��Ǵ�͸��
	CC_SYNTHESIZE(bool, _isPenetrate, IsPenetrate);
	// �ӵ���Զ���о���
	// ��λ������
	CC_SYNTHESIZE(int, _maxLength, MaxLength);
	// �ӵ���ƫ�뾶
	// ��λ������
	CC_SYNTHESIZE(float, _offsetDiameter, OffsetDiameter);
	// �ӵ���ƫ����
	CC_SYNTHESIZE(float, _offsetProbability, OffsetProbability);
	// ������
	// ��λ������
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
	// func ����Ч��
	// func Я��ʱ������Ч��
protected:
	string _weaponCode;
	string _bulletCode;

	Sprite* _bulletSprite;
	Sprite* _weaponSprite;
	ParticleSystemQuad* _bulletPartile;
};

