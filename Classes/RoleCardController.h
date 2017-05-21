#pragma once
#ifndef _ROLE_CARD_CONTROLLER_
#define _ROLE_CARD_CONTROLLER_

#include "cocos2d.h"
#include <iostream>
#include "BaseRole.h"
USING_NS_CC;


class RoleCardController : public Ref
{
public:
	RoleCardController();
	virtual ~RoleCardController();
public:
	static RoleCardController* getInstance();
	bool init();
	void purge();
public:
	CC_SYNTHESIZE(int, HeroID, HeroID);
public:
	std::vector<BaseRole *> heroVec;
	std::vector<BaseRole *> monsterVec;

	BaseRole * getHero();
};

#endif

