#pragma once
#include <iostream>
#include <cocos2d.h>
#include <BaseRole.h>
#include <propertyManager.h>

typedef enum CoinState
{
	COIN_FREE = 1,
	COIN_COLLECTED,
	COIN_DEFAULT,
}CoinState;

class Coin : public Node
{
public:
	Coin();
	virtual ~Coin();
public:
	static Coin * createWithProperty(propertyManager * manager,BaseRole * hero);
	bool init(propertyManager * manager,BaseRole * hero);
	void purge();
	void addCoinAmount(int amount);
public:
	BaseRole * hero;
	propertyManager * propertymanager;
	CoinState state;
public:
	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags)override;
	virtual void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
	cocos2d::CustomCommand _customCommand;
	virtual Rect getRealRect(Coin * trap, Rect rect);
	virtual void animationEvent(Armature * pArmature, MovementEventType movmentType, const std::string & movementIDstr);
public:
	virtual bool isColliding(BaseRole * role);
	CC_SYNTHESIZE(Armature *, armature, Armature);
};

