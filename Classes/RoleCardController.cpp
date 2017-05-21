#include "RoleCardController.h"

static RoleCardController * rolecardcontroller = nullptr;

RoleCardController::RoleCardController()
{
}


RoleCardController::~RoleCardController()
{
}

RoleCardController * RoleCardController::getInstance()
{
	if (rolecardcontroller == nullptr)
	{
		rolecardcontroller = new (std::nothrow) RoleCardController;
		rolecardcontroller->init();
	} 

	return rolecardcontroller;
}

bool RoleCardController::init()
{
	
	return true;
}

void RoleCardController::purge()
{
	if (heroVec.size() != 0)
	{
		for (int i = 0; i < heroVec.size(); i++)
		{
			heroVec[i]->purge();
		}
	}
	if (monsterVec.size() != 0)
	{
		for (int i = 0; i < monsterVec.size(); i++)
		{
			monsterVec[i]->purge();
		}
	}
	heroVec.clear();
	heroVec.shrink_to_fit();
	monsterVec.clear();
	monsterVec.shrink_to_fit();
}

BaseRole * RoleCardController::getHero()
{
	for (int i = 0; i < heroVec.size(); i++)
	{
		if (heroVec[i]->propertymanager->getID() == this->getHeroID())
		{
			return heroVec[i];
		}
	}
	return nullptr;
}
