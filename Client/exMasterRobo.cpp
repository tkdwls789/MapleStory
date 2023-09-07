#include "exMasterRobo.h"
#include "exTransform.h"
#include "exInput.h" 
#include "exTime.h"
#include "exObject.h"
#include "exResourceManager.h"
#include "exAnimator.h"
#include "exTexture.h"
#include "exCollider.h"
#include "exPlayerAttack.h"
#include "exPlayer.h"
#include "exSceneManager.h"
#include "exDamageManager.h"
#include "exSound.h"

// PlayerSkill
#include "exRaisingblow.h"
#include "exRaisingblowHit.h"
#include "exUpperCharge.h"
#include "exRush.h"
#include "exComboDeathFaultScreen.h"

namespace ex
{
	MasterRobo::MasterRobo()
		: mMasterRoboDeadSound(nullptr)
	{
		mMonstersInfo.mMaxHp = 3500000;
		mMonstersInfo.mHp = 3500000;
		mMonstersInfo.mLevel = 10;
		mMonstersInfo.mDamage = 1212;
		mMonstersInfo.mExp = 23;
	}

	MasterRobo::~MasterRobo()
	{
	}

	void MasterRobo::Initialize()
	{
		// left
		mAnimator->CreateAnimationFolder(L"MasterRoboLeftIdle",
			L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\MasterRobo\\Idle\\Left");

		mAnimator->CreateAnimationFolder(L"MasterRoboLeftMove",
			L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\MasterRobo\\Move\\Left");

		mAnimator->CreateAnimationFolder(L"MasterRoboLeftHit",
			L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\MasterRobo\\Hit\\Left");

		mAnimator->CreateAnimationFolder(L"MasterRoboLeftDead",
			L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\MasterRobo\\Die\\Left");


		// Right
		mAnimator->CreateAnimationFolder(L"MasterRoboRightIdle",
			L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\MasterRobo\\Idle\\Right");

		mAnimator->CreateAnimationFolder(L"MasterRoboRightMove",
			L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\MasterRobo\\Move\\Right");

		mAnimator->CreateAnimationFolder(L"MasterRoboRightHit",
			L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\MasterRobo\\Hit\\Right");

		mAnimator->CreateAnimationFolder(L"MasterRoboRightDead",
			L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\MasterRobo\\Die\\Right");;


		mMasterRoboDeadSound = ResourceManager::Load<Sound>(L"MasterRoboDeadSound", L"..\\Resources\\Maple\\Sound\\Monster\\Robo\\Robo_Die.wav");
		mCollider->SetSize(math::Vector2(80.0f, 92.0f));
		//mCollider->SetOffset(math::Vector2(1.0f, 1.0f));
		mAnimator->SetAffectedCamera(true);
		mDirection = mTransform->GetMoveDir();
		mMoveTime = mMoveDelay;
	}

	void MasterRobo::Update()
	{
		switch (mMonsterState)
		{
		case ex::Monsters::eMonsterState::Idle:
			Idle();
			break;
		case ex::Monsters::eMonsterState::Move:
			Move();
			break;
		case ex::Monsters::eMonsterState::Chase:
			Chase();
			break;
		case ex::Monsters::eMonsterState::Hit:
			Hit();
			break;
		case ex::Monsters::eMonsterState::Dead:
			Dead();
			break;
		default:
			break;
		}

		GameObject::Update();
	}

	void MasterRobo::Render(HDC _hdc)
	{

		GameObject::Render(_hdc);
	}

	void MasterRobo::Idle()
	{
		mIdleDelay += Time::GetDeltaTime();

		math::Vector2 pos = mTransform->GetPosition();
		if (mIdleDelay >= 2.3f)
		{
			if (mDirection == enums::eMoveDir::Left)
			{
				mDirection = enums::eMoveDir::Right;
			}
			else
			{
				mDirection = enums::eMoveDir::Left;
			}
			mMonsterState = eMonsterState::Move;
			mIdleDelay = 0.0f;
		}
		else
		{
			if (mDirection == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"MasterRoboLeftIdle", true);
			}
			else
			{
				mAnimator->PlayAnimation(L"MasterRoboRightIdle", true);
			}
		}
	}

	void MasterRobo::Move()
	{
		mMoveTime -= Time::GetDeltaTime();
		math::Vector2 pos = mTransform->GetPosition();
		if (mMoveTime <= 0.0f)
		{
			mMonsterState = eMonsterState::Idle;
			mMoveTime = mMoveDelay;
		}
		else
		{
			if (mDirection == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"MasterRoboLeftMove", true);
				pos.x -= 50.0f * Time::GetDeltaTime();
			}
			else
			{
				mAnimator->PlayAnimation(L"MasterRoboRightMove", true);
				pos.x += 50.0f * Time::GetDeltaTime();
			}
		}

		mTransform->SetPosition(pos);
	}

	void MasterRobo::Chase()
	{
	}

	void MasterRobo::Hit()
	{
		enums::eMoveDir playerDir = SceneManager::GetPlayer()->GetComponent<Transform>()->GetMoveDir();
		if (playerDir == enums::eMoveDir::Left)
		{
			mDirection = enums::eMoveDir::Right;
		}
		else
		{
			mDirection = enums::eMoveDir::Left;
		}

		if (mMonstersInfo.mHp <= 0)
		{
			mMasterRoboDeadSound->Play(false);
			mMonsterState = eMonsterState::Dead;
			Player* player = SceneManager::GetPlayer();
			player->GetInfo()->mExp += mMonstersInfo.mExp;
		}
	}

	void MasterRobo::Dead()
	{
		if (mDirection == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"MasterRoboLeftDead", false);

		}
		else
		{
			mAnimator->PlayAnimation(L"MasterRoboRightDead", false);
		}

		bool bCheck = mAnimator->IsActiveAnimationComplete();

		if (bCheck)
		{
			Destroy(this);
		}


	}
	void MasterRobo::OnCollisionEnter(Collider* _other)
	{

		PlayerAttack* playerAtt = dynamic_cast<PlayerAttack*>(_other->GetOwner());
		enums::eMoveDir playerDir = SceneManager::GetPlayer()->GetComponent<Transform>()->GetMoveDir();
		if (playerAtt != nullptr && mMonsterState != eMonsterState::Dead)
		{
			std::set<GameObject*>* attList = playerAtt->GetAttackList();

			if (attList->find(this) == attList->end())
			{
				mMonsterState = eMonsterState::Hit;
				attList->insert(this);

			}
		}
		Raisingblow* raisingblow = dynamic_cast<Raisingblow*>(_other->GetOwner());
		if (raisingblow != nullptr && mMonsterState != eMonsterState::Dead)
		{
			std::set<GameObject*>* attList = raisingblow->GetAttackList();

			if (attList->find(this) == attList->end())
			{
				RaisingblowHit* raisingBlowHit = new RaisingblowHit(this);
				object::ActiveSceneAddGameObject(enums::eLayerType::Effect, raisingBlowHit);
				mMonsterState = eMonsterState::Hit;
				attList->insert(this);

			}
		}

		UpperCharge* upperCharge = dynamic_cast<UpperCharge*>(_other->GetOwner());
		if (upperCharge != nullptr && mMonsterState != eMonsterState::Dead)
		{
			std::set<GameObject*>* attList = upperCharge->GetAttackList();

			if (attList->find(this) == attList->end())
			{
				mMonsterState = eMonsterState::Hit;
				attList->insert(this);

			}
		}

		Rush* rush = dynamic_cast<Rush*>(_other->GetOwner());
		if (rush != nullptr && mMonsterState != eMonsterState::Dead)
		{
			std::set<GameObject*>* attList = rush->GetAttackList();

			if (attList->find(this) == attList->end())
			{
				mMonsterState = eMonsterState::Hit;
				attList->insert(this);

			}
		}

		ComboDeathFaultScreen* ComboDeathFault = dynamic_cast<ComboDeathFaultScreen*>(_other->GetOwner());
		if (ComboDeathFault != nullptr && mMonsterState != eMonsterState::Dead)
		{
			std::set<GameObject*>* attList = ComboDeathFault->GetAttackList();

			if (attList->find(this) == attList->end())
			{
				mMonsterState = eMonsterState::Hit;
				attList->insert(this);
			}
		}
		if (mMonsterState != eMonsterState::Dead)
		{
			Player* player = dynamic_cast<Player*>(_other->GetOwner());
			if (player != nullptr && player->IsInvincible() == false)
			{
				DamageManager* damage = new DamageManager();
				object::ActiveSceneAddGameObject(enums::eLayerType::UI, damage);
				damage->SetPosition(math::Vector2(player->GetPositionX(), player->GetPositionY() - 28.0f));
				damage->PlayMonsterDamageAnimation(this->GetMonstersInfo().mDamage);

			}
		}

	}

	void MasterRobo::OnCollisionStay(Collider* _other)
	{
	}

	void MasterRobo::OnCollisionExit(Collider* _other)
	{
	}
}