#pragma once
#ifndef _BASE_ROLE_H_
#define _BASE_ROLE_H_
#include <iostream>
#include "cocos2d.h"
#include "propertyManager.h"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;
//using namespace CocosDenshion;
using namespace cocostudio;

typedef enum RoleType
{
	TYPE_HERO = 1,
	TYPE_MONSTER = 2,
}RoleType;

class BaseRole : public Node
{
public:
	BaseRole();
	virtual ~BaseRole();
	static BaseRole * creatWithProperty(propertyManager * manager);
	bool init(propertyManager * manager);
public:
	propertyManager * propertymanager;
	RoleType type;
	CC_SYNTHESIZE(Armature *, armature, Armature);
};
#endif

