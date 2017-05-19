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
	pManager->setID(1);
	pManager->setATK(10);
	pManager->setHP(100);
	pManager->setArmatureName("hero");
	pManager->setDataName("hero/hero.ExportJson");
	pManager->setSPEED(2);//前进后退速度应该不一致，有待修改
	//pManager->setHP()
	pManager->setGetHitRect({ { -40,-40 },{ 80,80 } });
	pManager->setHitRect({ {40,-40},{80,80} });
	pManager->setHitPoint(pManager->getHitRect().origin);
	pManager->setGetHitPoint(pManager->getGetHitRect().origin);
	pManager->setATKLimit(100);
	pManager->setLockLimit(400);
	pManager->retain();

	hero = BaseRole::creatWithProperty(pManager);
	hero->setPosition(Vec2(100, 200));
	hero->type = static_cast<RoleType>(1);
	hero->state = ROLE_DEFAULT;
	hero->face = FACE_RIGHT;

	this->addChild(hero, 1, 1);

	propertyManager * pManager2 = propertyManager::create();
	//pManager->setPlayerName("A");
	pManager2->setID(2);
	pManager2->setATK(10);
	pManager2->setHP(100);
	pManager2->setArmatureName("hero");
	pManager2->setDataName("hero/hero.ExportJson");
	pManager2->setSPEED(1);//前进后退速度应该不一致，有待修改
						  //pManager->setHP()
	pManager2->setGetHitRect({ { -40,-40 },{ 80,80 } });
	pManager2->setHitRect({ { 40,-40 },{ 80,80 } });
	pManager2->setHitPoint(pManager2->getHitRect().origin);
	pManager2->setGetHitPoint(pManager2->getGetHitRect().origin);
	pManager2->setATKLimit(100);
	pManager2->setLockLimit(200);
	pManager2->retain();

	monster = BaseRole::creatWithProperty(pManager2);
	monster->setPosition(Vec2(600,200));
	monster->type = static_cast<RoleType>(2);
	monster->state = ROLE_DEFAULT;
	monster->face = FACE_RIGHT;
	this->addChild(monster,1,1);

	RoleCardController::getInstance()->heroVec.push_back(hero);
	RoleCardController::getInstance()->setHeroID(hero->propertymanager->getID());
	RoleCardController::getInstance()->retain();
	RoleCardController::getInstance()->monsterVec.push_back(monster);
	RoleCardController::getInstance()->retain();

	BaseFSM * basefsm = BaseFSM::createFSM(hero);
	basefsm->retain();
	hero->setBaseFSM(basefsm);

	BaseFSM * basefsm2 = BaseFSM::createFSM(monster);
	basefsm2->retain();
	monster->setBaseFSM(basefsm2);

	//BaseAI * ai = BaseAI::creatAI(hero);
	//ai->retain();
	//hero->setBaseAI(ai);

	BaseAI * ai2 = BaseAI::creatAI(monster);
	ai2->retain();
	monster->setBaseAI(ai2);

	//ai->startRoleAI();
	ai2->startRoleAI();

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
			this->unscheduleAllSelectors();
			Director::getInstance()->getScheduler()->unscheduleAll();
			//monster->getBaseAI()->stopRoleAI();
			tsm->goOpenScene();
		}
		break;
	}
}

void GameLayer::update(float dt)
{
	Node::update(dt);
	auto leftArrow = EventKeyboard::KeyCode::KEY_LEFT_ARROW, 
		rightArrow = EventKeyboard::KeyCode::KEY_RIGHT_ARROW,
		a = EventKeyboard::KeyCode::KEY_A;
	hero->getBaseFSM()->switchActionState(keyPressedDurationAcion());

	auto itr = RoleCardController::getInstance()->monsterVec.begin();
	while (itr != RoleCardController::getInstance()->monsterVec.end())
	{
		if ((*itr)->state == ROLE_FREE)
		{
			(*itr)->purge();
			RoleCardController::getInstance()->monsterVec.erase(itr);
			break;
		}
		++itr;
	}
	if (RoleCardController::getInstance()->monsterVec.size() == 0 )
	{
		log("win");
	}

	itr = RoleCardController::getInstance()->heroVec.begin();
	while (itr != RoleCardController::getInstance()->heroVec.end())
	{
		if ((*itr)->state == ROLE_FREE)
		{
			(*itr)->purge();
			RoleCardController::getInstance()->heroVec.erase(itr);
			break;
		}
		++itr;
	}
	if (RoleCardController::getInstance()->heroVec.size() == 0)
	{
		log("lose");
	}

	//hero->getBaseFSM()->switchMoveState(keyPressedDurationDirection());
	
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

int GameLayer::keyPressedDurationDirection()
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

int GameLayer::keyPressedDurationAcion()
{
	auto leftArrow = EventKeyboard::KeyCode::KEY_LEFT_ARROW,
		rightArrow = EventKeyboard::KeyCode::KEY_RIGHT_ARROW,
		a = EventKeyboard::KeyCode::KEY_A;
	if (isKeyPressed(a))
	{
		return ROLE_ATTACK;
	}
	else if (isKeyPressed(leftArrow))
	{
		return FACE_LEFT;
	}
	else if (isKeyPressed(rightArrow))
	{
		return FACE_RIGHT;
	}
	return 0;
}
