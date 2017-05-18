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
