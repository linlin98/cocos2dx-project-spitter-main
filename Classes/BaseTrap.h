#pragma once
#include "cocos2d.h"
#include "propertyManager.h"
#include "BaseRole.h"
#include <iostream>
USING_NS_CC;
class BaseRole;
class BaseTrap : public Sprite
{
public:
	BaseTrap();
	virtual ~BaseTrap();
public:
	static BaseTrap * createWithProperty(propertyManager * manager,BaseRole * role);
	bool init(propertyManager * manager,BaseRole * role);
public:
	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags)override;
	virtual void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
	cocos2d::CustomCommand _customCommand;
	virtual Rect getRealRect(BaseTrap * trap, Rect rect);
public:
	propertyManager * propertymanager;
	BaseRole * currentPlayer;
public:
	virtual bool isColliding(BaseRole * role);
	CC_SYNTHESIZE(Armature *, armature, Armature);
};


