#pragma once
#ifndef _GAMELAYER_
#define _GAMELAYER_

#include <iostream>
#include "cocos2d.h"
#include "SceneManager.h"
#include "BaseRole.h"
#include "RoleCardController.h"
#include "BaseFSM.h"
#include "BaseAI.h"
#include "BaseRole.h"
#include "BaseTrap.h"
#include "Coin.h"
USING_NS_CC;

//typedef enum RoleFace
//{
//	FACE_LEFT = 1,
//	FACE_RIGHT,
//}RoleFace;
class GameLayer : public Layer
{
public:
	GameLayer();
	virtual ~GameLayer();
	CREATE_FUNC(GameLayer);
	virtual bool init();
	void menuCallBack(Ref * pSender);
	void update(float dt);
public:
	bool isKeyPressed(EventKeyboard::KeyCode keyCode);
	int keyPressedDurationDirection();
	int keyPressedDurationAcion();
	void setViewPointCenter(Point position);
public:
	void purge();
public:
	BaseRole * hero;
	BaseRole * monster;
	BaseRole * monster2;
	BaseTrap * trap;
	Coin * coin;
	SceneManager * tsm;
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
};
#endif
