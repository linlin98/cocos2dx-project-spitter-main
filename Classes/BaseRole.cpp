#include "BaseRole.h"
#include "BaseFSM.h"
#include "BaseAI.h"
#include "RoleCardController.h"


BaseRole::BaseRole()
{
}


BaseRole::~BaseRole()
{
}

//BaseRole * BaseRole::create(propertyManager * manager)
//{
//	BaseRole * baseRole = creatWithProperty(manager);
//	baseRole->
//}

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

	state = ROLE_DEFAULT;
	face = FACE_RIGHT;
	this->setcoinAmount(0);

	ArmatureDataManager::getInstance()->addArmatureFileInfo(propertymanager->getDataName());
	armature = Armature::create(propertymanager->getArmatureName());
	armature->getAnimation()->play("default");

	this->addChild(armature);

	armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(BaseRole::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	return true;
}

void BaseRole::fallHP(const char * hpCount)
{
	if (this->state!=ROLE_DEAD && state!=ROLE_FREE)
	{
		TextSuperEffects * effects = TextSuperEffects::create(hpCount);
		effects->startAnimation();
		this->addChild(effects);
	}
}

void BaseRole::addCoinAmount(const char * coinCount)
{
	if (this->state != ROLE_DEAD && state != ROLE_FREE)
	{
		TextSuperEffects * effects = TextSuperEffects::create(coinCount, 1);
		effects->startAnimation();
		this->addChild(effects);
	}
}

void BaseRole::purge()
{
	this->getBaseFSM()->purge();
	if (type == TYPE_MONSTER)
	{
		this->getBaseAI()->purge();
	}
	
	removeFromParent();

	if (this->type == TYPE_HERO)
	{
		lockRole = nullptr;
	}
	
	//CC_SAFE_RELEASE(lockRole);
	//CC_SAFE_RELEASE(this);

}

void BaseRole::jump()
{
	/*创建动作，2s，原地跳跃(即落地的地点相对于起跳地点x偏移0，y偏移0)，高度250，弹跳次数1*/
	CCJumpBy* jump = CCJumpBy::create(1.5f, ccp(-2, 0), 15, 1);
	/*callFunc也是一个动作，作用是调用一个函数*/
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(BaseRole::jumpEnd));
	/*组合动作*/
	CCActionInterval* jumpActions = CCSequence::create(jump, callFunc, NULL);

	runAction(jumpActions);
}

void BaseRole::jumpEnd()
{
	this->getBaseFSM()->changeToDefault();
}

Rect BaseRole::getRealRect(BaseRole * role, Rect rect)
{
	return Rect(rect.origin.x + role->getPositionX(), rect.origin.y + role->getPositionY(), rect.size.width, rect.size.height);
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
			if (this->type == TYPE_MONSTER && lockRole != nullptr && this->state != ROLE_DEAD && this->state != ROLE_FREE)
			{
				if (getRealRect(this,this->propertymanager->getHitRect()).intersectsRect(lockRole->getRealRect(lockRole,lockRole->propertymanager->getGetHitRect())))
				{
					int atk = propertymanager->getATK();
					__String * hpStr = __String::createWithFormat("%d", atk);
					lockRole->fallHP(hpStr->getCString());
					
					lockRole->propertymanager->setHP(lockRole->propertymanager->getHP() - atk);
					if (lockRole->propertymanager->getHP() <= 0)
					{
						//lockRole->getBaseAI()->stopRoleAI();
						lockRole->getBaseFSM()->changeToDead();
					}
				}
			}
			else if(this->type == TYPE_HERO && !(RoleCardController::getInstance()->monsterVec.empty()))
			{
				for (int i = 0; i < RoleCardController::getInstance()->monsterVec.size(); i++)
				{
					if (getRealRect(this, this->propertymanager->getHitRect()).intersectsRect(RoleCardController::getInstance()->monsterVec[i]->getRealRect(RoleCardController::getInstance()->monsterVec[i], RoleCardController::getInstance()->monsterVec[i]->propertymanager->getGetHitRect())))
					{
						int atk = propertymanager->getATK();
						__String * hpStr = __String::createWithFormat("%d", atk);
						RoleCardController::getInstance()->monsterVec[i]->fallHP(hpStr->getCString());

						RoleCardController::getInstance()->monsterVec[i]->propertymanager->setHP(RoleCardController::getInstance()->monsterVec[i]->propertymanager->getHP() - atk);
						if (RoleCardController::getInstance()->monsterVec[i]->propertymanager->getHP() <= 0)
						{
							RoleCardController::getInstance()->monsterVec[i]->getBaseAI()->stopRoleAI();
							RoleCardController::getInstance()->monsterVec[i]->getBaseFSM()->changeToDead();
						}
					}
				}
			}
			else
			{

			}
		}
		if (movmentType == COMPLETE)
		{
			basefsm->changeToDefault(1);
		}
	}

	if (!strcmp(movementID, "die"))
	{
		if (movmentType == COMPLETE)
		{
			armature->runAction(Sequence::create(FadeOut::create(.5f), CallFunc::create([=]() {state = ROLE_FREE; }), NULL));
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
