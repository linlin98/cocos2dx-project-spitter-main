#pragma once
#ifndef _LOADLAYER_
#define _LOADLAYER_

#include <iostream>
#include "cocos2d.h"
#include "SceneManager.h"

USING_NS_CC;
class LoadLayer :public Layer
{
public:
	LoadLayer();
	virtual ~LoadLayer();
	CREATE_FUNC(LoadLayer);
	virtual bool init();
	void onScheduleOnce(float dt);

public:
	SceneManager * tsm;
};
#endif
