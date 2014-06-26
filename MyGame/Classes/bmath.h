#ifndef __MATH_DEFINE_H__
#define __MATH_DEFINE_H__
#include <stdlib.h>
#include <math.h>

//////////////////////////////////////////////////////////////////
#define BABS(x) (x < 0 ? -x : x)
#define BMAX(x,y) (x > y ? x : y)
#define BMIN(x,y) (x < y ? x : y)
#define ANGLE_TO_RADIAN( angle ) ( angle * 0.0174427 ) 
#define RADIAN_TO_ANGLE( r ) ( r * 57.3305f )

#define PI 3.14159265358979323846f
#define HALF_PI 1.57f
#define ANGLE_PI 180.f
#define ANGLE_HALF_PI 90.f
#define SX 320
#define SY 650
	
///////////////////////////////////////////////////////////////////////////
float bFloatRand( float low, float height, int accuracy = 10 );

int bIntRand( int low, int height );

float bsqrt( float number );

double bsin( double x );

double bcos( double x );

double bacos( double x );

double batan2( double y, double x );

#endif