#pragma once
#ifndef _MONSTER_
#define _MONSTER_

#include "cocos2d.h"
#include "BaseRole.h"
#include "RoleCardController.h"

USING_NS_CC;
class Monster : public BaseRole
{
public:
	Monster();
	virtual ~Monster();
public:
	static Monster * creatWithProperty(propertyManager * manager);
	bool init(propertyManager * manager);
	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags)override;
	virtual void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
	virtual void animationEvent(Armature * pArmature, MovementEventType movmentType, const std::string & movementIDstr);
public:
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
