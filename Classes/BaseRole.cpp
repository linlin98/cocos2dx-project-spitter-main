#include "BaseRole.h"
#include "BaseFSM.h"
#include "BaseAI.h"


BaseRole::BaseRole()
{
}


BaseRole::~BaseRole()
{
}

BaseRole * BaseRole::creatWithProperty(propertyManager * manager)
{
	BaseRole * baseRole = new BaseRole;
	if (baseRole && baseRole->init(manager))
	{
		baseRole->autorelease();
	} 
	else
	{
		CC_SAFE_DELETE(baseRole);
		return nullptr;
	}
	return baseRole;
}

bool BaseRole::init(propertyManager * manager)
{
	propertymanager = manager;

	ArmatureDataManager::getInstance()->addArmatureFileInfo(propertymanager->getDataName());
	armature = Armature::create(propertymanager->getArmatureName());
	armature->getAnimation()->play("default");

	this->addChild(armature);

	armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(BaseRole::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	return true;
}

void BaseRole::changeFaceDirection(RoleFace face)
{
	if (face == FACE_LEFT)
	{
		armature->setScaleX(-1);
		propertymanager->setHitRect(Rect(-propertymanager->getHitPoint().x - propertymanager->getHitRect().size.width, propertymanager->getHitRect().origin.y,propertymanager->getHitRect().size.width, propertymanager->getHitRect().size.width));
		this->face = face;
	} 
	else if(face == FACE_RIGHT)
	{
		armature->setScaleX(1);
		propertymanager->setHitRect(Rect(propertymanager->getHitPoint().x, propertymanager->getHitRect().origin.y, propertymanager->getHitRect().size.width, propertymanager->getHitRect().size.width));
		this->face = face;
	}
}

void BaseRole::animationEvent(Armature * pArmature, MovementEventType movmentType, const std::string & movementIDstr)
{
	const char * movementID = movementIDstr.c_str();
	if (!strcmp(movementID, "attack"))
	{
		if (movmentType == START)
		{
		}
		if (movmentType == COMPLETE)
		{
			basefsm->changeToDefault(1);
		}
	}
}

void BaseRole::draw(cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform, uint32_t flags)
{
	_customCommand.init(_globalZOrder);
	_customCommand.func = CC_CALLBACK_0(BaseRole::onDraw,this,transform,flags);
	renderer->addCommand(&_customCommand);
}

void BaseRole::onDraw(const cocos2d::Mat4 & transform, uint32_t flags)
{
	Director * director = Director::getInstance();
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

	CHECK_GL_ERROR_DEBUG();

	Rect rect = propertymanager->getHitRect();
	DrawPrimitives::setDrawColor4B(0, 0, 255, 255);
	DrawPrimitives::drawRect(Vec2(rect.getMinX(),rect.getMinY()), Vec2(rect.getMaxX(),rect.getMaxY()));

	rect = propertymanager->getGetHitRect();
	DrawPrimitives::setDrawColor4B(0, 255, 0, 255);
	DrawPrimitives::drawRect(Vec2(rect.getMinX(), rect.getMinY()), Vec2(rect.getMaxX(), rect.getMaxY()));

	CHECK_GL_ERROR_DEBUG();
	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}
