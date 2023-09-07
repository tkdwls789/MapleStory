#include "exGateKeeper.h"
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
#include "exGateKeeperAttack.h"
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
	GateKeeper::GateKeeper()
		: mAttackDelay(0)
		, mGateKeeperHitSound(nullptr)
		, mGateKeeperDeadSound(nullptr)
	{
		mMonstersInfo.mMaxHp = 30000000;
		mMonstersInfo.mHp = 30000000;
		mMonstersInfo.mLevel = 180;
		mMonstersInfo.mDamage = 1212;
		mSkillDamage = 257;
		mMonstersInfo.mExp = 35;
	}

	GateKeeper::~GateKeeper()
	{
	}

	void GateKeeper::Initialize()
	{
		// left
		mAnimator->CreateAnimationFolder(L"GateKeeperLeftIdle",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\GateKeeper\\Idle\\Left");

		mAnimator->CreateAnimationFolder(L"GateKeeperLeftMove",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\GateKeeper\\Move\\Left");

		mAnimator->CreateAnimationFolder(L"GateKeeperLeftHit",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\GateKeeper\\Hit\\Left");

		mAnimator->CreateAnimationFolder(L"GateKeeperLeftDead",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\GateKeeper\\Die\\Left");

		mAnimator->CreateAnimationFolder(L"GateKeeperLeftAttack",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\GateKeeper\\Attack\\Left", math::Vector2(-100.0f, -100.0f), 0.15f);


		// Right
		mAnimator->CreateAnimationFolder(L"GateKeeperRightIdle",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\GateKeeper\\Idle\\Right");

		mAnimator->CreateAnimationFolder(L"GateKeeperRightMove",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\GateKeeper\\Move\\Right");

		mAnimator->CreateAnimationFolder(L"GateKeeperRightHit",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\GateKeeper\\Hit\\Right");

		mAnimator->CreateAnimationFolder(L"GateKeeperRightDead",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\GateKeeper\\Die\\Right");

		mAnimator->CreateAnimationFolder(L"GateKeeperRightAttack",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\GateKeeper\\Attack\\Right", math::Vector2(100.0f, -100.0f), 0.15f);

		mGateKeeperHitSound = ResourceManager::Load<Sound>(L"GateKeeperHitSound", L"..\\Resources\\Maple\\Sound\\Monster\\GateKeeper\\GateKeeper_Die.wav");
		mGateKeeperDeadSound = ResourceManager::Load<Sound>(L"GateKeeperDeadSound", L"..\\Resources\\Maple\\Sound\\Monster\\GateKeeper\\GateKeeper_Hit.wav");

		mCollider->SetSize(math::Vector2(200.0f, 130.0f));
		//mCollider->SetOffset(math::Vector2(1.0f, 1.0f));
		mAnimator->SetAffectedCamera(true);
		mDirection = mTransform->GetMoveDir();
		mMoveTime = mMoveDelay;

		mAnimator->PlayAnimation(L"GateKeeperLeftIdle", true);
	}

	void GateKeeper::Update()
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

	void GateKeeper::Render(HDC _hdc)
	{

		GameObject::Render(_hdc);
	}

	void GateKeeper::Idle()
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
				mAnimator->PlayAnimation(L"GateKeeperLeftIdle", true);
			}
			else
			{
				mAnimator->PlayAnimation(L"GateKeeperRightIdle", true);
			}
		}

		math::Vector2 playerPos = SceneManager::GetPlayer()->GetPosition();
		float distanceX = fabs(playerPos.x - this->GetPositionX());
		float distanceY = fabs(playerPos.y - this->GetPositionY());

		if (distanceX < 300.0f && distanceY < 50.0f)
		{
			float playerPosX = SceneManager::GetPlayer()->GetPositionX();
			float GateKeeperPosX = mTransform->GetPositionX();

			if (playerPosX <= GateKeeperPosX)
			{
				mAnimator->PlayAnimation(L"GateKeeperLeftAttack", false);
				mDirection = enums::eMoveDir::Left;
			}
			else
			{
				mAnimator->PlayAnimation(L"GateKeeperRightAttack", false);
				mDirection = enums::eMoveDir::Right;
			}
			GateKeeperAttack* gateKeeperAttack = new GateKeeperAttack(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, gateKeeperAttack);
			mMonsterState = eMonsterState::Attack;
		}
	}

	void GateKeeper::Move()
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
				mAnimator->PlayAnimation(L"GateKeeperLeftMove", true);
				pos.x -= 50.0f * Time::GetDeltaTime();
			}
			else
			{
				mAnimator->PlayAnimation(L"GateKeeperRightMove", true);
				pos.x += 50.0f * Time::GetDeltaTime();
			}
		}

		math::Vector2 playerPos = SceneManager::GetPlayer()->GetPosition();
		float distanceX = fabs(playerPos.x - this->GetPositionX());
		float distanceY = fabs(playerPos.y - this->GetPositionY());
		if (distanceX < 300.0f && distanceY < 50.0f)
		{
			float playerPosX = SceneManager::GetPlayer()->GetPositionX();
			float GateKeeperPosX = mTransform->GetPositionX();
			if (playerPosX <= GateKeeperPosX)
			{
				mAnimator->PlayAnimation(L"GateKeeperLeftAttack", false);
				mDirection = enums::eMoveDir::Left;
			}
			else
			{
				mAnimator->PlayAnimation(L"GateKeeperRightAttack", false);
				mDirection = enums::eMoveDir::Right;
			}
			mTransform->SetMoveDir(mDirection);
			GateKeeperAttack* gateKeeperAttack = new GateKeeperAttack(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, gateKeeperAttack);
			mMonsterState = eMonsterState::Attack;
		}

		mTransform->SetPosition(pos);
	}

	void GateKeeper::Attack()
	{
		mAttackDelay += Time::GetDeltaTime();

		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (bCheck)
		{
			mMonsterState = eMonsterState::Move;
		}
	}

	void GateKeeper::Chase()
	{
	}

	void GateKeeper::Hit()
	{
		float playerPosX = SceneManager::GetPlayer()->GetPositionX();
		float GateKeeperPosX = mTransform->GetPositionX();
		if (playerPosX <= GateKeeperPosX)
		{
			mAnimator->PlayAnimation(L"GateKeeperLeftHit", false);
			mDirection = enums::eMoveDir::Left;
		}
		else
		{
			mAnimator->PlayAnimation(L"GateKeeperRightHit", false);
			mDirection = enums::eMoveDir::Right;
		}
		mHitDelay += Time::GetDeltaTime();



		if (mHitDelay >= 1.3f)
		{
			if (mDirection == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"GateKeeperLeftMove", true);
				mMonsterState = eMonsterState::Move;
			}
			else
			{
				mAnimator->PlayAnimation(L"GateKeeperRightMove", true);
				mMonsterState = eMonsterState::Move;
			}
			mHitDelay = 0.0f;

			if (mMonstersInfo.mHp <= 0)
			{
				mGateKeeperDeadSound->Play(false);
				mMonsterState = eMonsterState::Dead;
				Player* player = SceneManager::GetPlayer();
				player->GetInfo()->mExp += mMonstersInfo.mExp;
			}
		}
	}

	void GateKeeper::Dead()
	{
		if (mDirection == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"GateKeeperLeftDead", false);

		}
		else
		{
			mAnimator->PlayAnimation(L"GateKeeperRightDead", false);
		}

		bool bCheck = mAnimator->IsActiveAnimationComplete();

		if (bCheck)
		{
			Destroy(this);
		}


	}
	void GateKeeper::OnCollisionEnter(Collider* _other)
	{
		PlayerAttack* playerAtt = dynamic_cast<PlayerAttack*>(_other->GetOwner());
		if (playerAtt != nullptr && mMonsterState != eMonsterState::Dead)
		{
			std::set<GameObject*>* attList = playerAtt->GetAttackList();
			if (attList->find(this) == attList->end())
			{
				mGateKeeperHitSound->Play(false);
				attList->insert(this);

				mMonsterState = eMonsterState::Hit;


			}
		}

		Raisingblow* raisingblow = dynamic_cast<Raisingblow*>(_other->GetOwner());
		if (raisingblow != nullptr && mMonsterState != eMonsterState::Dead)
		{
			std::set<GameObject*>* attList = raisingblow->GetAttackList();

			if (attList->find(this) == attList->end())
			{
				mGateKeeperHitSound->Play(false);
				RaisingblowHit* raisingBlowHit = new RaisingblowHit(this);
				object::ActiveSceneAddGameObject(enums::eLayerType::Effect, raisingBlowHit);
				attList->insert(this);

				mMonsterState = eMonsterState::Hit;

			}
		}

		UpperCharge* upperCharge = dynamic_cast<UpperCharge*>(_other->GetOwner());
		if (upperCharge != nullptr && mMonsterState != eMonsterState::Dead)
		{
			std::set<GameObject*>* attList = upperCharge->GetAttackList();

			if (attList->find(this) == attList->end())
			{
				mGateKeeperHitSound->Play(false);
				attList->insert(this);

				mMonsterState = eMonsterState::Hit;


			}
		}

		Rush* rush = dynamic_cast<Rush*>(_other->GetOwner());
		if (rush != nullptr && mMonsterState != eMonsterState::Dead)
		{
			std::set<GameObject*>* attList = rush->GetAttackList();

			if (attList->find(this) == attList->end())
			{
				mGateKeeperHitSound->Play(false);
				attList->insert(this);

				mMonsterState = eMonsterState::Hit;


			}
		}

		ComboDeathFaultScreen* ComboDeathFault = dynamic_cast<ComboDeathFaultScreen*>(_other->GetOwner());
		if (ComboDeathFault != nullptr && mMonsterState != eMonsterState::Dead)
		{
			std::set<GameObject*>* attList = ComboDeathFault->GetAttackList();

			if (attList->find(this) == attList->end())
			{
				mGateKeeperHitSound->Play(false);
				attList->insert(this);

				mMonsterState = eMonsterState::Hit;

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

	void GateKeeper::OnCollisionStay(Collider* _other)
	{
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

	void GateKeeper::OnCollisionExit(Collider* _other)
	{
	}
}