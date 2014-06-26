#pragma once
#include <DataModelBase.h>

class ICanRefresh
{
public:
	ICanRefresh(const string& filename);
	~ICanRefresh();

private:
	Sprite* _refObject;
};

