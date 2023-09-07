#include "exPapulatus.h"
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
#include "exPapulatusHpBar.h"

// PlayerSkill
#include "exPlayerAttack.h"
#include "exRaisingblow.h"
#include "exRaisingblowHit.h"
#include "exRush.h"
#include "exUpperCharge.h"
#include "exComboDeathFaultScreen.h"


// MonsterSkill
#include "exPapulatusSkill1.h"
#include "exPapulatusSkill2.h"
#include "exPapulatusSkill3.h"
#include "exPapulatusSkill4.h"
#include "exPapulatusSkill5.h"
#include "exPapulatusSleep.h"

namespace ex
{
	Papulatus::Papulatus()
		: mAttackDelay(0.0f)
		, mbChaseOn(false)
		, mSkillDelay(1.5f)
		, mUsingSkillNumber(0)
		, mPapulatusHitSound(nullptr)
		, mPapulatusDeadSound(nullptr)
		, mSleepDelay(0.0f)
		, mSkill3Delay(0.0f)
		, mbSleepOn(false)
	{
		mMonstersInfo.mMaxHp = 720000000;
		mMonstersInfo.mHp = 720000000;
		mMonstersInfo.mLevel = 190;
		mMonstersInfo.mDamage = 750;
		mSkill1Damage = 4017;
		mSkill2Damage = 2412;
		mSkill3Damage = 878;
		mSkill4Damage = 0;
		mMonstersInfo.mExp = 200;
	}

	Papulatus::~Papulatus()
	{
	}

