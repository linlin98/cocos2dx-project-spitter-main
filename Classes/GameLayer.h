#pragma once
#ifndef _GAMELAYER_
#define _GAMELAYER_

#include <iostream>
#include "cocos2d.h"
#include "SceneManager.h"
USING_NS_CC;
class GameLayer : public Layer
{
public:
	GameLayer();
	virtual ~GameLayer();
	CREATE_FUNC(GameLayer);
	virtual bool init();
	void menuCallBack(Ref * pSender);
public:
	SceneManager * tsm;
};
#endif
