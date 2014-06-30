#include "Gun.h"
#include "DataDictionary.h"
#include "DataModelBase.h"

/// 高速子弹： 速度> 1500
/// 中速子弹： 1500>速度>= 1000
/// 低速子弹： 速度< 1000


Gun::Gun(int type)
{
	auto doc = DataDictionary::Instance()->getDoc("gun.txt");  
	rapidjson::Value &v =(*doc)[type];
	_bulletSprite = nullptr;
	_gunName = "手枪";
	_gunName = v["name"].GetString();//ReadString::getInstance()->read(type, "name");
	_type = v["type"].GetInt();
	_bulletSpd = v["BulletSpd"].GetInt();
	_bulletCode  = v["BulletCode"].GetString() + string(".png");
	_weaponCode = v["GunCode"].GetString() + string(".png");
	_weaponSprite = createWithAssets( _weaponCode); 

	_oneShotStep = v["OneShotStep"].GetDouble();
	_bulletLineLength = v["BulletLineLength"].GetInt();
	int pentmp = v["IsPenetrate"].GetInt();
	if (pentmp == 0)
		_isPenetrate = false;
	else
		_isPenetrate = true;
	_bulletDmgWidth = v["BulletDmgWidth"].GetInt();
	_maxLength = v["MaxLength"].GetInt();
	_offsetDiameter =  v["OffsetDiameter"].GetInt();
	_offsetProbability =  v["OffsetProbability"].GetDouble();
	_scatterAngle = v["ScatterAngle"].GetDouble();
	_oneSpawnBullets = v["OneSpawnBullets"].GetInt();
	_bulletClip = v["BulletClip"].GetInt();
	_reloadTime = v["ReloadTime"].GetDouble();
	_power = v["Powner"].GetInt();
	_recoilDiff = v["Recoil"].GetInt();

	_leftBullets = _bulletClip;
}

//bool Gun::UTF8ToGB(string &szOut ,string str)
//{
//	WCHAR *strSrc;
//	TCHAR *szRes;
//	int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
//	strSrc = new WCHAR[i+1];
//	MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);
//	i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
//	szRes = new TCHAR[i+1];
//	WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);
//	szOut = szRes;
//	delete []strSrc;
//	delete []szRes;
//	return true;
//}

void Gun::reload()
{
	_leftBullets = _bulletClip;
}

Sprite* Gun::createBullet()
{ 
	Sprite* bullet = createWithAssets(_bulletCode); 
	bullet->setAnchorPoint(Vec2(1,0.5));
	bullet->setScaleX(0.1);

	//_bulletPartile = ParticleSystemQuad::create("bullet.plist");   
	//_bulletPartile->setSpeed(_bulletSpd);
	//_bulletPartile->setScaleX(2);
	//mSystem->setTextureWithRect(CCTextureCache::sharedTextureCache()->addImage("bullet.png")  
	//	  ,CCRectMake(0,0,32,32));//加载图片，第一个参数是纹理，第二个参数是选择图片上的位置  
	//mSystem->setBlendAdditive(true);//这个调用必不可少  
	////mSystem->setPosition(ccp(400,670));//设置位置  
	////addChild(mSystem);  

	return bullet;
}

void Gun::addToNode(Layer* layer)
{
	layer->addChild(_bulletSprite, -2);
	//layer->addChild(_bulletPartile);
}

void Gun::runAction(Action* act)
{
	_bulletSprite->runAction(act);
	//_bulletPartile->runAction(act->clone());
}

void Gun::setPosition(const Point& pos)
{
	_bulletSprite->setPosition(pos);
	//_bulletPartile->setPosition(pos);
}

Gun::~Gun()
{
}
