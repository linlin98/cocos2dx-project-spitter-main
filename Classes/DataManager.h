#pragma once
#ifndef _DATA_MANAGER_
#define _DATA_MANAGER_

#include "cocos2d.h"
#include <iostream>
#include <string>
#include <vector>
#include "json/rapidjson.h"
#include "json/document.h"
USING_NS_CC;
using namespace rapidjson;
class DataManager : public Ref
{
public:
	DataManager();
	virtual ~DataManager();
public:
	static DataManager * getInstance();
	void initWithJsonFile(const char * filename);
	std::vector<std::string> getLevelDataWithIndex(int index);
public:
	std::string tollgateData;
	std::vector<std::string> _levelDataArray;
	CC_SYNTHESIZE(int, levelIndex, levelIndex);
};

#endif