#include "Coin.h"



Coin::Coin()
{
}


Coin::~Coin()
{
}

Coin * Coin::createWithProperty(propertyManager * manager,BaseRole * hero)
{
	Coin * coin = new Coin;
	if (coin&&coin->init(manager,hero))
	{
		coin->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(coin);
		return nullptr;
	}
	return coin;
}

bool Coin::init(propertyManager * manager,BaseRole * hero)
{
	this->hero = hero;
	this->propertymanager = manager;
	state = COIN_DEFAULT;
	//this->addChild("res/mushroom.png");
	ArmatureDataManager::getInstance()->addArmatureFileInfo(propertymanager->getDataName());
	armature = Armature::create(propertymanager->getArmatureName());
	armature->getAnimation()->play("coin");

	this->addChild(armature);

	armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(Coin::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	return true;
}

void Coin::addCoinAmount(int amount)
{
	hero->setcoinAmount(amount + hero->getcoinAmount());
	__String * coinStr = __String::createWithFormat("%d", amount);
	hero->fallHP(coinStr->getCString());
}

void Coin::draw(cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform, uint32_t flags)
{
	_customCommand.init(_globalZOrder);
	_customCommand.func = CC_CALLBACK_0(Coin::onDraw, this, transform, flags);
	renderer->addCommand(&_customCommand);
}

void Coin::onDraw(const cocos2d::Mat4 & transform, uint32_t flags)
{
	Director * director = Director::getInstance();
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

	CHECK_GL_ERROR_DEBUG();

	Rect rect = propertymanager->getHitRect();
	DrawPrimitives::setDrawColor4B(0, 0, 255, 255);
	DrawPrimitives::drawRect(Vec2(rect.getMinX(), rect.getMinY()), Vec2(rect.getMaxX(), rect.getMaxY()));

	//rect = propertymanager->getGetHitRect();
	//DrawPrimitives::setDrawColor4B(0, 255, 0, 255);
	//DrawPrimitives::drawRect(Vec2(rect.getMinX(), rect.getMinY()), Vec2(rect.getMaxX(), rect.getMaxY()));

	CHECK_GL_ERROR_DEBUG();
	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

Rect Coin::getRealRect(Coin * coin, Rect rect)
{
	return Rect(rect.origin.x + coin->getPositionX(), rect.origin.y + coin->getPositionY(), rect.size.width, rect.size.height);
}

bool Coin::isColliding(BaseRole * role)
{
	return getRealRect(this, this->propertymanager->getHitRect()).intersectsRect(role->getRealRect(role, role->propertymanager->getGetHitRect()));
}

void Coin::animationEvent(Armature * pArmature, MovementEventType movmentType, const std::string & movementIDstr)
{
	const char * movementID = movementIDstr.c_str();

	if (!strcmp(movementID,"coin"))
	{
		if (this->state == COIN_COLLECTED)
		{
			armature->runAction(Sequence::create(FadeOut::create(.5f), CallFunc::create([=]() {state = COIN_FREE; }), NULL));
		}
	}
}