	void Papulatus::Initialize()
	{
		// Left
		mAnimator->CreateAnimationFolder(L"PapulatusLeftIdle",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Idle\\Left", math::Vector2(0.0f, -100.0f));

		mAnimator->CreateAnimationFolder(L"PapulatusLeftMove",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Move\\Left", math::Vector2(0.0f, -100.0f));

		mAnimator->CreateAnimationFolder(L"PapulatusLeftHit",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Hit\\Left", math::Vector2(0.0f, -100.0f));

		mAnimator->CreateAnimationFolder(L"PapulatusLeftDead",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Die\\Left", math::Vector2(0.0f, -100.0f));

		// Left Skill
		mAnimator->CreateAnimationFolder(L"PapulatusLeftSkill1",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Skill1\\Left", math::Vector2(0.0f, -160.0f), 0.077f);

		mAnimator->CreateAnimationFolder(L"PapulatusLeftSkill2",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Skill2\\Left", math::Vector2(-75.0f, -100.0f), 0.077f);

		mAnimator->CreateAnimationFolder(L"PapulatusLeftSkill3",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Skill3\\Left", math::Vector2(0.0f, -140.0f), 0.077f);

		mAnimator->CreateAnimationFolder(L"PapulatusLeftSkill4",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Skill4\\Left", math::Vector2(0.0f, -100.0f), 0.077f);

		mAnimator->CreateAnimationFolder(L"PapulatusLeftSkill5",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Skill5\\Left", math::Vector2(0.0f, -120.0f), 0.077f);

		mAnimator->CreateAnimationFolder(L"PapulatusLeftSleep",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Skill5\\Sleep\\Left", math::Vector2(0.0f, -50.0f), 0.077f);

		mAnimator->CreateAnimationFolder(L"PapulatusLeftWakeUp",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Skill5\\WakeUp\\Left", math::Vector2(0.0f, -120.0f), 0.077f);


		// Right
		mAnimator->CreateAnimationFolder(L"PapulatusRightIdle",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Idle\\Right", math::Vector2(0.0f, -100.0f));

		mAnimator->CreateAnimationFolder(L"PapulatusRightMove",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Move\\Right", math::Vector2(0.0f, -100.0f));

		mAnimator->CreateAnimationFolder(L"PapulatusRightHit",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Hit\\Right", math::Vector2(0.0f, -100.0f));

		mAnimator->CreateAnimationFolder(L"PapulatusRightDead",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Die\\Right", math::Vector2(0.0f, -100.0f));

		//Right Skill
		mAnimator->CreateAnimationFolder(L"PapulatusRightSkill1",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Skill1\\Right", math::Vector2(0.0f, -160.0f), 0.077f);

		mAnimator->CreateAnimationFolder(L"PapulatusRightSkill2",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Skill2\\Right", math::Vector2(75.0f, -100.0f), 0.077f);

		mAnimator->CreateAnimationFolder(L"PapulatusRightSkill3",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Skill3\\Right", math::Vector2(0.0f, -140.0f), 0.077f);

		mAnimator->CreateAnimationFolder(L"PapulatusRightSkill4",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Skill4\\Right", math::Vector2(0.0f, -100.0f), 0.077f);

		mAnimator->CreateAnimationFolder(L"PapulatusRightSkill5",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Skill5\\Right", math::Vector2(0.0f, -120.0f), 0.077f);

		mAnimator->CreateAnimationFolder(L"PapulatusRightSleep",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Skill5\\Sleep\\Right", math::Vector2(0.0f, -50.0f), 0.077f);

		mAnimator->CreateAnimationFolder(L"PapulatusRightWakeUp",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Skill5\\WakeUp\\Right", math::Vector2(0.0f, -120.0f), 0.077f);



		mPapulatusHitSound = ResourceManager::Load<Sound>(L"PapulatusHitSound", L"..\\Resources\\Maple\\Sound\\Monster\\Papulatus\\Papulatus_Die.wav");
		mPapulatusDeadSound = ResourceManager::Load<Sound>(L"PapulatusDeadSound", L"..\\Resources\\Maple\\Sound\\Monster\\Papulatus\\Papulatus_Hit.wav");

		mAnimator->PlayAnimation(L"PapulatusLeftMove", true);
		mTransform->SetMoveDir(enums::eMoveDir::Left);

		mAnimator->SetAffectedCamera(true);
		mCollider->SetSize(math::Vector2(250.0f, 120.0f));
		mCollider->SetOffset(math::Vector2(0.0f, 0.0f));
		mDirection = mTransform->GetMoveDir();
		mMoveTime = mMoveDelay;
	}


	void Papulatus::Update()
	{

		float halfHp = mMonstersInfo.mMaxHp / 4.3f;
		if (halfHp >= mMonstersInfo.mHp && false == mbSleepOn && mMonsterState != eMonsterState::Dead)
		{
			float playerPosX = SceneManager::GetPlayer()->GetPositionX();
			float PapulatusPosX = mTransform->GetPositionX();
			mbSleepOn = true;
			if (playerPosX <= PapulatusPosX)
			{
				mAnimator->PlayAnimation(L"PapulatusLeftSkill5", false);
				mDirection = enums::eMoveDir::Left;
			}
			else
			{
				mAnimator->PlayAnimation(L"PapulatusRightSkill5", false);
				mDirection = enums::eMoveDir::Right;
			}

			PapulatusSkill5* papulatusSkill5 = new PapulatusSkill5(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, papulatusSkill5);
			mMonsterState = eMonsterState::Skill5;
		}

		float playerPosX = SceneManager::GetPlayer()->GetPositionX();
		float papulatusPosX = mTransform->GetPositionX();

		if (mMonsterState != eMonsterState::Dead)
		{
			if (playerPosX < papulatusPosX)
			{
				mDirection = enums::eMoveDir::Left;
			}
			if (playerPosX > papulatusPosX)
			{
				mDirection = enums::eMoveDir::Right;
			}
		}
		if (mMonstersInfo.mHp <= 0)
		{
			mMonsterState = eMonsterState::Dead;
		}

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
		case ex::Monsters::eMonsterState::Sleep:
			Sleep();
			break;
		case ex::Monsters::eMonsterState::WakeUp:
			WakeUp();
			break;

		default:
			break;
		}


		GameObject::Update();
	}

	void Papulatus::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Papulatus::Idle()
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
			mAnimator->PlayAnimation(L"PapulatusLeftIdle", true);
		}
		else
		{
			mAnimator->PlayAnimation(L"PapulatusRightIdle", true);
		}


		mSkillDelay += Time::GetDeltaTime();
		if (mSkillDelay >= 1.0f)
		{
			math::Vector2 playerPos = SceneManager::GetPlayer()->GetPosition();
			float distanceX = fabs(playerPos.x - this->GetPositionX());
			float distanceY = fabs(playerPos.y - this->GetPositionY());

			mUsingSkillNumber = rand() % 4 + 1;

			if (distanceX < 500.0f && distanceY < 500.0f)
			{
				float playerPosX = SceneManager::GetPlayer()->GetPositionX();
				float PapulatusPosX = mTransform->GetPositionX();

				if (mUsingSkillNumber == 1)
				{
					if (playerPosX <= PapulatusPosX)
					{
						mAnimator->PlayAnimation(L"PapulatusLeftSkill1", false);
						mDirection = enums::eMoveDir::Left;
					}
					else
					{
						mAnimator->PlayAnimation(L"PapulatusRightSkill1", false);
						mDirection = enums::eMoveDir::Right;
					}
					PapulatusSkill1* papulatusSkill1 = new PapulatusSkill1(this);
					object::ActiveSceneAddGameObject(enums::eLayerType::Effect, papulatusSkill1);
					mMonsterState = eMonsterState::Skill1;
				}
				else if (mUsingSkillNumber == 2)
				{
					if (playerPosX <= PapulatusPosX)
					{
						mAnimator->PlayAnimation(L"PapulatusLeftSkill2", false);
						mDirection = enums::eMoveDir::Left;
					}
					else
					{
						mAnimator->PlayAnimation(L"PapulatusRightSkill2", false);
						mDirection = enums::eMoveDir::Right;
					}
					PapulatusSkill2* papulatusSkill2 = new PapulatusSkill2(this);
					object::ActiveSceneAddGameObject(enums::eLayerType::Effect, papulatusSkill2);
					mMonsterState = eMonsterState::Skill2;
				}
				else if (mUsingSkillNumber == 3)
				{
					if (playerPosX <= PapulatusPosX)
					{
						mAnimator->PlayAnimation(L"PapulatusLeftSkill3", false);
						mDirection = enums::eMoveDir::Left;
					}
					else
					{
						mAnimator->PlayAnimation(L"PapulatusRightSkill3", false);
						mDirection = enums::eMoveDir::Right;
					}
					PapulatusSkill3* papulatusSkill3 = new PapulatusSkill3(this);
					object::ActiveSceneAddGameObject(enums::eLayerType::Effect, papulatusSkill3);
					mMonsterState = eMonsterState::Skill3;
				}
				else if (mUsingSkillNumber == 4)
				{
					if (playerPosX <= PapulatusPosX)
					{
						mAnimator->PlayAnimation(L"PapulatusLeftSkill4", false);
						mDirection = enums::eMoveDir::Left;
					}
					else
					{
						mAnimator->PlayAnimation(L"PapulatusRightSkill4", false);
						mDirection = enums::eMoveDir::Right;
					}

					PapulatusSkill4* papulatusSkill4 = new PapulatusSkill4(this);
					object::ActiveSceneAddGameObject(enums::eLayerType::Effect, papulatusSkill4);
					mMonsterState = eMonsterState::Skill4;
				}
				mSkillDelay = 0.0f;
				mTransform->SetMoveDir(mDirection);
			}
		}


	}

	void Papulatus::Move()
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
				mAnimator->PlayAnimation(L"PapulatusLeftMove", true);
				mDirection = enums::eMoveDir::Left;
				pos.x -= 50.0f * Time::GetDeltaTime();
			}
			else
			{
				mAnimator->PlayAnimation(L"PapulatusRightMove", true);
				mDirection = enums::eMoveDir::Right;
				pos.x += 50.0f * Time::GetDeltaTime();
			}
		}

		mTransform->SetMoveDir(mDirection);
		mTransform->SetPosition(pos);
	}

	void Papulatus::Chase()
	{
		float playerPosX = SceneManager::GetPlayer()->GetPositionX();
		float papulatusPosX = mTransform->GetPositionX();
		math::Vector2 pos = mTransform->GetPosition();
		float diff = playerPosX - papulatusPosX;
		if (playerPosX <= papulatusPosX)
		{
			if (diff < 10.0f)
			{
				mAnimator->PlayAnimation(L"PapulatusLeftMove", true);
				mDirection = enums::eMoveDir::Left;
				pos.x -= 60.0f * Time::GetDeltaTime();
			}
		}
		else
		{
			if (diff > 10.0f)
			{
				mAnimator->PlayAnimation(L"PapulatusRightMove", true);
				mDirection = enums::eMoveDir::Right;
				pos.x += 60.0f * Time::GetDeltaTime();
			}
		}
		math::Vector2 playerPos = SceneManager::GetPlayer()->GetPosition();
		float distanceX = fabs(playerPos.x - this->GetPositionX());
		float distanceY = fabs(playerPos.y - this->GetPositionY());
		if (distanceX < 300.0f && distanceY < 200.0f)
		{
			mMonsterState = eMonsterState::Idle;
		}

		mTransform->SetPosition(pos);
		mTransform->SetMoveDir(mDirection);
	}

	void Papulatus::Hit()
	{
		mbChaseOn = true;
		float playerPosX = SceneManager::GetPlayer()->GetPositionX();
		float GateKeeperPosX = mTransform->GetPositionX();
		if (playerPosX <= GateKeeperPosX && mbChaseOn == false)
		{
			mAnimator->PlayAnimation(L"PapulatusLeftHit", false);
			mDirection = enums::eMoveDir::Left;
		}
		else
		{
			mAnimator->PlayAnimation(L"PapulatusRightHit", false);
			mDirection = enums::eMoveDir::Right;
		}
		mHitDelay += Time::GetDeltaTime();
		if (mHitDelay >= 1.3f && mbChaseOn == false)
		{
			if (mDirection == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PapulatusLeftMove", true);
				mDirection = enums::eMoveDir::Left;
			}
			else
			{
				mAnimator->PlayAnimation(L"PapulatusRightMove", true);
				mDirection = enums::eMoveDir::Right;
			}


			mHitDelay = 0.0f;
		}
		if (mbChaseOn)
		{
			mMonsterState = eMonsterState::Idle;
		}

		if (mMonstersInfo.mHp <= 0)
		{
			mPapulatusDeadSound->Play(false);
			Player* player = SceneManager::GetPlayer();
			player->GetInfo()->mExp += mMonstersInfo.mExp;
			mMonsterState = eMonsterState::Dead;
		}
		mTransform->SetMoveDir(mDirection);
	}

	void Papulatus::Dead()
	{
		mbChaseOn = false;
		if (mDirection == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"PapulatusLeftDead", false);
		}
		else
		{
			mAnimator->PlayAnimation(L"PapulatusRightDead", false);

		}

		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (bCheck)
		{
			SceneManager::SetPortalCheck(true);
			Destroy(this);
		}
	}

	void Papulatus::Skill1()
	{
		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (bCheck)
		{
			mMonsterState = eMonsterState::Idle;
		}
	}

	void Papulatus::Skill2()
	{
		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (bCheck)
		{
			mMonsterState = eMonsterState::Idle;
		}
	}

	void Papulatus::Skill3()
	{
		float playerPosX = SceneManager::GetPlayer()->GetPositionX();
		float PapulatusPosX = mTransform->GetPositionX();
		mSkill3Delay += Time::GetDeltaTime();
		if (mSkill3Delay <= 6.0f)
		{
			if (playerPosX <= PapulatusPosX)
			{
				mAnimator->PlayAnimation(L"PapulatusLeftSkill3", false);
				mDirection = enums::eMoveDir::Left;
			}
			else
			{
				mAnimator->PlayAnimation(L"PapulatusRightSkill3", false);
				mDirection = enums::eMoveDir::Right;
			}

		}

		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (bCheck)
		{
			if (playerPosX <= PapulatusPosX)
			{
				mAnimator->PlayAnimation(L"PapulatusLeftIdle", false);
				mDirection = enums::eMoveDir::Left;
			}
			else
			{
				mAnimator->PlayAnimation(L"PapulatusRightIdle", false);
				mDirection = enums::eMoveDir::Right;
			}
			mMonsterState = eMonsterState::Idle;
		}
		mSkill3Delay = 0.0f;


	}

	void Papulatus::Skill4()
	{
		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (bCheck)
		{
			mMonsterState = eMonsterState::Idle;
		}
	}

	void Papulatus::Skill5()
	{
		float playerPosX = SceneManager::GetPlayer()->GetPositionX();
		float PapulatusPosX = mTransform->GetPositionX();

		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (bCheck)
		{
			if (playerPosX <= PapulatusPosX)
			{
				mAnimator->PlayAnimation(L"PapulatusLeftSleep", false);
				mDirection = enums::eMoveDir::Left;
			}
			else
			{
				mAnimator->PlayAnimation(L"PapulatusRightSleep", false);
				mDirection = enums::eMoveDir::Right;
			}
			PapulatusSleep* papulatusSleep = new PapulatusSleep(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, papulatusSleep);
			mMonsterState = eMonsterState::Sleep;
		}
	}

	void Papulatus::Sleep()
	{
		float playerPosX = SceneManager::GetPlayer()->GetPositionX();
		float PapulatusPosX = mTransform->GetPositionX();

		mSleepDelay += Time::GetDeltaTime();
		if (mSleepDelay <= 4.0f)
		{
			if (playerPosX <= PapulatusPosX)
			{
				mAnimator->PlayAnimation(L"PapulatusLeftSleep", false);
				mDirection = enums::eMoveDir::Left;
			}
			else
			{
				mAnimator->PlayAnimation(L"PapulatusRightSleep", false);
				mDirection = enums::eMoveDir::Right;
			}
			mMonstersInfo.mHp += (int)(60000000 * Time::GetDeltaTime());
			if (mMonstersInfo.mHp >= mMonstersInfo.mMaxHp)
			{
				mMonstersInfo.mHp = mMonstersInfo.mMaxHp;
			}
		}
		else
		{
			bool bCheck = mAnimator->IsActiveAnimationComplete();
			if (bCheck)
			{
				if (playerPosX <= PapulatusPosX)
				{
					mAnimator->PlayAnimation(L"PapulatusLeftWakeUp", false);
					mDirection = enums::eMoveDir::Left;
				}
				else
				{
					mAnimator->PlayAnimation(L"PapulatusRightWakeUp", false);
					mDirection = enums::eMoveDir::Right;
				}
				mMonsterState = eMonsterState::WakeUp;
			}
			mSleepDelay = 0.0f;
		}
	}

	void Papulatus::WakeUp()
	{
		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (bCheck)
		{
			mMonsterState = eMonsterState::Idle;
		}
	}

	void Papulatus::OnCollisionEnter(Collider* _other)
	{
		if (mMonsterState != eMonsterState::Sleep && mMonsterState != eMonsterState::WakeUp && mMonsterState != eMonsterState::Skill5)
		{
			PlayerAttack* playerAtt = dynamic_cast<PlayerAttack*>(_other->GetOwner());
			if (playerAtt != nullptr && mMonsterState != eMonsterState::Dead)
			{
				std::set<GameObject*>* attList = playerAtt->GetAttackList();

				if (attList->find(this) == attList->end())
				{
					mPapulatusHitSound->Play(false);
					attList->insert(this);
					if (mMonsterState == eMonsterState::Idle ||
						mMonsterState == eMonsterState::Move)
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
					mPapulatusHitSound->Play(false);
					RaisingblowHit* raisingBlowHit = new RaisingblowHit(this);
					object::ActiveSceneAddGameObject(enums::eLayerType::Effect, raisingBlowHit);
					attList->insert(this);
					if (mMonsterState == eMonsterState::Idle ||
						mMonsterState == eMonsterState::Move)
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
					mPapulatusHitSound->Play(false);
					attList->insert(this);
					if (mMonsterState == eMonsterState::Idle ||
						mMonsterState == eMonsterState::Move)
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
					mPapulatusHitSound->Play(false);
					attList->insert(this);
					if (mMonsterState == eMonsterState::Idle ||
						mMonsterState == eMonsterState::Move)
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
					mPapulatusHitSound->Play(false);
					attList->insert(this);
					if (mMonsterState == eMonsterState::Idle ||
						mMonsterState == eMonsterState::Move)
					{
						mMonsterState = eMonsterState::Hit;
					}
				}
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

	void Papulatus::OnCollisionStay(Collider* _other)
	{
	}

	void Papulatus::OnCollisionExit(Collider* _other)
	{
	}

}