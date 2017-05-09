#include "HelloWorldLayer.h"

HelloWorldLayer * HelloWorldLayer::create()
{
	HelloWorldLayer * pRet = new HelloWorldLayer();

	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

bool HelloWorldLayer::init()
{
	if (Layer::init() == false)
	{
		return false;
	}

	Size size = Director::getInstance()->getVisibleSize();

	Label * label = Label::createWithTTF("HelloWorld", "fonts/Marker Felt.ttf", 24);
	label->setPosition(size.width / 2, size.height * 5 / 6);
	this->addChild(label);

	auto sprite = Sprite::create("HelloWorld.png");
	sprite->setPosition(size.width / 2, size.height / 2);
	this->addChild(sprite);

	return true;
}

HelloWorldLayer::HelloWorldLayer()
{
}


HelloWorldLayer::~HelloWorldLayer()
{
}
