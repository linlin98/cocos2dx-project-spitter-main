#pragma 
#ifndef _TEXT_SUPER_EFFECTS_
#define _TEXT_SUPER_EFFECTS_

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class TextSuperEffects : public Node
{
public:
	TextSuperEffects();
	virtual ~TextSuperEffects();

	static TextSuperEffects * create(const char * str,const int index = 0);

	bool init(const char * str,const int index = 0);

	void startAnimation();

	void removeObjects();


public:

	Label * label;

};

#endif