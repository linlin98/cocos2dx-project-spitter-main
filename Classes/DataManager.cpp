#include "DataManager.h"

static DataManager * dataManager = nullptr;

DataManager::DataManager()
{
}


DataManager::~DataManager()
{
}

DataManager * DataManager::getInstance()
{
	if (dataManager == nullptr)
	{
		dataManager = new (std::nothrow) DataManager;
		//rolecardcontroller->init();
	}

	return dataManager;
}

void DataManager::initWithJsonFile(const char * filename)
{
	tollgateData = FileUtils::getInstance()->getStringFromFile(filename);
	log("´òÓ¡JsonÊý¾Ý %s", tollgateData.c_str());
}

std::vector<std::string> DataManager::getLevelDataWithIndex(int index)
{
	Document doc;
	doc.Parse<kParseDefaultFlags>(tollgateData.c_str());
	_levelDataArray.clear();
	rapidjson::Value &array = doc["Tollgate"];
	if (array.IsArray())
	{
		int i = index;
		for (int j = 0; j < array[i]["RollData"].Size(); j++)
		{
			rapidjson::Value & str = array[i]["RollData"][j];
			log("test str is %s", str.GetString());
			_levelDataArray.push_back(str.GetString());
		}
	}

	return _levelDataArray;
}



