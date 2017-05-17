#ifndef _BASE_AI_H_
#define _BASE_AI_H_
#pragma once
#include "cocos2d.h"
#include "BaseRole.h"
USING_NS_CC;

class BaseRole;

class BaseAI : public Ref
{
public:
	BaseAI();
	virtual ~BaseAI();
public:
	static BaseAI * creatAI(BaseRole * role);
	bool init(BaseRole * role);
	void startRoleAI();
	void stopRoleAI();
	void updateFunc(float dt);
	void purge();
public:
	BaseRole * baseRole;
};
#endif

