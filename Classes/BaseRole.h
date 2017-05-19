#pragma once
#ifndef _BASE_ROLE_H_
#define _BASE_ROLE_H_
#include <iostream>
#include "cocos2d.h"
#include "propertyManager.h"
#include "cocostudio/CocoStudio.h"
#include "BaseFSM.h"
#include "BaseAI.h"
#include "TextSuperEffects.h"
//#include "RoleCardController.h"
USING_NS_CC;
//using namespace CocosDenshion;
using namespace cocostudio;

typedef enum RoleType
{
	TYPE_HERO = 1,
	TYPE_MONSTER = 2,
}RoleType;

typedef enum RoleState
{
	ROLE_DEFAULT = 1,
	ROLE_MOVE,
	ROLE_DEAD,
	ROLE_ATTACK,
	ROLE_FREE,
}RoleState;

typedef enum RoleFace
{
	FACE_LEFT = 1,
	FACE_RIGHT,
}RoleFace;

class BaseFSM;
class BaseAI;
//class RoleCardController;

class BaseRole : public Node
{
public:
	BaseRole();
	virtual ~BaseRole();
	static BaseRole * creatWithProperty(propertyManager * manager);
	bool init(propertyManager * manager);
public:
	void fallHP(const char * hpCount);
	void purge();

	Rect getRealRect(BaseRole * role,Rect rect);

	void changeFaceDirection(RoleFace face);

	void animationEvent(Armature * pArmature, MovementEventType movmentType, const std::string & movementIDstr);

	void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags)override;
	void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
	cocos2d::CustomCommand _customCommand;
public:
	BaseRole * lockRole;

	propertyManager * propertymanager;
	//RoleCardController * rolecardcontroller;
	RoleType type;
	RoleState state;
	RoleFace face;
	int ID;

	CC_SYNTHESIZE(Armature *, armature, Armature);
	CC_SYNTHESIZE(BaseFSM *, basefsm, BaseFSM);
public:
	CC_SYNTHESIZE(BaseAI *, baseai, BaseAI);
};
#endif

