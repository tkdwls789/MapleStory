#include "exThanatos.h"
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
#include "exThanatosAttack.h"
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
	Thanatos::Thanatos()
		: mThanatosHitSound(nullptr)
		, mThanatosDeadSound(nullptr)
		, mAttackDelay(0.0f)
	{
		mMonstersInfo.mMaxHp = 27000000;
		mMonstersInfo.mHp = 27000000;
		mMonstersInfo.mLevel = 180;
		mMonstersInfo.mDamage = 1212;
		mSkillDamage = 280;
		mMonstersInfo.mExp = 35;
	}

	Thanatos::~Thanatos()
	{
	}

	void Thanatos::Initialize()
	{
		// left
		mAnimator->CreateAnimationFolder(L"ThanatosLeftIdle",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\Thanatos\\Idle\\Left");

		mAnimator->CreateAnimationFolder(L"ThanatosLeftMove",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\Thanatos\\Move\\Left");

		mAnimator->CreateAnimationFolder(L"ThanatosLeftHit",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\Thanatos\\Hit\\Left");

		mAnimator->CreateAnimationFolder(L"ThanatosLeftDead",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\Thanatos\\Die\\Left");

		mAnimator->CreateAnimationFolder(L"ThanatosLeftAttack",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\Thanatos\\Attack\\Left", math::Vector2(0.0f, 0.0f), 0.1f);


		// Right
		mAnimator->CreateAnimationFolder(L"ThanatosRightIdle",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\Thanatos\\Idle\\Right");

		mAnimator->CreateAnimationFolder(L"ThanatosRightMove",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\Thanatos\\Move\\Right");

		mAnimator->CreateAnimationFolder(L"ThanatosRightHit",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\Thanatos\\Hit\\Right");

		mAnimator->CreateAnimationFolder(L"ThanatosRightDead",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\Thanatos\\Die\\Right");

		mAnimator->CreateAnimationFolder(L"ThanatosRightAttack",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\Thanatos\\Attack\\Right", math::Vector2(0.0f, 0.0f), 0.1f);


		mThanatosHitSound = ResourceManager::Load<Sound>(L"ThanatosHitSound", L"..\\Resources\\Maple\\Sound\\Monster\\Thanatos\\Thanatos_Hit.wav");
		mThanatosDeadSound = ResourceManager::Load<Sound>(L"ThanatosDeadSound", L"..\\Resources\\Maple\\Sound\\Monster\\Thanatos\\Thanatos_Die.wav");


		mCollider->SetSize(math::Vector2(200.0f, 170.0f));
		//mCollider->SetOffset(math::Vector2(1.0f, 1.0f));
		mAnimator->SetAffectedCamera(true);
		mDirection = mTransform->GetMoveDir();
		mMoveTime = mMoveDelay;

		mAnimator->PlayAnimation(L"ThanatosLeftIdle", true);
	}

	void Thanatos::Update()
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

	void Thanatos::Render(HDC _hdc)
	{

		GameObject::Render(_hdc);
	}

	void Thanatos::Idle()
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
				mAnimator->PlayAnimation(L"ThanatosLeftIdle", true);
			}
			else
			{
				mAnimator->PlayAnimation(L"ThanatosRightIdle", true);
			}
		}

		math::Vector2 playerPos = SceneManager::GetPlayer()->GetPosition();
		float distanceX = fabs(playerPos.x - this->GetPositionX());
		float distanceY = fabs(playerPos.y - this->GetPositionY());

		if (distanceX < 300.0f && distanceY < 70.0f)
		{
			float playerPosX = SceneManager::GetPlayer()->GetPositionX();
			float ThanatosPosX = mTransform->GetPositionX();

			if (playerPosX <= ThanatosPosX)
			{
				mAnimator->PlayAnimation(L"ThanatosLeftAttack", false);
				mDirection = enums::eMoveDir::Left;
			}
			else
			{
				mAnimator->PlayAnimation(L"ThanatosRightAttack", false);
				mDirection = enums::eMoveDir::Right;
			}
			ThanatosAttack* thanatosAttack = new ThanatosAttack(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, thanatosAttack);
			mMonsterState = eMonsterState::Attack;
		}
	}

	void Thanatos::Move()
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
				mAnimator->PlayAnimation(L"ThanatosLeftMove", true);
				pos.x -= 50.0f * Time::GetDeltaTime();
			}
			else
			{
				mAnimator->PlayAnimation(L"ThanatosRightMove", true);
				pos.x += 50.0f * Time::GetDeltaTime();
			}
		}

		math::Vector2 playerPos = SceneManager::GetPlayer()->GetPosition();
		float distanceX = fabs(playerPos.x - this->GetPositionX());
		float distanceY = fabs(playerPos.y - this->GetPositionY());
		if (distanceX < 300.0f && distanceY < 70.0f)
		{
			float playerPosX = SceneManager::GetPlayer()->GetPositionX();
			float ThanatosPosX = mTransform->GetPositionX();
			if (playerPosX <= ThanatosPosX)
			{
				mAnimator->PlayAnimation(L"ThanatosLeftAttack", false);
				mDirection = enums::eMoveDir::Left;
			}
			else
			{
				mAnimator->PlayAnimation(L"ThanatosRightAttack", false);
				mDirection = enums::eMoveDir::Right;
			}
			mTransform->SetMoveDir(mDirection);
			ThanatosAttack* thanatosAttack = new ThanatosAttack(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, thanatosAttack);
			mMonsterState = eMonsterState::Attack;
		}

		mTransform->SetPosition(pos);
	}

	void Thanatos::Attack()
	{
		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (bCheck)
		{
			mMonsterState = eMonsterState::Move;
		}
	}

	void Thanatos::Chase()
	{
	}

	void Thanatos::Hit()
	{
		float playerPosX = SceneManager::GetPlayer()->GetPositionX();
		float ThanatosPosX = mTransform->GetPositionX();
		if (playerPosX <= ThanatosPosX)
		{
			mAnimator->PlayAnimation(L"ThanatosLeftHit", false);
			mDirection = enums::eMoveDir::Left;
		}
		else
		{
			mAnimator->PlayAnimation(L"ThanatosRightHit", false);
			mDirection = enums::eMoveDir::Right;
		}
		mHitDelay += Time::GetDeltaTime();



		if (mHitDelay >= 1.3f)
		{
			if (mDirection == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"ThanatosLeftMove", true);
				mMonsterState = eMonsterState::Move;
			}
			else
			{
				mAnimator->PlayAnimation(L"ThanatosRightMove", true);
				mMonsterState = eMonsterState::Move;
			}
			mHitDelay = 0.0f;
		}

		if (mMonstersInfo.mHp <= 0)
		{
			mThanatosDeadSound->Play(false);
			mMonsterState = eMonsterState::Dead;
			Player* player = SceneManager::GetPlayer();
			player->GetInfo()->mExp += mMonstersInfo.mExp;
		}
	}

	void Thanatos::Dead()
	{
		if (mDirection == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"ThanatosLeftDead", false);

		}
		else
		{
			mAnimator->PlayAnimation(L"ThanatosRightDead", false);
		}

		bool bCheck = mAnimator->IsActiveAnimationComplete();

		if (bCheck)
		{
			Player* player = SceneManager::GetPlayer();
			player->GetInfo()->mExp += mMonstersInfo.mExp;
			Destroy(this);
		}


	}
	void Thanatos::OnCollisionEnter(Collider* _other)
	{
		PlayerAttack* playerAtt = dynamic_cast<PlayerAttack*>(_other->GetOwner());
		if (playerAtt != nullptr && mMonsterState != eMonsterState::Dead)
		{
			std::set<GameObject*>* attList = playerAtt->GetAttackList();

			if (attList->find(this) == attList->end())
			{
				mThanatosHitSound->Play(false);
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
				mThanatosHitSound->Play(false);
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
				mThanatosHitSound->Play(false);
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
				mThanatosHitSound->Play(false);
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
				mThanatosHitSound->Play(false);
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

	void Thanatos::OnCollisionStay(Collider* _other)
	{
	}

	void Thanatos::OnCollisionExit(Collider* _other)
	{
	}
}