#include <DataModelBase.h>

float getCocosAngle(const Vec2& vect)
{
	float angleRadians = batan2((float)vect.y, (float)vect.x);
	float angleDegrees = CC_RADIANS_TO_DEGREES(angleRadians);
	float cocosAngle = angleDegrees;
	/*if (pos.x < 0){
	cocosAngle = 180 + cocosAngle;
	}*/
	if (cocosAngle >= 360) cocosAngle -= 360;
	if (cocosAngle < 0) cocosAngle += 360;

	return -cocosAngle;
}

Sprite* createWithAssets(string filename)
{
	Sprite* ret = Sprite::create();

    //@todo:
    // 使用更高效的读取方式，现在的读取太耗费性能了
	if (SpriteFrameCache::getInstance()->getSpriteFrameByName(filename) == nullptr)
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("assets.plist", "assets.png");

	ret->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(filename));

    if (ret == nullptr)
    {
		string error = filename + " 加载失败";
		cocos2d::log(error.c_str());
    }
	return ret;
}

Vec2 getCocosVector(float angle)
{
	Vec2 ret;
	ret.x = bcos(angle);
	ret.y = bsin(angle);

	return ret;
}