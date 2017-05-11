#include "GameLayer.h"




GameLayer::GameLayer()
{
}


GameLayer::~GameLayer()
{
}

bool GameLayer::init()
{
	this->scheduleUpdate();
	//Director::getInstance()->getScheduler()->schedule(schedule_selector(ControlLayer::update), this, (float)1 / 60, false);

	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		keys[keyCode] = true;
	};

	listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		keys[keyCode] = false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	propertyManager * pManager = propertyManager::create();
	//pManager->setPlayerName("A");
	pManager->setArmatureName("hero");
	pManager->setDataName("hero/hero.ExportJson");
	pManager->setSPEED(2);//前进后退速度应该不一致，有待修改
	//pManager->setHP()
	pManager->retain();

	hero = BaseRole::creatWithProperty(pManager);
	hero->setPosition(Vec2(400,200));
	hero->type = static_cast<RoleType>(1);
	hero->state = ROLE_DEFAULT;
	this->addChild(hero,1,1);

	RoleCardController::getInstance()->heroVec.push_back(hero);

	BaseFSM * basefsm = BaseFSM::createFSM(hero);
	basefsm->retain();
	hero->setBaseFSM(basefsm);

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

void GameLayer::update(float dt)
{
	Node::update(dt);
	auto leftArrow = EventKeyboard::KeyCode::KEY_LEFT_ARROW, 
		rightArrow = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
	hero->getBaseFSM()->switchMoveState(keyPressedDuration());
	//hero->getBaseFSM()->switchMoveState();
}

bool GameLayer::isKeyPressed(EventKeyboard::KeyCode keyCode)
{
	if (keys[keyCode]) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}

int GameLayer::keyPressedDuration()
{
	auto leftArrow = EventKeyboard::KeyCode::KEY_LEFT_ARROW, 
		rightArrow = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
	if (isKeyPressed(leftArrow)) 
	{
		return FACE_LEFT;
	}
	else if (isKeyPressed(rightArrow)) 
	{
		return FACE_RIGHT;
	}
	else
	{
		return 0;
	}
}
