#include "ICanRefresh.h"


ICanRefresh::ICanRefresh(const string& filename)
{
	_refObject = Sprite::create(filename);
}


ICanRefresh::~ICanRefresh()
{
	// ��˵��auto release��
	//delete _refObject;
}
