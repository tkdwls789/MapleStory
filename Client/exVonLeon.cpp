#include "exVonLeon.h"
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
#include "exFloor.h"
#include "exSound.h"
//#include "exVonLeonHpBar.h"

// PlayerSkill
#include "exPlayerAttack.h"
#include "exRaisingblow.h"
#include "exRaisingblowHit.h"
#include "exRush.h"
#include "exUpperCharge.h"
#include "exComboDeathFaultScreen.h"


// MonsterSkill
#include "exVonLeonSkill1.h"
#include "exVonLeonSkill2.h"
#include "exVonLeonSkill3.h"
#include "exVonLeonSkill4.h"
#include "exVonLeonSkill5.h"
#include "exVonLeonTeleport.h"

namespace ex
{
	VonLeon::VonLeon()
		: mAttackDelay(0.0f)
		, mbChaseOn(true)
		, mSkillDelay(1.5f)
		, mUsingSkillNumber(0)
		, mVonLeonHitSound(nullptr)
		, mVonLeonDeadSound(nullptr)
		, mSleepDelay(0.0f)
		, mSkill3Delay(0.0f)
	{
		mMonstersInfo.mMaxHp = 1000000000;
		mMonstersInfo.mHp = 1000000000;
		mMonstersInfo.mLevel = 200;
		mMonstersInfo.mDamage = 750;
		mSkill1Damage = 4312;
		mSkill2Damage = 3617;
		mSkill3Damage = 1878;
		mSkill4Damage = 0;
		mMonstersInfo.mExp = 300;

		// Left
		mAnimator->CreateAnimationFolder(L"VonLeonLeftIdle",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\VonLeon\\Idle\\Left", math::Vector2(0.0f, 10.0f));

		mAnimator->CreateAnimationFolder(L"VonLeonLeftMove",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\VonLeon\\Move\\Left", math::Vector2(0.0f, 0.0f));

		mAnimator->CreateAnimationFolder(L"VonLeonLeftHit",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\VonLeon\\Hit\\Left", math::Vector2(0.0f, 0.0f));

		mAnimator->CreateAnimationFolder(L"VonLeonLeftDead",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\VonLeon\\Die\\Left", math::Vector2(0.0f, 0.0f));

		// Left Skill
		mAnimator->CreateAnimationFolder(L"VonLeonLeftSkill1",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\VonLeon\\Skill1\\Left", math::Vector2(0.0f, 0.0f), 0.1f);

		mAnimator->CreateAnimationFolder(L"VonLeonLeftSkill2",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\VonLeon\\Skill2\\Left", math::Vector2(5.0f, 0.0f), 0.1f);

		mAnimator->CreateAnimationFolder(L"VonLeonLeftSkill3",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\VonLeon\\Skill3\\Left", math::Vector2(0.0f, 42.0f), 0.1f);

		mAnimator->CreateAnimationFolder(L"VonLeonLeftSkill4",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\VonLeon\\Skill4\\Left", math::Vector2(0.0f, 40.0f), 0.1f);

		mAnimator->CreateAnimationFolder(L"VonLeonLeftSkill5",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\VonLeon\\Skill5\\Left", math::Vector2(-50.0f, 30.0f), 0.1f);

		mAnimator->CreateAnimationFolder(L"VonLeonLeftTeleport",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\VonLeon\\Teleport\\Left", math::Vector2(0.0f, -30.0f), 0.1f);

		mAnimator->CreateAnimationFolder(L"VonLeonLeftTeleportAfter",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\VonLeon\\TeleportAfter\\Left", math::Vector2(0.0f, 0.0f), 0.1f);

		// Right
		mAnimator->CreateAnimationFolder(L"VonLeonRightIdle",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\VonLeon\\Idle\\Right", math::Vector2(0.0f, 10.0f));

		mAnimator->CreateAnimationFolder(L"VonLeonRightMove",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\VonLeon\\Move\\Right", math::Vector2(0.0f, 0.0f));

		mAnimator->CreateAnimationFolder(L"VonLeonRightHit",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\VonLeon\\Hit\\Right", math::Vector2(0.0f, 0.0f));

		mAnimator->CreateAnimationFolder(L"VonLeonRightDead",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\VonLeon\\Die\\Right", math::Vector2(0.0f, 0.0f));

		//Right Skill
		mAnimator->CreateAnimationFolder(L"VonLeonRightSkill1",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\VonLeon\\Skill1\\Right", math::Vector2(0.0f, 0.0f), 0.1f);

		mAnimator->CreateAnimationFolder(L"VonLeonRightSkill2",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\VonLeon\\Skill2\\Right", math::Vector2(5.0f, 0.0f), 0.1f);

		mAnimator->CreateAnimationFolder(L"VonLeonRightSkill3",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\VonLeon\\Skill3\\Right", math::Vector2(0.0f, 42.0f), 0.1f);

		mAnimator->CreateAnimationFolder(L"VonLeonRightSkill4",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\VonLeon\\Skill4\\Right", math::Vector2(0.0f, 40.0f), 0.1f);

		mAnimator->CreateAnimationFolder(L"VonLeonRightSkill5",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\VonLeon\\Skill5\\Right", math::Vector2(50.0f, 30.0f), 0.1f);

		mAnimator->CreateAnimationFolder(L"VonLeonRightTeleport",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\VonLeon\\Teleport\\Right", math::Vector2(0.0f, -30.0f), 0.1f);

		mAnimator->CreateAnimationFolder(L"VonLeonRightTeleportAfter",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\VonLeon\\TeleportAfter\\Right", math::Vector2(0.0f, 0.0f), 0.1f);

		mVonLeonHitSound = ResourceManager::Load<Sound>(L"VonLeonHitSound", L"..\\Resources\\Maple\\Sound\\Monster\\VonLeon\\VonLeon_Hit.wav");
		mVonLeonDeadSound = ResourceManager::Load<Sound>(L"VonLeonDeadSound", L"..\\Resources\\Maple\\Sound\\Monster\\VonLeon\\VonLeon_Die.wav");

		mTransform->SetPosition(math::Vector2(1000.0f, 1000.0f));
	}

	VonLeon::~VonLeon()
	{
	}

	void VonLeon::Initialize()
	{
		mAnimator->PlayAnimation(L"VonLeonLeftMove", true);
		mTransform->SetMoveDir(enums::eMoveDir::Left);
		mTransform->SetPosition(math::Vector2(995.0f, 360.0f));

		mAnimator->SetAffectedCamera(true);
		mCollider->SetSize(math::Vector2(400.0f, 520.0f));
		mDirection = mTransform->GetMoveDir();
		mMoveTime = mMoveDelay;
	}



	void VonLeon::Update()
	{

		float playerPosX = SceneManager::GetPlayer()->GetPositionX();
		float vonLeonPosX = mTransform->GetPositionX();

		if (mMonsterState != eMonsterState::Dead)
		{
			if (playerPosX < vonLeonPosX)
			{
				mDirection = enums::eMoveDir::Left;
			}
			if (playerPosX > vonLeonPosX)
			{
				mDirection = enums::eMoveDir::Right;
			}
		}
		


		switch (mMonsterState)
		{
		case ex::Monsters::eMonsterState::Idle:
			Idle();
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
		case ex::Monsters::eMonsterState::Skill1:
			Skill1();
			break;
		case ex::Monsters::eMonsterState::Skill2:
			Skill2();
			break;
		case ex::Monsters::eMonsterState::Skill3:
			Skill3();
			break;
		case ex::Monsters::eMonsterState::Skill4:
			Skill4();
			break;
		case ex::Monsters::eMonsterState::Skill5:
			Skill5();
			break;
		case ex::Monsters::eMonsterState::Teleport:
			Teleport();
			break;

		default:
			break;
		}


		GameObject::Update();
	}

	void VonLeon::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void VonLeon::Idle()
	{
		mIdleDelay += Time::GetDeltaTime();

		math::Vector2 pos = mTransform->GetPosition();
		if (mIdleDelay >= 2.3f)
		{
			if (mbChaseOn)
			{
				mMonsterState = eMonsterState::Chase;
			}
			mIdleDelay = 0.0f;
		}

		if (mDirection == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"VonLeonLeftIdle", true);
		}
		else
		{
			mAnimator->PlayAnimation(L"VonLeonRightIdle", true);
		}


		mSkillDelay += Time::GetDeltaTime();
		if (mSkillDelay >= 1.2f)
		{
			math::Vector2 playerPos = SceneManager::GetPlayer()->GetPosition();
			float distanceX = fabs(playerPos.x - this->GetPositionX());
			float distanceY = fabs(playerPos.y - this->GetPositionY());

			mUsingSkillNumber = rand() % 6 + 1;

			if (distanceX < 500.0f && distanceY < 500.0f)
			{
				float playerPosX = SceneManager::GetPlayer()->GetPositionX();
				float VonLeonPosX = mTransform->GetPositionX();

				if (mUsingSkillNumber == 1)
				{
					if (playerPosX <= VonLeonPosX)
					{
						mAnimator->PlayAnimation(L"VonLeonLeftSkill1", false);
						mDirection = enums::eMoveDir::Left;
					}
					else
					{
						mAnimator->PlayAnimation(L"VonLeonRightSkill1", false);
						mDirection = enums::eMoveDir::Right;
					}
					VonLeonSkill1* vonLeonSkill1 = new VonLeonSkill1(this);
					object::ActiveSceneAddGameObject(enums::eLayerType::Effect, vonLeonSkill1);
					mMonsterState = eMonsterState::Skill1;
				}
				else if (mUsingSkillNumber == 2)
				{
					if (playerPosX <= VonLeonPosX)
					{
						mAnimator->PlayAnimation(L"VonLeonLeftSkill2", false);
						mDirection = enums::eMoveDir::Left;
					}
					else
					{
						mAnimator->PlayAnimation(L"VonLeonRightSkill2", false);
						mDirection = enums::eMoveDir::Right;
					}
					VonLeonSkill2* vonLeonSkill2 = new VonLeonSkill2(this);
					object::ActiveSceneAddGameObject(enums::eLayerType::Effect, vonLeonSkill2);
					mMonsterState = eMonsterState::Skill2;
				}
				else if (mUsingSkillNumber == 3)
				{
					if (playerPosX <= VonLeonPosX)
					{
						mAnimator->PlayAnimation(L"VonLeonLeftSkill3", false);
						mDirection = enums::eMoveDir::Left;
					}
					else
					{
						mAnimator->PlayAnimation(L"VonLeonRightSkill3", false);
						mDirection = enums::eMoveDir::Right;
					}
					VonLeonSkill3* vonLeonSkill3 = new VonLeonSkill3(this);
					object::ActiveSceneAddGameObject(enums::eLayerType::Effect, vonLeonSkill3);
					mMonsterState = eMonsterState::Skill3;
				}
				else if (mUsingSkillNumber == 4)
				{
					if (playerPosX <= VonLeonPosX)
					{
						mAnimator->PlayAnimation(L"VonLeonLeftSkill4", false);
						mDirection = enums::eMoveDir::Left;
					}
					else
					{
						mAnimator->PlayAnimation(L"VonLeonRightSkill4", false);
						mDirection = enums::eMoveDir::Right;
					}

					VonLeonSkill4* vonLeonSkill4 = new VonLeonSkill4(this);
					object::ActiveSceneAddGameObject(enums::eLayerType::Effect, vonLeonSkill4);
					mMonsterState = eMonsterState::Skill4;
				}
				else if (mUsingSkillNumber == 5)
				{
					if (playerPosX <= VonLeonPosX)
					{
						mAnimator->PlayAnimation(L"VonLeonLeftSkill5", false);
						mDirection = enums::eMoveDir::Left;
					}
					else
					{
						mAnimator->PlayAnimation(L"VonLeonRightSkill5", false);
						mDirection = enums::eMoveDir::Right;
					}

					VonLeonSkill5* vonLeonSkill5 = new VonLeonSkill5(this);
					object::ActiveSceneAddGameObject(enums::eLayerType::Effect, vonLeonSkill5);
					mMonsterState = eMonsterState::Skill5;
				}
				else
				{
					if (playerPosX <= VonLeonPosX)
					{
						mAnimator->PlayAnimation(L"VonLeonLeftTeleport", false);
						mDirection = enums::eMoveDir::Left;
					}
					else
					{
						mAnimator->PlayAnimation(L"VonLeonRightTeleport", false);
						mDirection = enums::eMoveDir::Right;
					}

					VonLeonTeleport* vonLeonTeleport = new VonLeonTeleport(this);
					object::ActiveSceneAddGameObject(enums::eLayerType::Effect, vonLeonTeleport);
					mMonsterState = eMonsterState::Teleport;
				}
				mSkillDelay = 0.0f;
				mTransform->SetMoveDir(mDirection);
			}
		}
	}


	void VonLeon::Chase()
	{
		float playerPosX = SceneManager::GetPlayer()->GetPositionX();
		float VonLeonPosX = mTransform->GetPositionX();
		math::Vector2 pos = mTransform->GetPosition();
		float diff = playerPosX - VonLeonPosX;
		if (playerPosX <= VonLeonPosX)
		{
			mAnimator->PlayAnimation(L"VonLeonLeftMove", true);
			mDirection = enums::eMoveDir::Left;
			if (diff < 10.0f)
			{
				pos.x -= 60.0f * Time::GetDeltaTime();
			}
		}
		else
		{
			mAnimator->PlayAnimation(L"VonLeonRightMove", true);
			mDirection = enums::eMoveDir::Right;
			if (diff > 10.0f)
			{
				pos.x += 60.0f * Time::GetDeltaTime();
			}
		}
		math::Vector2 playerPos = SceneManager::GetPlayer()->GetPosition();
		float distanceX = fabs(playerPos.x - this->GetPositionX());
		float distanceY = fabs(playerPos.y - this->GetPositionY());
		if (distanceX < 300.0f && distanceY < 500.0f)
		{
			mMonsterState = eMonsterState::Idle;
		}

		mTransform->SetPosition(pos);
		mTransform->SetMoveDir(mDirection);
	}

	void VonLeon::Hit()
	{
		float playerPosX = SceneManager::GetPlayer()->GetPositionX();
		float monsterX = mTransform->GetPositionX();
		if (playerPosX <= monsterX)
		{
			mAnimator->PlayAnimation(L"VonLeonLeftHit", false);
			mDirection = enums::eMoveDir::Left;
		}
		else
		{
			mAnimator->PlayAnimation(L"VonLeonRightHit", false);
			mDirection = enums::eMoveDir::Right;
		}
		mHitDelay += Time::GetDeltaTime();
		if (mHitDelay >= 1.3f && mbChaseOn == false)
		{
			if (mDirection == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"VonLeonLeftMove", true);
				mDirection = enums::eMoveDir::Left;
			}
			else
			{
				mAnimator->PlayAnimation(L"VonLeonRightMove", true);
				mDirection = enums::eMoveDir::Right;
			}
			if (mbChaseOn)
			{
				mMonsterState = eMonsterState::Chase;
			}
			else
			{
				mMonsterState = eMonsterState::Move;
			}

			mHitDelay = 0.0f;
		}
		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (bCheck)
		{
			mMonsterState = eMonsterState::Idle;
		}

		mTransform->SetMoveDir(mDirection);

		if (mMonstersInfo.mHp <= 0)
		{
			mVonLeonDeadSound->Play(false);
			mMonsterState = eMonsterState::Dead;
			Player* player = SceneManager::GetPlayer();
			player->GetInfo()->mExp += mMonstersInfo.mExp;
		}
	}

	void VonLeon::Dead()
	{
		mbChaseOn = false;
		SceneManager::SetPortalCheck(true);
		if (mDirection == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"VonLeonLeftDead", false);
		}
		else
		{
			mAnimator->PlayAnimation(L"VonLeonRightDead", false);

		}

		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (bCheck)
		{
			Player* player = SceneManager::GetPlayer();
			player->GetInfo()->mExp += mMonstersInfo.mExp;
			Destroy(this);
		}
	}

	void VonLeon::Skill1()
	{
		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (bCheck)
		{
			mMonsterState = eMonsterState::Idle;
		}
	}

	void VonLeon::Skill2()
	{
		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (bCheck)
		{
			mMonsterState = eMonsterState::Idle;
		}
	}

	void VonLeon::Skill3()
	{
		float playerPosX = SceneManager::GetPlayer()->GetPositionX();
		float VonLeonPosX = mTransform->GetPositionX();
		mSkill3Delay += Time::GetDeltaTime();
		if (mSkill3Delay <= 6.0f)
		{
			if (playerPosX <= VonLeonPosX)
			{
				mAnimator->PlayAnimation(L"VonLeonLeftSkill3", false);
				mDirection = enums::eMoveDir::Left;
			}
			else
			{
				mAnimator->PlayAnimation(L"VonLeonRightSkill3", false);
				mDirection = enums::eMoveDir::Right;
			}

		}

		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (bCheck)
		{
			if (playerPosX <= VonLeonPosX)
			{
				mAnimator->PlayAnimation(L"VonLeonLeftIdle", false);
				mDirection = enums::eMoveDir::Left;
			}
			else
			{
				mAnimator->PlayAnimation(L"VonLeonRightIdle", false);
				mDirection = enums::eMoveDir::Right;
			}
			mMonsterState = eMonsterState::Idle;
		}
		mSkill3Delay = 0.0f;


	}

	void VonLeon::Skill4()
	{
		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (bCheck)
		{
			mMonsterState = eMonsterState::Idle;
		}
	}

	void VonLeon::Skill5()
	{
		float playerPosX = SceneManager::GetPlayer()->GetPositionX();
		float VonLeonPosX = mTransform->GetPositionX();

		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (bCheck)
		{
			mMonsterState = eMonsterState::Idle;
		}

	}

	void VonLeon::Teleport()
	{
		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (bCheck)
		{
			mMonsterState = eMonsterState::Idle;
		}
	}



	void VonLeon::OnCollisionEnter(Collider* _other)
	{
		if (mMonsterState != eMonsterState::Sleep || mMonsterState != eMonsterState::WakeUp || mMonsterState != eMonsterState::Dead)
		{
			PlayerAttack* playerAtt = dynamic_cast<PlayerAttack*>(_other->GetOwner());
			if (playerAtt != nullptr && mMonsterState != eMonsterState::Dead)
			{
				std::set<GameObject*>* attList = playerAtt->GetAttackList();

				if (attList->find(this) == attList->end())
				{
					mVonLeonHitSound->Play(false);
					attList->insert(this);
					if (mMonsterState == eMonsterState::Idle ||
						mMonsterState == eMonsterState::Chase)
					{
						mMonsterState = eMonsterState::Hit;
					}
				}
			}

			Raisingblow* raisingblow = dynamic_cast<Raisingblow*>(_other->GetOwner());
			if (raisingblow != nullptr && mMonsterState != eMonsterState::Dead)
			{
				std::set<GameObject*>* attList = raisingblow->GetAttackList();

				if (attList->find(this) == attList->end())
				{
					mVonLeonHitSound->Play(false);
					RaisingblowHit* raisingBlowHit = new RaisingblowHit(this);
					object::ActiveSceneAddGameObject(enums::eLayerType::Effect, raisingBlowHit);
					attList->insert(this);
					if (mMonsterState == eMonsterState::Idle ||
						mMonsterState == eMonsterState::Chase)
					{
						mMonsterState = eMonsterState::Hit;
					}
				}
			}

			UpperCharge* upperCharge = dynamic_cast<UpperCharge*>(_other->GetOwner());
			if (upperCharge != nullptr && mMonsterState != eMonsterState::Dead)
			{
				std::set<GameObject*>* attList = upperCharge->GetAttackList();

				if (attList->find(this) == attList->end())
				{
					mVonLeonHitSound->Play(false);
					attList->insert(this);
					if (mMonsterState == eMonsterState::Idle ||
						mMonsterState == eMonsterState::Chase)
					{
						mMonsterState = eMonsterState::Hit;
					}

				}
			}

			Rush* rush = dynamic_cast<Rush*>(_other->GetOwner());
			if (rush != nullptr && mMonsterState != eMonsterState::Dead)
			{
				std::set<GameObject*>* attList = rush->GetAttackList();

				if (attList->find(this) == attList->end())
				{
					mVonLeonHitSound->Play(false);
					attList->insert(this);
					if (mMonsterState == eMonsterState::Idle ||
						mMonsterState == eMonsterState::Chase)
					{
						mMonsterState = eMonsterState::Hit;
					}

				}
			}

			ComboDeathFaultScreen* ComboDeathFault = dynamic_cast<ComboDeathFaultScreen*>(_other->GetOwner());
			if (ComboDeathFault != nullptr && mMonsterState != eMonsterState::Dead)
			{
				std::set<GameObject*>* attList = ComboDeathFault->GetAttackList();

				if (attList->find(this) == attList->end())
				{
					mVonLeonHitSound->Play(false);
					attList->insert(this);
					if (mMonsterState == eMonsterState::Idle ||
						mMonsterState == eMonsterState::Chase)
					{
						mMonsterState = eMonsterState::Hit;
					}
				}
			}
		}

		//if (mMonsterState != eMonsterState::Dead)
		//{
		//	Player* player = dynamic_cast<Player*>(_other->GetOwner());
		//	if (player != nullptr && player->IsInvincible() == false)
		//	{
		//		DamageManager* damage = new DamageManager();
		//		object::ActiveSceneAddGameObject(enums::eLayerType::UI, damage);
		//		damage->SetPosition(math::Vector2(player->GetPositionX(), player->GetPositionY() - 28.0f));
		//		damage->PlayMonsterDamageAnimation(this->GetMonstersInfo().mDamage);

		//	}
		//}
	}

	void VonLeon::OnCollisionStay(Collider* _other)
	{
	}

	void VonLeon::OnCollisionExit(Collider* _other)
	{
	}

}