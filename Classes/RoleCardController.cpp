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
