#pragma once
#ifndef _BASE_FSM_
#define _BASE_FSM_

#include <iostream>
#include "cocos2d.h"
#include "BaseRole.h"
#include <cstring>
USING_NS_CC;
class BaseRole;
class BaseFSM : public Ref
{
public:
	BaseFSM();
	virtual ~BaseFSM();
public:
	static BaseFSM * createFSM(BaseRole * baserole);
	bool init(BaseRole * baserole);

	void purge();
public:
	void changeToDefault(int i = 0);//默认参数可以写在声明或定义，但不能兼得 
	void changeToDead();
	void changeToAttack();
	void changeToJump();
	void changeToLeft();
	void changeToRight();
	//void changeToEnemy();
	void switchMoveState(int state);
	void switchActionState(int state);

public:
	BaseRole * role;
};
#endif
