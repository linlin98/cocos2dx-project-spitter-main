#pragma once
#ifndef _OPENLAYER_
#define _OPENLAYER_

#include <iostream>
#include "cocos2d.h"
#include "SceneManager.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
class OpenLayer :public Layer
{
public:
	OpenLayer();
	virtual ~OpenLayer();
	CREATE_FUNC(OpenLayer);
	virtual bool init();
	void menuCallBack(Ref * pSender);
public:
	SceneManager * tsm;
};
#endif
