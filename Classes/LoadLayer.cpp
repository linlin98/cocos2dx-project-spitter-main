#include "LoadLayer.h"



LoadLayer::LoadLayer()
{
}


LoadLayer::~LoadLayer()
{
}

bool LoadLayer::init()
{
	Size winSize = Director::getInstance()->getWinSize();
	Label * label = Label::createWithTTF("Loading...","fonts/Marker Felt.ttf",32);
	//auto size = Director::getInstance()->getWinSize();
	
	label->setPosition(Point(winSize.width/2, winSize.height/2));

//	auto point = label->getPosition();

	this->addChild(label);
	scheduleOnce(CC_SCHEDULE_SELECTOR(LoadLayer::onScheduleOnce), 2.0);
	return true;
}

void LoadLayer::onScheduleOnce(float dt)
{
	tsm->goOpenScene();
}
