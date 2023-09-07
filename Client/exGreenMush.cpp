#include "exGreenMush.h"
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
#include "exEffectManger.h"

// Player Skill
#include "exRaisingblow.h"
#include "exRaisingblowHit.h"
#include "exUpperCharge.h"
#include "exRush.h"
#include "exComboDeathFaultScreen.h"

namespace ex
{
	GreenMush::GreenMush()
		: mGreenMushDeadSound(nullptr)
	{
		mMonstersInfo.mMaxHp = 3000;
		mMonstersInfo.mHp = 3000;
		mMonstersInfo.mLevel = 10;
		mMonstersInfo.mDamage = 261;
		mMonstersInfo.mExp = 10.0f;
	}

	GreenMush::~GreenMush()
	{
	}

	void GreenMush::Initialize()
	{
		Texture* image = ResourceManager::Load<Texture>(L"GreenMushLeft"
			, L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\GreenMush_LEFT.bmp");

		mAnimator->CreateAnimation(L"GreenMushLeftIdle", image, math::Vector2(0.0f, 60.0f), math::Vector2(60.0f, 60.0f)
			, math::Vector2(60.0f, 60.0f), 1);
		mAnimator->CreateAnimation(L"GreenMushLeftMove", image, math::Vector2(60.0f, 60.0f), math::Vector2(60.0f, 60.0f)
			, math::Vector2(60.0f, 60.0f), 4);
		mAnimator->CreateAnimation(L"GreenMushLeftHit", image, math::Vector2(0.0f, 120.0f), math::Vector2(60.0f, 60.0f)
			, math::Vector2(60.0f, 60.0f), 1);
		mAnimator->CreateAnimation(L"GreenMushLeftDead", image, math::Vector2(0.0f, 0.0f), math::Vector2(60.0f, 60.0f)
			, math::Vector2(60.0f, 60.0f), 4);

		image = ResourceManager::Load<Texture>(L"GreenMushRight"
			, L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\GreenMush_RIGHT.bmp");
		mAnimator->CreateAnimation(L"GreenMushRightIdle", image, math::Vector2(0.0f, 60.0f), math::Vector2(60.0f, 60.0f)
			, math::Vector2(60.0f, 60.0f), 1);
		mAnimator->CreateAnimation(L"GreenMushRightMove", image, math::Vector2(60.0f, 60.0f), math::Vector2(60.0f, 60.0f)
			, math::Vector2(60.0f, 60.0f), 4);
		mAnimator->CreateAnimation(L"GreenMushRightHit", image, math::Vector2(0.0f, 120.0f), math::Vector2(60.0f, 60.0f)
			, math::Vector2(60.0f, 60.0f), 1);
		mAnimator->CreateAnimation(L"GreenMushRightDead", image, math::Vector2(0.0f, 0.0f), math::Vector2(60.0f, 60.0f)
			, math::Vector2(60.0f, 60.0f), 4);

		mGreenMushDeadSound = ResourceManager::Load<Sound>(L"GreenMushDeadSound", L"..\\Resources\\Maple\\Sound\\Monster\\Mush\\Mush_Die.wav");

		mCollider->SetSize(math::Vector2(55.0f, 70.0f));
		mCollider->SetOffset(math::Vector2(5.0f, 4.0f));
		mAnimator->SetAffectedCamera(true);
		mDirection = mTransform->GetMoveDir();
		mMoveTime = mMoveDelay;
	}

	void GreenMush::Update()
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

	void GreenMush::Render(HDC _hdc)
	{

		GameObject::Render(_hdc);
	}

	void GreenMush::Idle()
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
				mAnimator->PlayAnimation(L"GreenMushLeftIdle", true);
			}
			else
			{
				mAnimator->PlayAnimation(L"GreenMushRightIdle", true);
			}
		}
	}

	void GreenMush::Move()
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
				mAnimator->PlayAnimation(L"GreenMushLeftMove", true);
				pos.x -= 50.0f * Time::GetDeltaTime();
			}
			else
			{
				mAnimator->PlayAnimation(L"GreenMushRightMove", true);
				pos.x += 50.0f * Time::GetDeltaTime();
			}
		}

		mTransform->SetPosition(pos);
	}

	void GreenMush::Chase()
	{
	}

	void GreenMush::Hit()
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
			mGreenMushDeadSound->Play(false);
			mMonsterState = eMonsterState::Dead;
			Player* player = SceneManager::GetPlayer();
			player->GetInfo()->mExp += mMonstersInfo.mExp;
		}
	}

	void GreenMush::Dead()
	{
		if (mDirection == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"GreenMushLeftDead", false);

		}
		else
		{
			mAnimator->PlayAnimation(L"GreenMushRightDead", false);
		}
		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (bCheck)
		{
			Destroy(this);
		}


	}
	void GreenMush::OnCollisionEnter(Collider* _other)
	{
		PlayerAttack* playerAtt = dynamic_cast<PlayerAttack*>(_other->GetOwner());
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



	void GreenMush::OnCollisionStay(Collider* _other)
	{
	}

	void GreenMush::OnCollisionExit(Collider* _other)
	{
	}
}