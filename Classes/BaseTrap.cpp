#include "BaseTrap.h"



BaseTrap::BaseTrap()
{
}


BaseTrap::~BaseTrap()
{
}

BaseTrap * BaseTrap::createWithProperty(propertyManager * manager, BaseRole * role)
{
	BaseTrap * baseTrap = new BaseTrap;
	if (baseTrap && baseTrap->init(manager, role))
	{
		baseTrap->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(baseTrap);
		return nullptr;
	}
	return baseTrap;
}

bool BaseTrap::init(propertyManager * manager,BaseRole * role)
{
	this->propertymanager = manager;
	this->currentPlayer = role;
	CCSprite::initWithFile("res/mushroom.png");
	ArmatureDataManager::getInstance()->addArmatureFileInfo(propertymanager->getDataName());
	armature = Armature::create(propertymanager->getArmatureName());
	armature->getAnimation()->play("default");

	this->addChild(armature);

	return true;
}
void BaseTrap::draw(cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform, uint32_t flags)
{
	_customCommand.init(_globalZOrder);
	_customCommand.func = CC_CALLBACK_0(BaseTrap::onDraw, this, transform, flags);
	renderer->addCommand(&_customCommand);
}

void BaseTrap::onDraw(const cocos2d::Mat4 & transform, uint32_t flags)
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

Rect BaseTrap::getRealRect(BaseTrap * trap, Rect rect)
{
	return Rect(rect.origin.x + trap->getPositionX(), rect.origin.y + trap->getPositionY(), rect.size.width, rect.size.height);
}

bool BaseTrap::isColliding(BaseRole * role)
{
	return getRealRect(this, this->propertymanager->getHitRect()).intersectsRect(role->getRealRect(role, role->propertymanager->getGetHitRect()));
}
