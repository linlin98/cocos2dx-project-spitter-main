#include "BaseRole.h"



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

	return true;
}
