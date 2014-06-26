#include "ICanRefresh.h"


ICanRefresh::ICanRefresh(const string& filename)
{
	_refObject = Sprite::create(filename);
}


ICanRefresh::~ICanRefresh()
{
	// 据说是auto release的
	//delete _refObject;
}
