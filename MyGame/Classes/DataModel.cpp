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

Vec2 getCocosVector(float angle)
{
	Vec2 ret;
	ret.x = bcos(angle);
	ret.y = bsin(angle);

	return ret;
}