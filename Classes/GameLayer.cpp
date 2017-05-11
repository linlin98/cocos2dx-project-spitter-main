#include "GameLayer.h"




GameLayer::GameLayer()
{
}


GameLayer::~GameLayer()
{
}

bool GameLayer::init()
{
	propertyManager * pManager = propertyManager::create();
	//pManager->setPlayerName("A");
	pManager->setArmatureName("hero");
	pManager->setDataName("hero/hero.ExportJson");
	//pManager->setHP()
	pManager->retain();

	auto hero = BaseRole::creatWithProperty(pManager);
	hero->setPosition(Vec2(400,200));
	hero->type = static_cast<RoleType>(1);
	this->addChild(hero,1,1);

	RoleCardController::getInstance()->heroVec.push_back(hero);

	auto winSize = Director::getInstance()->getWinSize();
	auto bg_pic = Sprite::create("res/background_demo.png");
	bg_pic->setPosition(Point(winSize.width / 2, winSize.height / 2));
	this->addChild(bg_pic);

	MenuItemLabel * menuItem = MenuItemLabel::create(Label::createWithTTF("Back", "fonts/Marker Felt.ttf", 20),
		CC_CALLBACK_1(GameLayer::menuCallBack, this));
	menuItem->setTag(101);
	menuItem->setPosition(Vec2(winSize.width * 0.95, winSize.height * 0.1));

	Menu * menu = Menu::create(menuItem, NULL, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);
	return true;
}

void GameLayer::menuCallBack(Ref * pSender)
{
	switch (((MenuItem *)pSender)->getTag())
	{
		case 101:
		{
			tsm->goOpenScene();
		}
		break;
	}
}