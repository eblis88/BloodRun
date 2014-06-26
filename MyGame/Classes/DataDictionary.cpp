#include "DataDictionary.h"


DataDictionary* DataDictionary::_thisInstance;

DataDictionary::DataDictionary()
{
	//const char* file_path = FileUtils::getInstance()->fullPathForFilename("gun.json").c_str();
    //log("external file path = %s",file_path);

    //打印JSon文件的内容
    //printf("%s\n",contentStr.c_str());
}

DataDictionary* DataDictionary::Instance()
{
	if (_thisInstance == nullptr) _thisInstance = new DataDictionary();
	return _thisInstance;
}
Document* DataDictionary::getDoc(string name)
{
	if (doc.find(name) == doc.end())
		addFile(name);

	return doc.at(name);	
}

void DataDictionary::addFile(string name)
{
	std::string contentStr = FileUtils::getInstance()->getStringFromFile(name);
	//contentStr = FileUtils::getInstance()->getStringFromFile("gun.txt");
    Document* thisdoc = new Document();
	thisdoc->Parse<0>(contentStr.c_str());
	doc.insert(std::pair<string, Document*>(name, thisdoc));
}


DataDictionary::~DataDictionary()
{
	for (auto dnp : doc)
	{
		delete dnp.second;
	}

	doc.clear();
}