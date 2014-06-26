#pragma once
#include <cocos2d.h>
#include <string.h>
#include <map>
#include "json/document.h"

using namespace std;
using namespace rapidjson;
using namespace cocos2d;
class DataDictionary
{
protected:
	DataDictionary();
	~DataDictionary();
	static DataDictionary* _thisInstance;

	map<string, Document*> doc;
public:
	static DataDictionary* Instance();
	void addFile(string filename);

	Document* getDoc(string name);
};
