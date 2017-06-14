#include "TextSuperEffects.h"



TextSuperEffects::TextSuperEffects()
{
}


TextSuperEffects::~TextSuperEffects()
{
}

TextSuperEffects * TextSuperEffects::create(const char * str,const int index)
{
	TextSuperEffects * texteffect = new TextSuperEffects;
	
	if (texteffect && texteffect->init(str, index))
	{
		texteffect->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(texteffect);
		return nullptr;
	}

	return texteffect;
}

bool TextSuperEffects::init(const char * str, const int index)
{
	label = Label::createWithSystemFont(str, "", 30);
	if (index==0)
	{
		label->setColor(Color3B::RED);
	}
	else if(index == 1)
	{
		label->setColor(Color3B::YELLOW);
	}
	
	this->addChild(label);

	return true;
}

void TextSuperEffects::startAnimation()
{
	auto easeIN = EaseExponentialIn::create(Spawn::create(MoveBy::create(.7f, Vec2(0, 150)), FadeOut::create(.7f), NULL));
	auto sequnence = Sequence::create(easeIN, CallFunc::create([&]() {this->removeObjects(); }), NULL);

	label->runAction(sequnence);
}

void TextSuperEffects::removeObjects()
{
	this->stopAllActions();
	this->removeAllChildrenWithCleanup(true);

	this->removeFromParent();
}
