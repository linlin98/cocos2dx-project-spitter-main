#include "BaseAI.h"
#include "RoleCardController.h"
#include <vector>
#include <cmath>
#include <iostream>

BaseAI::BaseAI()
{
}


BaseAI::~BaseAI()
{
}

BaseAI * BaseAI::creatAI(BaseRole * role)
{
	BaseAI * ai = new BaseAI();
	if (ai && ai->init(role))
	{
		ai->autorelease();
	} 
	else
	{
		CC_SAFE_DELETE(ai);
	}
	return ai;
}

bool BaseAI::init(BaseRole * role)
{
	this->baseRole = role;
	return true;
}

void BaseAI::startRoleAI()
{
	Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(BaseAI::updateFunc), this, (float)1 / 60, false);
}

void BaseAI::updateFunc(float dt)
{
	//int i = 0;
	std::vector<BaseRole *> roleVec;
	if (baseRole->type != TYPE_MONSTER)//???喵喵喵，如果是==TYPE_HERO就会中断，迷
	{
		roleVec = RoleCardController::getInstance()->monsterVec;
	} 
	else
	{
		roleVec = RoleCardController::getInstance()->heroVec;
		//i = 1;
		//std::cout << "check" << std::endl;
	}

	int roleID = 0;
	if (roleVec.size() != 0)
	{
		float distance = Director::getInstance()->getVisibleSize().width;
		for (int i = 0;i<roleVec.size();i++)
		{
			float newDis = abs(baseRole->getPosition().distance((roleVec[i])->getPosition()));
			if (newDis < distance)
			{
				newDis = distance;
				roleID = i;
			}
		}

		if (roleVec[roleID]->getPositionX() > baseRole->getPositionX())
		{
			baseRole->changeFaceDirection(FACE_RIGHT);
		}
		else
		{
			baseRole->changeFaceDirection(FACE_LEFT);
		}
	} 
	else
	{
		return;
	}
}
