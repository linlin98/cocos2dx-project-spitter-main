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

	static TextSuperEffects * create(const char * str);

	bool init(const char * str);

	void startAnimation();

	void removeObjects();


public:

	Label * label;

};

#endif