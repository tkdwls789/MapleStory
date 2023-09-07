#include "exMasterCronus.h"
#include "exInput.h" 
#include "exTime.h"
#include "exObject.h"
#include "exResourceManager.h"
#include "exTransform.h"
#include "exAnimator.h"
#include "exCollider.h"
#include "exTexture.h"
#include "exPlayer.h"
#include "exSceneManager.h"
#include "exDamageManager.h"
#include "exMasterCronusAttack.h"
#include "exSound.h"

// PlayerSkill
#include "exPlayerAttack.h"
#include "exRaisingblow.h"
#include "exRaisingblowHit.h"
#include "exRush.h"
#include "exUpperCharge.h"
#include "exComboDeathFaultScreen.h"

namespace ex
{
	MasterCronus::MasterCronus()
		: mAttackDelay(0)
		, mMasterCronusHitSound(nullptr)
		, mMasterCronusDeadSound(nullptr)
	{
		mMonstersInfo.mMaxHp = 50000000;
		mMonstersInfo.mHp = 50000000;
		mMonstersInfo.mLevel = 150;
		mMonstersInfo.mDamage = 300;
		mSkillDamage = 250;
		mMonstersInfo.mExp = 0;
	}

	MasterCronus::~MasterCronus()
	{
	}

	void MasterCronus::Initialize()
	{
		// left
		mAnimator->CreateAnimationFolder(L"MasterCronusLeftIdle",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\MasterCronus\\Idle\\Left");

		mAnimator->CreateAnimationFolder(L"MasterCronusLeftMove",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\MasterCronus\\Move\\Left");

		mAnimator->CreateAnimationFolder(L"MasterCronusLeftHit",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\MasterCronus\\Hit\\Left");

		mAnimator->CreateAnimationFolder(L"MasterCronusLeftDead",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\MasterCronus\\Die\\Left");

		mAnimator->CreateAnimationFolder(L"MasterCronusLeftAttack",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\MasterCronus\\Attack\\Left"/*, math::Vector2(-100.0f, -100.0f), 0.15f*/);


		// Right
		mAnimator->CreateAnimationFolder(L"MasterCronusRightIdle",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\MasterCronus\\Idle\\Right");

		mAnimator->CreateAnimationFolder(L"MasterCronusRightMove",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\MasterCronus\\Move\\Right");

		mAnimator->CreateAnimationFolder(L"MasterCronusRightHit",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\MasterCronus\\Hit\\Right");

		mAnimator->CreateAnimationFolder(L"MasterCronusRightDead",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\MasterCronus\\Die\\Right");

		mAnimator->CreateAnimationFolder(L"MasterCronusRightAttack",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\MasterCronus\\Attack\\Right"/*, math::Vector2(100.0f, -100.0f), 0.15f*/);

		mMasterCronusHitSound = ResourceManager::Load<Sound>(L"MasterCronusHitSound", L"..\\Resources\\Maple\\Sound\\Monster\\MasterCronus\\MasterCronus_Die.wav");
		mMasterCronusDeadSound = ResourceManager::Load<Sound>(L"MasterCronusDeadSound", L"..\\Resources\\Maple\\Sound\\Monster\\MasterCronus\\MasterCronus_Hit.wav");

		mCollider->SetSize(math::Vector2(80.0f, 80.0f));
		//mCollider->SetOffset(math::Vector2(1.0f, 1.0f));
		mAnimator->SetAffectedCamera(true);
		mDirection = mTransform->GetMoveDir();
		mMoveTime = mMoveDelay;

		mAnimator->PlayAnimation(L"MasterCronusLeftIdle", true);
	}

	void MasterCronus::Update()
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

	void MasterCronus::Render(HDC _hdc)
	{

		GameObject::Render(_hdc);
	}

	void MasterCronus::Idle()
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
				mAnimator->PlayAnimation(L"MasterCronusLeftIdle", true);
			}
			else
			{
				mAnimator->PlayAnimation(L"MasterCronusRightIdle", true);
			}
		}

		math::Vector2 playerPos = SceneManager::GetPlayer()->GetPosition();
		float distanceX = fabs(playerPos.x - this->GetPositionX());
		float distanceY = fabs(playerPos.y - this->GetPositionY());

		if (distanceX < 300.0f && distanceY < 50.0f)
		{
			float playerPosX = SceneManager::GetPlayer()->GetPositionX();
			float MasterCronusPosX = mTransform->GetPositionX();

			if (playerPosX <= MasterCronusPosX)
			{
				mAnimator->PlayAnimation(L"MasterCronusLeftAttack", false);
				mDirection = enums::eMoveDir::Left;
			}
			else
			{
				mAnimator->PlayAnimation(L"MasterCronusRightAttack", false);
				mDirection = enums::eMoveDir::Right;
			}
			MasterCronusAttack* masterCronusAttack = new MasterCronusAttack(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, masterCronusAttack);
			mMonsterState = eMonsterState::Attack;
		}
	}

	void MasterCronus::Move()
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
				mAnimator->PlayAnimation(L"MasterCronusLeftMove", true);
				pos.x -= 50.0f * Time::GetDeltaTime();
			}
			else
			{
				mAnimator->PlayAnimation(L"MasterCronusRightMove", true);
				pos.x += 50.0f * Time::GetDeltaTime();
			}
		}

		math::Vector2 playerPos = SceneManager::GetPlayer()->GetPosition();
		float distanceX = fabs(playerPos.x - this->GetPositionX());
		float distanceY = fabs(playerPos.y - this->GetPositionY());
		if (distanceX < 300.0f && distanceY < 50.0f)
		{
			float playerPosX = SceneManager::GetPlayer()->GetPositionX();
			float MasterCronusPosX = mTransform->GetPositionX();
			if (playerPosX <= MasterCronusPosX)
			{
				mAnimator->PlayAnimation(L"MasterCronusLeftAttack", false);
				mDirection = enums::eMoveDir::Left;
			}
			else
			{
				mAnimator->PlayAnimation(L"MasterCronusRightAttack", false);
				mDirection = enums::eMoveDir::Right;
			}
			mTransform->SetMoveDir(mDirection);
			MasterCronusAttack* masterCronusAttack = new MasterCronusAttack(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, masterCronusAttack);
			mMonsterState = eMonsterState::Attack;
		}
		mTransform->SetMoveDir(mDirection);
		mTransform->SetPosition(pos);
	}

	void MasterCronus::Attack()
	{
		mAttackDelay += Time::GetDeltaTime();

		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (bCheck)
		{
			mMonsterState = eMonsterState::Move;
		}
	}

	void MasterCronus::Chase()
	{
	}

	void MasterCronus::Hit()
	{
		float playerPosX = SceneManager::GetPlayer()->GetPositionX();
		float MasterCronusPosX = mTransform->GetPositionX();
		if (playerPosX <= MasterCronusPosX)
		{
			mAnimator->PlayAnimation(L"MasterCronusLeftHit", false);
			mDirection = enums::eMoveDir::Left;
		}
		else
		{
			mAnimator->PlayAnimation(L"MasterCronusRightHit", false);
			mDirection = enums::eMoveDir::Right;
		}
		mHitDelay += Time::GetDeltaTime();



		if (mHitDelay >= 1.3f)
		{
			if (mDirection == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"MasterCronusLeftMove", true);
				mMonsterState = eMonsterState::Move;
			}
			else
			{
				mAnimator->PlayAnimation(L"MasterCronusRightMove", true);
				mMonsterState = eMonsterState::Move;
			}
			mHitDelay = 0.0f;
		}

		if (mMonstersInfo.mHp <= 0)
		{
			mMasterCronusDeadSound->Play(false);
			mMonsterState = eMonsterState::Dead;
		}
		mTransform->SetMoveDir(mDirection);
	}

	void MasterCronus::Dead()
	{
		if (mDirection == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"MasterCronusLeftDead", false);

		}
		else
		{
			mAnimator->PlayAnimation(L"MasterCronusRightDead", false);
		}

		bool bCheck = mAnimator->IsActiveAnimationComplete();

		if (bCheck)
		{
			Player* player = SceneManager::GetPlayer();
			player->GetInfo()->mExp += mMonstersInfo.mExp;
			Destroy(this);
		}


	}
	void MasterCronus::OnCollisionEnter(Collider* _other)
	{
		PlayerAttack* playerAtt = dynamic_cast<PlayerAttack*>(_other->GetOwner());
		if (playerAtt != nullptr && mMonsterState != eMonsterState::Dead)
		{
			std::set<GameObject*>* attList = playerAtt->GetAttackList();
			if (attList->find(this) == attList->end())
			{
				mMasterCronusHitSound->Play(false);
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
				mMasterCronusHitSound->Play(false);
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
				mMasterCronusHitSound->Play(false);
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
				mMasterCronusHitSound->Play(false);
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
				mMasterCronusHitSound->Play(false);
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

	void MasterCronus::OnCollisionStay(Collider* _other)
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

	void MasterCronus::OnCollisionExit(Collider* _other)
	{
	}
}