#include "Monster.h"



Monster::Monster()
{
}


Monster::~Monster()
{
}

Monster * Monster::creatWithProperty(propertyManager * manager)
{
	Monster * monster = new Monster;
	if (monster && monster->init(manager))
	{
		monster->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(monster);
		return nullptr;
	}
	return monster;
}

bool Monster::init(propertyManager * manager)
{
	propertymanager = manager;

	ArmatureDataManager::getInstance()->addArmatureFileInfo(propertymanager->getDataName());
	armature = Armature::create(propertymanager->getArmatureName());
	armature->getAnimation()->play("default");

	this->addChild(armature);

	armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(Monster::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	return true;
}

void Monster::draw(cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform, uint32_t flags)
{
	_customCommand.init(_globalZOrder);
	_customCommand.func = CC_CALLBACK_0(Monster::onDraw, this, transform, flags);
	renderer->addCommand(&_customCommand);
}

void Monster::onDraw(const cocos2d::Mat4 & transform, uint32_t flags)
{
	Director * director = Director::getInstance();
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

	CHECK_GL_ERROR_DEBUG();

	Rect rect = propertymanager->getHitRect();
	DrawPrimitives::setDrawColor4B(0, 0, 255, 255);
	DrawPrimitives::drawRect(Vec2(rect.getMinX(), rect.getMinY()), Vec2(rect.getMaxX(), rect.getMaxY()));

	rect = propertymanager->getGetHitRect();
	DrawPrimitives::setDrawColor4B(0, 255, 0, 255);
	DrawPrimitives::drawRect(Vec2(rect.getMinX(), rect.getMinY()), Vec2(rect.getMaxX(), rect.getMaxY()));

	CHECK_GL_ERROR_DEBUG();
	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void Monster::animationEvent(Armature * pArmature, MovementEventType movmentType, const std::string & movementIDstr)
{
	const char * movementID = movementIDstr.c_str();
	if (!strcmp(movementID, "attack"))
	{
		if (movmentType == START)
		{
			if (this->type == TYPE_MONSTER && lockRole != nullptr && this->state != ROLE_DEAD && this->state != ROLE_FREE)
			{
				if (getRealRect(this, this->propertymanager->getHitRect()).intersectsRect(lockRole->getRealRect(lockRole, lockRole->propertymanager->getGetHitRect())))
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
			else if (this->type == TYPE_HERO && !(RoleCardController::getInstance()->monsterVec.empty()))
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

	if (!strcmp(movementID, "gethit"))
	{
		if (movmentType == COMPLETE)
		{
			armature->runAction(Sequence::create(FadeOut::create(.5f), CallFunc::create([=]() {state = ROLE_FREE; }), NULL));
		}
	}
}
