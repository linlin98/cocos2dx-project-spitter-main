#pragma once
#include "F:\learn\cpp\project\cocos2d-x-3.14.1\cocos2d-x-3.14.1\tools\cocos2d-console\bin\~\Desktop\HelloCpp\cocos2d\cocos\2d\CCLayer.h"
#ifndef _HelloWorldLayer_
#define _HelloWorldLayer_

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class HelloWorldLayer :	public Layer
{
public:
	HelloWorldLayer();
	virtual ~HelloWorldLayer();
	static HelloWorldLayer * create();
	virtual bool init();
};

#endif

