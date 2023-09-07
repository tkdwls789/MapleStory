#include "exMushMom.h"
#include "exMushMomHpBar.h"
#include "exTransform.h"
#include "exInput.h" 
#include "exTime.h"
#include "exResourceManager.h"
#include "exAnimator.h"
#include "exTexture.h"
#include "exCollider.h"
#include "exRigidbody.h"
#include "exSceneManager.h"
#include "exPlayer.h"
#include "exObject.h"
#include "exDamageManager.h"
#include "exSound.h"

// PlayerSkill
#include "exPlayerAttack.h"
#include "exRaisingblow.h"
#include "exRaisingblowHit.h"
#include "exRush.h"
#include "exUpperCharge.h"
#include "exComboDeathFaultScreen.h"

// MonsterSkill
#include "exMushMomSkill.h"


namespace ex
{
	MushMom::MushMom()
		: mSkillDamage(0)
		, mAttackDelay(0.0f)
		, mbMushMomHit(false)
		, mMushMomHitSound(nullptr)
		, mMushMomDeadSound(nullptr)
	{
		mMonstersInfo.mMaxHp = 300000000;
		mMonstersInfo.mHp = 300000000;
		mMonstersInfo.mLevel = 150;
		mMonstersInfo.mDamage = 700;
		mSkillDamage = 1303;
		mMonstersInfo.mExp = 100;
	}

	MushMom::~MushMom()
	{
	}

