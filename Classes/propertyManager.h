#pragma once
#ifndef _PROPERTY_MANAGER_H_
#define _PROPERTY_MANAGER_H_
#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class propertyManager :public Ref
{
public:
	propertyManager();
	~propertyManager();
	CREATE_FUNC(propertyManager);
	virtual bool init();
public:
	CC_SYNTHESIZE(int, ID, ID);
	CC_SYNTHESIZE(int, HP, HP);
	CC_SYNTHESIZE(int, SPEED, SPEED);
	CC_SYNTHESIZE(int, ATK, ATK);

	CC_SYNTHESIZE(std::string, ArmatureName, ArmatureName);//资源路经
	CC_SYNTHESIZE(std::string, DataName, DataName);//动画名字
	CC_SYNTHESIZE(std::string, PlayerName, PlayerName);//人物名字

	CC_SYNTHESIZE(Rect, HitRect, HitRect);
	CC_SYNTHESIZE(Point, HitPoint, HitPoint);

	CC_SYNTHESIZE(Rect, GetHitRect, GetHitRect);
	CC_SYNTHESIZE(Point, GetHitPoint, GetHitPoint);

	CC_SYNTHESIZE(unsigned int, LockLimit, LockLimit);
	CC_SYNTHESIZE(unsigned int, ATKLimit, ATKLimit);
};

#endif 

