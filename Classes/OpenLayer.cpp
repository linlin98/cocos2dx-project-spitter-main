#include "OpenLayer.h"
#include "SimpleAudioEngine.h"

OpenLayer::OpenLayer()
{
}


OpenLayer::~OpenLayer()
{
}

bool OpenLayer::init()
{
	auto engine1=CocosDenshion::SimpleAudioEngine::getInstance();
	//auto engine = SimpleAudioEngine::getInstance();
	engine1->playBackgroundMusic("res/Myrne,Linying - Silver City.mp3", true);

	Size winSize = Director::getInstance()->getWinSize();
	auto sprite = Sprite::create("res/starback.jpg");
	sprite->setPosition(Point(winSize.width/2,winSize.height/2));
	this->addChild(sprite);
	
	Label * label = Label::createWithTTF("Spitter", "fonts/Marker Felt.ttf", 48);
	label->setPosition(Vec2(winSize.width / 2, winSize.height * 3 / 4));
	this->addChild(label);

	MenuItemLabel * menuItem = MenuItemLabel::create(Label::createWithTTF("Start", "fonts/Marker Felt.ttf", 30),
		CC_CALLBACK_1(OpenLayer::menuCallBack,this));
	menuItem->setTag(101);
	menuItem->setPosition(Vec2(winSize.width / 2, winSize.height*0.3));

	MenuItemLabel * menuItem_2 = MenuItemLabel::create(Label::createWithTTF("Exit", "fonts/Marker Felt.ttf", 30),
		CC_CALLBACK_1(OpenLayer::menuCallBack, this));
	menuItem_2->setTag(102);
	menuItem_2->setPosition(Vec2(winSize.width / 2, winSize.height*0.15));

	Menu * menu = Menu::create(menuItem, menuItem_2, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);
	return true;
}

void OpenLayer::menuCallBack(Ref * pSender)
{
	switch (((MenuItem *)pSender)->getTag())
	{
		case 101:
		{
			auto engine = CocosDenshion::SimpleAudioEngine::getInstance();
			engine->stopBackgroundMusic();

			tsm->goGameScene();
		}
		break;
		case 102:
		{
			Director::getInstance()->end();
			exit(0);
		}
		break;
	}
}