	void MushMom::Initialize()
	{
		// Left
		mAnimator->CreateAnimationFolder(L"MushMomLeftIdle",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\MushMom\\Idle\\Left", math::Vector2(0.0f, -20.0f));

		mAnimator->CreateAnimationFolder(L"MushMomLeftMove",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\MushMom\\Move\\Left", math::Vector2(0.0f, -103.0f));

		mAnimator->CreateAnimationFolder(L"MushMomLeftHit",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\MushMom\\Hit\\Left", math::Vector2(0.0f, -60.0f));

		mAnimator->CreateAnimationFolder(L"MushMomLeftDead",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\MushMom\\Die\\Left", math::Vector2(0.0f, -50.0f), 0.1f);

		mAnimator->CreateAnimationFolder(L"MushMomLeftAttack",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\MushMom\\Attack\\Left", math::Vector2(0.0f, -110.0f), 0.3f);

		// Right
		mAnimator->CreateAnimationFolder(L"MushMomRightIdle",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\MushMom\\Idle\\Right", math::Vector2(0.0f, -20.0f));

		mAnimator->CreateAnimationFolder(L"MushMomRightMove",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\MushMom\\Move\\Right", math::Vector2(0.0f, -103.0f));

		mAnimator->CreateAnimationFolder(L"MushMomRightHit",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\MushMom\\Hit\\Right", math::Vector2(0.0f, -60.0f));

		mAnimator->CreateAnimationFolder(L"MushMomRightDead",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\MushMom\\Die\\Right", math::Vector2(0.0f, -50.0f), 0.1f);

		mAnimator->CreateAnimationFolder(L"MushMomRightAttack",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\MushMom\\Attack\\Right", math::Vector2(0.0f, -110.0f), 0.3f);

		mMushMomHitSound = ResourceManager::Load<Sound>(L"MushMomHitSound", L"..\\Resources\\Maple\\Sound\\Monster\\MushMom\\MushMom_Hit.wav");
		mMushMomDeadSound = ResourceManager::Load<Sound>(L"MushMomDeadSound", L"..\\Resources\\Maple\\Sound\\Monster\\MushMom\\MushMom_Die.wav");

		mAnimator->SetAffectedCamera(true);
		mAnimator->SetScale(math::Vector2(2.2f, 2.2f));
		mCollider->SetSize(math::Vector2(300.0f, 200.0f));
		mCollider->SetOffset(math::Vector2(0.0f, 10.0f));

		mDirection = mTransform->GetMoveDir();
		mMoveTime = mMoveDelay;
	}

	void MushMom::Update()
	{

		switch (mMonsterState)
		{
		case ex::Monsters::eMonsterState::Idle:
			Idle();
			break;
		case ex::Monsters::eMonsterState::Move:
			Move();
			break;
		case ex::Monsters::eMonsterState::Attack:
			Attack();
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

	void MushMom::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void MushMom::Idle()
	{
		mIdleDelay += Time::GetDeltaTime();
		math::Vector2 playerPos = SceneManager::GetPlayer()->GetPosition();
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

		if (playerPos.x <= mTransform->GetPositionX())
		{
			mAnimator->PlayAnimation(L"MushMomLeftIdle", false);
			mDirection = enums::eMoveDir::Left;
		}
		else
		{
			mAnimator->PlayAnimation(L"MushMomRightIdle", false);
			mDirection = enums::eMoveDir::Right;
		}

		float distanceX = fabs(playerPos.x - this->GetPositionX());
		float distanceY = fabs(playerPos.y - this->GetPositionY());

		if (distanceX < 550.0f && distanceY < 80.0f)
		{
			MushMomSkill* mushMomSkill = new MushMomSkill(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, mushMomSkill);

			float playerPosX = SceneManager::GetPlayer()->GetPositionX();
			if (playerPosX <= mTransform->GetPositionX())
			{
				mAnimator->PlayAnimation(L"MushMomLeftAttack", false);
				mDirection = enums::eMoveDir::Left;
			}
			else
			{
				mAnimator->PlayAnimation(L"MushMomRightAttack", false);
				mDirection = enums::eMoveDir::Right;
			}
			mMonsterState = eMonsterState::Attack;

			mTransform->SetMoveDir(mDirection);
		}
	}

	void MushMom::Move()
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
				mAnimator->PlayAnimation(L"MushMomLeftMove", true);
				pos.x -= 50.0f * Time::GetDeltaTime();
			}
			else
			{
				mAnimator->PlayAnimation(L"MushMomRightMove", true);
				pos.x += 50.0f * Time::GetDeltaTime();
			}
		}

		math::Vector2 playerPos = SceneManager::GetPlayer()->GetPosition();
		float distanceX = fabs(playerPos.x - this->GetPositionX());
		float distanceY = fabs(playerPos.y - this->GetPositionY());
		if (distanceX < 550.0f && distanceY < 80.0f)
		{
			MushMomSkill* mushMomSkill = new MushMomSkill(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, mushMomSkill);
			enums::eMoveDir playerDir = SceneManager::GetPlayer()->GetComponent<Transform>()->GetMoveDir();

			if (playerPos.x <= mTransform->GetPositionX())
			{
				mAnimator->PlayAnimation(L"MushMomLeftAttack", false);
				mDirection = enums::eMoveDir::Left;
			}
			else
			{
				mAnimator->PlayAnimation(L"MushMomRightAttack", false);
				mDirection = enums::eMoveDir::Right;
			}
			mMonsterState = eMonsterState::Attack;
		}
		mTransform->SetMoveDir(mDirection);
		mTransform->SetPosition(pos);
	}

	void MushMom::Attack()
	{
		mAttackDelay += Time::GetDeltaTime();
		math::Vector2 playerPos = SceneManager::GetPlayer()->GetPosition();
		if (mAttackDelay >= 1.5f)
		{
			bool bCheck = mAnimator->IsActiveAnimationComplete();
			if (bCheck)
			{
				if (playerPos.x <= mTransform->GetPositionX())
				{
					mAnimator->PlayAnimation(L"MushMomLeftIdle", false);
					mDirection = enums::eMoveDir::Left;
				}
				else
				{
					mAnimator->PlayAnimation(L"MushMomRightIdle", false);
					mDirection = enums::eMoveDir::Right;
				}
				mMonsterState = eMonsterState::Idle;
			}
			mAttackDelay = 0.0f;
		}
	}

	void MushMom::Chase()
	{
	}

	void MushMom::Hit()
	{
		enums::eMoveDir playerDir = SceneManager::GetPlayer()->GetTransform()->GetMoveDir();
		float playerPosX = SceneManager::GetPlayer()->GetPositionX();
		float MushMomPosX = mTransform->GetPositionX();
		if (playerPosX <= MushMomPosX)
		{
			mAnimator->PlayAnimation(L"MushMomLeftHit", false);
			mDirection = enums::eMoveDir::Left;
		}
		else
		{
			mAnimator->PlayAnimation(L"GateKeeperRightHit", false);
			mDirection = enums::eMoveDir::Right;
		}
		mHitDelay += Time::GetDeltaTime();

		if (playerDir == enums::eMoveDir::Left)
		{
			mDirection = enums::eMoveDir::Right;
		}
		else
		{
			mDirection = enums::eMoveDir::Left;
		}

		if (mHitDelay >= 1.3f)
		{
			if (mDirection == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"MushMomLeftMove", true);
			}
			else
			{
				mAnimator->PlayAnimation(L"MushMomRightMove", true);
			}

			mMonsterState = eMonsterState::Move;
			mHitDelay = 0.0f;
		}

		if (mMonstersInfo.mHp <= 0)
		{
			mMushMomDeadSound->Play(false);
			Player* player = SceneManager::GetPlayer();
			player->GetInfo()->mExp += mMonstersInfo.mExp;
			mMonsterState = eMonsterState::Dead;
		}
	}

	void MushMom::Dead()
	{
		mbMushMomHit = false;
		if (mDirection == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"MushMomLeftDead", false);
		}
		else
		{
			mAnimator->PlayAnimation(L"MushMomRightDead", false);

		}

		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (bCheck)
		{
			SceneManager::SetPortalCheck(true);
			Destroy(this);
		}
	}
	void MushMom::OnCollisionEnter(Collider* _other)
	{
		PlayerAttack* playerAtt = dynamic_cast<PlayerAttack*>(_other->GetOwner());
		if (playerAtt != nullptr && mMonsterState != eMonsterState::Dead)
		{
			std::set<GameObject*>* attList = playerAtt->GetAttackList();

			if (attList->find(this) == attList->end())
			{
				mMushMomHitSound->Play(false);

				mMonsterState = eMonsterState::Hit;

				attList->insert(this);
				mbMushMomHit = true;
			}
		}

		Raisingblow* raisingblow = dynamic_cast<Raisingblow*>(_other->GetOwner());
		if (raisingblow != nullptr && mMonsterState != eMonsterState::Dead)
		{
			std::set<GameObject*>* attList = raisingblow->GetAttackList();

			if (attList->find(this) == attList->end())
			{
				mMushMomHitSound->Play(false);
				RaisingblowHit* raisingBlowHit = new RaisingblowHit(this);
				object::ActiveSceneAddGameObject(enums::eLayerType::Effect, raisingBlowHit);
				attList->insert(this);


				mMonsterState = eMonsterState::Hit;

				mbMushMomHit = true;
			}
		}

		UpperCharge* upperCharge = dynamic_cast<UpperCharge*>(_other->GetOwner());
		if (upperCharge != nullptr && mMonsterState != eMonsterState::Dead)
		{
			std::set<GameObject*>* attList = upperCharge->GetAttackList();

			if (attList->find(this) == attList->end())
			{
				mMushMomHitSound->Play(false);

				mMonsterState = eMonsterState::Hit;

				attList->insert(this);
				mbMushMomHit = true;
			}
		}

		Rush* rush = dynamic_cast<Rush*>(_other->GetOwner());
		if (rush != nullptr && mMonsterState != eMonsterState::Dead)
		{
			std::set<GameObject*>* attList = rush->GetAttackList();

			if (attList->find(this) == attList->end())
			{
				mMushMomHitSound->Play(false);

				mMonsterState = eMonsterState::Hit;

				attList->insert(this);
				mbMushMomHit = true;
			}
		}

		ComboDeathFaultScreen* ComboDeathFault = dynamic_cast<ComboDeathFaultScreen*>(_other->GetOwner());
		if (ComboDeathFault != nullptr && mMonsterState != eMonsterState::Dead)
		{
			std::set<GameObject*>* attList = ComboDeathFault->GetAttackList();

			if (attList->find(this) == attList->end())
			{
				mMushMomHitSound->Play(false);

				mMonsterState = eMonsterState::Hit;
				attList->insert(this);
				mbMushMomHit = true;
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

	void MushMom::OnCollisionStay(Collider* _other)
	{
	}

	void MushMom::OnCollisionExit(Collider* _other)
	{
	}

}