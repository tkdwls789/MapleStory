//#include "exPilotPapulatus.h"
//#include "exTransform.h"
//#include "exInput.h" 
//#include "exTime.h"
//#include "exResourceManager.h"
//#include "exAnimator.h"
//#include "exTexture.h"
//#include "exCollider.h"
//#include "exRigidbody.h"
//#include "exSceneManager.h"
//#include "exPlayer.h"
//#include "exObject.h"
//#include "exDamageManager.h"
//#include "exFloor.h"
//#include "exSound.h"
//
//// PlayerSkill
//#include "exPlayerAttack.h"
//#include "exRaisingblow.h"
//#include "exRaisingblowHit.h"
//#include "exRush.h"
//#include "exUpperCharge.h"
//#include "exComboDeathFaultScreen.h"
//
//
//// MonsterSkill
////#include "exPilotPapulatusSkill1.h"
////#include "exPilotPapulatusSkill2.h"
////#include "exPilotPapulatusSkill3.h"
////#include "exPilotPapulatusSkill4.h"
////#include "exPilotPapulatusSkill5.h"
//
//
//namespace ex
//{
//	PilotPapulatus::PilotPapulatus()
//		: mAttackDelay(0.0f)
//		, mbChaseOn(false)
//		, mSkillDelay(1.5f)
//		, mUsingSkillNumber(0)
//		, mPilotPapulatusHitSound(nullptr)
//		, mPilotPapulatusDeadSound(nullptr)
//		, mSleepDelay(0.0f)
//		, mSkill3Delay(0.0f)
//		, mbSleepOn(false)
//	{
//		mMonstersInfo.mMaxHp = 700000000;
//		mMonstersInfo.mHp = 700000000;
//		mMonstersInfo.mLevel = 190;
//		mMonstersInfo.mDamage = 750;
//		mSkill1Damage = 411;
//		mSkill2Damage = 403;
//		mSkill3Damage = 280;
//		mSkill4Damage = 0;
//	}
//
//	PilotPapulatus::~PilotPapulatus()
//	{
//	}
//
//	void PilotPapulatus::Initialize()
//	{
//		// Left
//		mAnimator->CreateAnimationFolder(L"PilotPapulatusLeftIdle",
//			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\PilotPapulatus\\Idle\\Left", math::Vector2(0.0f, -100.0f));
//
//		mAnimator->CreateAnimationFolder(L"PilotPapulatusLeftMove",
//			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\PilotPapulatus\\Move\\Left", math::Vector2(0.0f, -100.0f));
//
//		mAnimator->CreateAnimationFolder(L"PilotPapulatusLeftHit",
//			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\PilotPapulatus\\Hit\\Left", math::Vector2(0.0f, -100.0f));
//
//		mAnimator->CreateAnimationFolder(L"PilotPapulatusLeftDead",
//			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\PilotPapulatus\\Die\\Left", math::Vector2(0.0f, -100.0f));
//
//		// Left Skill
//		mAnimator->CreateAnimationFolder(L"PilotPapulatusLeftSkill1",
//			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\PilotPapulatus\\Skill1\\Left", math::Vector2(0.0f, -160.0f), 0.077f);
//
//		mAnimator->CreateAnimationFolder(L"PilotPapulatusLeftSkill2",
//			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\PilotPapulatus\\Skill2\\Left", math::Vector2(-75.0f, -100.0f), 0.077f);
//
//		mAnimator->CreateAnimationFolder(L"PilotPapulatusLeftSkill3",
//			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\PilotPapulatus\\Skill3\\Left", math::Vector2(0.0f, -140.0f), 0.077f);
//
//		mAnimator->CreateAnimationFolder(L"PilotPapulatusLeftSkill4",
//			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\PilotPapulatus\\Skill4\\Left", math::Vector2(0.0f, -100.0f), 0.077f);
//
//		mAnimator->CreateAnimationFolder(L"PilotPapulatusLeftSkill5",
//			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\PilotPapulatus\\Skill5\\Left", math::Vector2(0.0f, -120.0f), 0.077f);
//
//		mAnimator->CreateAnimationFolder(L"PilotPapulatusLeftSleep",
//			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\PilotPapulatus\\Skill5\\Sleep\\Left", math::Vector2(0.0f, -50.0f), 0.077f);
//
//		mAnimator->CreateAnimationFolder(L"PilotPapulatusLeftWakeUp",
//			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\PilotPapulatus\\Skill5\\WakeUp\\Left", math::Vector2(0.0f, -120.0f), 0.077f);
//
//
//		// Right
//		mAnimator->CreateAnimationFolder(L"PilotPapulatusRightIdle",
//			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\PilotPapulatus\\Idle\\Right", math::Vector2(0.0f, -100.0f));
//
//		mAnimator->CreateAnimationFolder(L"PilotPapulatusRightMove",
//			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\PilotPapulatus\\Move\\Right", math::Vector2(0.0f, -100.0f));
//
//		mAnimator->CreateAnimationFolder(L"PilotPapulatusRightHit",
//			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\PilotPapulatus\\Hit\\Right", math::Vector2(0.0f, -100.0f));
//
//		mAnimator->CreateAnimationFolder(L"PilotPapulatusRightDead",
//			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\PilotPapulatus\\Die\\Right", math::Vector2(0.0f, -100.0f));
//
//		//Right Skill
//		mAnimator->CreateAnimationFolder(L"PilotPapulatusRightSkill1",
//			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\PilotPapulatus\\Skill1\\Right", math::Vector2(0.0f, -160.0f), 0.077f);
//
//		mAnimator->CreateAnimationFolder(L"PilotPapulatusRightSkill2",
//			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\PilotPapulatus\\Skill2\\Right", math::Vector2(75.0f, -100.0f), 0.077f);
//
//		mAnimator->CreateAnimationFolder(L"PilotPapulatusRightSkill3",
//			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\PilotPapulatus\\Skill3\\Right", math::Vector2(0.0f, -140.0f), 0.077f);
//
//		mAnimator->CreateAnimationFolder(L"PilotPapulatusRightSkill4",
//			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\PilotPapulatus\\Skill4\\Right", math::Vector2(0.0f, -100.0f), 0.077f);
//
//		mAnimator->CreateAnimationFolder(L"PilotPapulatusRightSkill5",
//			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\PilotPapulatus\\Skill5\\Right", math::Vector2(0.0f, -120.0f), 0.077f);
//
//		mAnimator->CreateAnimationFolder(L"PilotPapulatusRightSleep",
//			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\PilotPapulatus\\Skill5\\Sleep\\Right", math::Vector2(0.0f, -50.0f), 0.077f);
//
//		mAnimator->CreateAnimationFolder(L"PilotPapulatusRightWakeUp",
//			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\PilotPapulatus\\Skill5\\WakeUp\\Right", math::Vector2(0.0f, -120.0f), 0.077f);
//
//
//
//		mPilotPapulatusHitSound = ResourceManager::Load<Sound>(L"PilotPapulatusHitSound", L"..\\Resources\\Maple\\Sound\\Monster\\PilotPapulatus\\PilotPapulatus_Die.wav");
//		mPilotPapulatusDeadSound = ResourceManager::Load<Sound>(L"PilotPapulatusDeadSound", L"..\\Resources\\Maple\\Sound\\Monster\\PilotPapulatus\\PilotPapulatus_Hit.wav");
//
//		mAnimator->PlayAnimation(L"PilotPapulatusLeftMove", true);
//		mTransform->SetMoveDir(enums::eMoveDir::Left);
//
//		mAnimator->SetAffectedCamera(true);
//		mCollider->SetSize(math::Vector2(250.0f, 120.0f));
//		mCollider->SetOffset(math::Vector2(0.0f, 0.0f));
//		mDirection = mTransform->GetMoveDir();
//		mMoveTime = mMoveDelay;
//	}
//
//
//	void PilotPapulatus::Update()
//	{
//
//		int halfHp = mMonstersInfo.mMaxHp / 2;
//		if (halfHp >= mMonstersInfo.mHp && false == mbSleepOn)
//		{
//			float playerPosX = SceneManager::GetPlayer()->GetPositionX();
//			float PilotPapulatusPosX = mTransform->GetPositionX();
//			mbSleepOn = true;
//			if (playerPosX <= PilotPapulatusPosX)
//			{
//				mAnimator->PlayAnimation(L"PilotPapulatusLeftSkill5", false);
//				mDirection = enums::eMoveDir::Left;
//			}
//			else
//			{
//				mAnimator->PlayAnimation(L"PilotPapulatusRightSkill5", false);
//				mDirection = enums::eMoveDir::Right;
//			}
//
//			PilotPapulatusSkill5* papulatusSkill5 = new PilotPapulatusSkill5(this);
//			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, papulatusSkill5);
//			mMonsterState = eMonsterState::Skill5;
//		}
//
//		if (mMonstersInfo.mHp <= 0)
//		{
//			mPilotPapulatusDeadSound->Play(false);
//			mMonsterState = eMonsterState::Dead;
//		}
//
//		switch (mMonsterState)
//		{
//		case ex::Monsters::eMonsterState::Idle:
//			Idle();
//			break;
//		case ex::Monsters::eMonsterState::Move:
//			Move();
//			break;
//		case ex::Monsters::eMonsterState::Chase:
//			Chase();
//			break;
//		case ex::Monsters::eMonsterState::Hit:
//			Hit();
//			break;
//		case ex::Monsters::eMonsterState::Dead:
//			Dead();
//			break;
//		case ex::Monsters::eMonsterState::Skill1:
//			Skill1();
//			break;
//		case ex::Monsters::eMonsterState::Skill2:
//			Skill2();
//			break;
//		case ex::Monsters::eMonsterState::Skill3:
//			Skill3();
//			break;
//		case ex::Monsters::eMonsterState::Skill4:
//			Skill4();
//			break;
//		case ex::Monsters::eMonsterState::Skill5:
//			Skill5();
//			break;
//
//		default:
//			break;
//		}
//
//
//		GameObject::Update();
//	}
//
//	void PilotPapulatus::Render(HDC _hdc)
//	{
//		GameObject::Render(_hdc);
//	}
//
//	void PilotPapulatus::Idle()
//	{
//		mIdleDelay += Time::GetDeltaTime();
//
//		math::Vector2 pos = mTransform->GetPosition();
//		if (mIdleDelay >= 2.3f)
//		{
//			if (mbChaseOn)
//			{
//				mMonsterState = eMonsterState::Chase;
//			}
//			else
//			{
//				if (mDirection == enums::eMoveDir::Left)
//				{
//					mDirection = enums::eMoveDir::Right;
//				}
//				else
//				{
//					mDirection = enums::eMoveDir::Left;
//				}
//				mMonsterState = eMonsterState::Move;
//			}
//			mIdleDelay = 0.0f;
//		}
//
//		if (mDirection == enums::eMoveDir::Left)
//		{
//			mAnimator->PlayAnimation(L"PilotPapulatusLeftIdle", true);
//		}
//		else
//		{
//			mAnimator->PlayAnimation(L"PilotPapulatusRightIdle", true);
//		}
//
//
//		mSkillDelay += Time::GetDeltaTime();
//		if (mSkillDelay >= 1.5f)
//		{
//			math::Vector2 playerPos = SceneManager::GetPlayer()->GetPosition();
//			float distanceX = fabs(playerPos.x - this->GetPositionX());
//			float distanceY = fabs(playerPos.y - this->GetPositionY());
//
//			mUsingSkillNumber = rand() % 4 + 1;
//
//			if (distanceX < 300.0f && distanceY < 200.0f)
//			{
//				float playerPosX = SceneManager::GetPlayer()->GetPositionX();
//				float PilotPapulatusPosX = mTransform->GetPositionX();
//
//				if (mUsingSkillNumber == 1)
//				{
//					if (playerPosX <= PilotPapulatusPosX)
//					{
//						mAnimator->PlayAnimation(L"PilotPapulatusLeftSkill1", false);
//						mDirection = enums::eMoveDir::Left;
//					}
//					else
//					{
//						mAnimator->PlayAnimation(L"PilotPapulatusRightSkill1", false);
//						mDirection = enums::eMoveDir::Right;
//					}
//					PilotPapulatusSkill1* papulatusSkill1 = new PilotPapulatusSkill1(this);
//					object::ActiveSceneAddGameObject(enums::eLayerType::Effect, papulatusSkill1);
//					mMonsterState = eMonsterState::Skill1;
//				}
//				else if (mUsingSkillNumber == 2)
//				{
//					if (playerPosX <= PilotPapulatusPosX)
//					{
//						mAnimator->PlayAnimation(L"PilotPapulatusLeftSkill2", false);
//						mDirection = enums::eMoveDir::Left;
//					}
//					else
//					{
//						mAnimator->PlayAnimation(L"PilotPapulatusRightSkill2", false);
//						mDirection = enums::eMoveDir::Right;
//					}
//					PilotPapulatusSkill2* papulatusSkill2 = new PilotPapulatusSkill2(this);
//					object::ActiveSceneAddGameObject(enums::eLayerType::Effect, papulatusSkill2);
//					mMonsterState = eMonsterState::Skill2;
//				}
//				else if (mUsingSkillNumber == 3)
//				{
//					if (playerPosX <= PilotPapulatusPosX)
//					{
//						mAnimator->PlayAnimation(L"PilotPapulatusLeftSkill3", false);
//						mDirection = enums::eMoveDir::Left;
//					}
//					else
//					{
//						mAnimator->PlayAnimation(L"PilotPapulatusRightSkill3", false);
//						mDirection = enums::eMoveDir::Right;
//					}
//					PilotPapulatusSkill3* papulatusSkill3 = new PilotPapulatusSkill3(this);
//					object::ActiveSceneAddGameObject(enums::eLayerType::Effect, papulatusSkill3);
//					mMonsterState = eMonsterState::Skill3;
//				}
//				else if (mUsingSkillNumber == 4)
//				{
//					if (playerPosX <= PilotPapulatusPosX)
//					{
//						mAnimator->PlayAnimation(L"PilotPapulatusLeftSkill4", false);
//						mDirection = enums::eMoveDir::Left;
//					}
//					else
//					{
//						mAnimator->PlayAnimation(L"PilotPapulatusRightSkill4", false);
//						mDirection = enums::eMoveDir::Right;
//					}
//
//					PilotPapulatusSkill4* papulatusSkill4 = new PilotPapulatusSkill4(this);
//					object::ActiveSceneAddGameObject(enums::eLayerType::Effect, papulatusSkill4);
//					mMonsterState = eMonsterState::Skill4;
//				}
//				mSkillDelay = 0.0f;
//				mTransform->SetMoveDir(mDirection);
//			}
//		}
//
//
//	}
//
//	void PilotPapulatus::Move()
//	{
//		mMoveTime -= Time::GetDeltaTime();
//		math::Vector2 pos = mTransform->GetPosition();
//		if (mMoveTime <= 0.0f)
//		{
//			mMonsterState = eMonsterState::Idle;
//			mMoveTime = mMoveDelay;
//		}
//		else
//		{
//			if (mDirection == enums::eMoveDir::Left)
//			{
//				mAnimator->PlayAnimation(L"PilotPapulatusLeftMove", true);
//				mDirection = enums::eMoveDir::Left;
//				pos.x -= 50.0f * Time::GetDeltaTime();
//			}
//			else
//			{
//				mAnimator->PlayAnimation(L"PilotPapulatusRightMove", true);
//				mDirection = enums::eMoveDir::Right;
//				pos.x += 50.0f * Time::GetDeltaTime();
//			}
//		}
//
//		mTransform->SetMoveDir(mDirection);
//		mTransform->SetPosition(pos);
//	}
//
//	void PilotPapulatus::Chase()
//	{
//		float playerPosX = SceneManager::GetPlayer()->GetPositionX();
//		float papulatusPosX = mTransform->GetPositionX();
//		math::Vector2 pos = mTransform->GetPosition();
//		float diff = playerPosX - papulatusPosX;
//		if (playerPosX <= papulatusPosX)
//		{
//			mAnimator->PlayAnimation(L"PilotPapulatusLeftMove", true);
//			mDirection = enums::eMoveDir::Left;
//			if (diff < 10.0f)
//			{
//				pos.x -= 60.0f * Time::GetDeltaTime();
//			}
//		}
//		else
//		{
//			mAnimator->PlayAnimation(L"PilotPapulatusRightMove", true);
//			mDirection = enums::eMoveDir::Right;
//			if (diff > 10.0f)
//			{
//				pos.x += 60.0f * Time::GetDeltaTime();
//			}
//		}
//		math::Vector2 playerPos = SceneManager::GetPlayer()->GetPosition();
//		float distanceX = fabs(playerPos.x - this->GetPositionX());
//		float distanceY = fabs(playerPos.y - this->GetPositionY());
//		if (distanceX < 300.0f && distanceY < 200.0f)
//		{
//			mMonsterState = eMonsterState::Idle;
//		}
//
//		mTransform->SetPosition(pos);
//		mTransform->SetMoveDir(mDirection);
//	}
//
//	void PilotPapulatus::Hit()
//	{
//		mbChaseOn = true;
//		float playerPosX = SceneManager::GetPlayer()->GetPositionX();
//		float GateKeeperPosX = mTransform->GetPositionX();
//		if (playerPosX <= GateKeeperPosX)
//		{
//			mAnimator->PlayAnimation(L"PilotPapulatusLeftHit", false);
//			mDirection = enums::eMoveDir::Left;
//		}
//		else
//		{
//			mAnimator->PlayAnimation(L"PilotPapulatusRightHit", false);
//			mDirection = enums::eMoveDir::Right;
//		}
//		mHitDelay += Time::GetDeltaTime();
//		if (mHitDelay >= 1.3f)
//		{
//			if (mDirection == enums::eMoveDir::Left)
//			{
//				mAnimator->PlayAnimation(L"PilotPapulatusLeftMove", true);
//				mDirection = enums::eMoveDir::Left;
//			}
//			else
//			{
//				mAnimator->PlayAnimation(L"PilotPapulatusRightMove", true);
//				mDirection = enums::eMoveDir::Right;
//			}
//			if (mbChaseOn)
//			{
//				mMonsterState = eMonsterState::Chase;
//			}
//			else
//			{
//				mMonsterState = eMonsterState::Move;
//			}
//
//			mHitDelay = 0.0f;
//		}
//		mTransform->SetMoveDir(mDirection);
//	}
//
//	void PilotPapulatus::Dead()
//	{
//		if (mDirection == enums::eMoveDir::Left)
//		{
//			mAnimator->PlayAnimation(L"PilotPapulatusLeftDead", false);
//		}
//		else
//		{
//			mAnimator->PlayAnimation(L"PilotPapulatusRightDead", false);
//
//		}
//
//		bool bCheck = mAnimator->IsActiveAnimationComplete();
//		if (bCheck)
//		{
//			Destroy(this);
//		}
//	}
//
//	void PilotPapulatus::Skill1()
//	{
//		bool bCheck = mAnimator->IsActiveAnimationComplete();
//		if (bCheck)
//		{
//			mMonsterState = eMonsterState::Idle;
//		}
//	}
//
//	void PilotPapulatus::Skill2()
//	{
//		bool bCheck = mAnimator->IsActiveAnimationComplete();
//		if (bCheck)
//		{
//			mMonsterState = eMonsterState::Idle;
//		}
//	}
//
//	void PilotPapulatus::Skill3()
//	{
//		float playerPosX = SceneManager::GetPlayer()->GetPositionX();
//		float PilotPapulatusPosX = mTransform->GetPositionX();
//		mSkill3Delay += Time::GetDeltaTime();
//		if (mSkill3Delay <= 4.0f)
//		{
//			if (playerPosX <= PilotPapulatusPosX)
//			{
//				mAnimator->PlayAnimation(L"PilotPapulatusLeftSkill3", false);
//				mDirection = enums::eMoveDir::Left;
//			}
//			else
//			{
//				mAnimator->PlayAnimation(L"PilotPapulatusRightSkill3", false);
//				mDirection = enums::eMoveDir::Right;
//			}
//
//		}
//
//		bool bCheck = mAnimator->IsActiveAnimationComplete();
//		if (bCheck)
//		{
//			if (playerPosX <= PilotPapulatusPosX)
//			{
//				mAnimator->PlayAnimation(L"PilotPapulatusLeftIdle", false);
//				mDirection = enums::eMoveDir::Left;
//			}
//			else
//			{
//				mAnimator->PlayAnimation(L"PilotPapulatusRightIdle", false);
//				mDirection = enums::eMoveDir::Right;
//			}
//			mMonsterState = eMonsterState::Idle;
//		}
//		mSkill3Delay = 0.0f;
//
//
//	}
//
//	void PilotPapulatus::Skill4()
//	{
//		bool bCheck = mAnimator->IsActiveAnimationComplete();
//		if (bCheck)
//		{
//			mMonsterState = eMonsterState::Idle;
//		}
//	}
//
//	void PilotPapulatus::Skill5()
//	{
//		float playerPosX = SceneManager::GetPlayer()->GetPositionX();
//		float PilotPapulatusPosX = mTransform->GetPositionX();
//
//		bool bCheck = mAnimator->IsActiveAnimationComplete();
//		if (bCheck)
//		{
//			if (playerPosX <= PilotPapulatusPosX)
//			{
//				mAnimator->PlayAnimation(L"PilotPapulatusLeftSleep", false);
//				mDirection = enums::eMoveDir::Left;
//			}
//			else
//			{
//				mAnimator->PlayAnimation(L"PilotPapulatusRightSleep", false);
//				mDirection = enums::eMoveDir::Right;
//			}
//			PilotPapulatusSleep* papulatusSleep = new PilotPapulatusSleep(this);
//			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, papulatusSleep);
//			mMonsterState = eMonsterState::Sleep;
//		}
//	}
//
//
//
//	void PilotPapulatus::OnCollisionEnter(Collider* _other)
//	{
//		if (mMonsterState != eMonsterState::Sleep && mMonsterState != eMonsterState::WakeUp && mMonsterState != eMonsterState::Skill5)
//		{
//			PlayerAttack* playerAtt = dynamic_cast<PlayerAttack*>(_other->GetOwner());
//			if (playerAtt != nullptr && mMonsterState != eMonsterState::Dead)
//			{
//				std::set<GameObject*>* attList = playerAtt->GetAttackList();
//
//				if (attList->find(this) == attList->end())
//				{
//					mPilotPapulatusHitSound->Play(false);
//					attList->insert(this);
//					if (mMonsterState == eMonsterState::Idle ||
//						mMonsterState == eMonsterState::Move ||
//						mMonsterState == eMonsterState::Chase)
//					{
//						mMonsterState = eMonsterState::Hit;
//
//					}
//				}
//			}
//
//			Raisingblow* raisingblow = dynamic_cast<Raisingblow*>(_other->GetOwner());
//			if (raisingblow != nullptr && mMonsterState != eMonsterState::Dead)
//			{
//				std::set<GameObject*>* attList = raisingblow->GetAttackList();
//
//				if (attList->find(this) == attList->end())
//				{
//					mPilotPapulatusHitSound->Play(false);
//					RaisingblowHit* raisingBlowHit = new RaisingblowHit(this);
//					object::ActiveSceneAddGameObject(enums::eLayerType::Effect, raisingBlowHit);
//					attList->insert(this);
//					if (mMonsterState == eMonsterState::Idle ||
//						mMonsterState == eMonsterState::Move ||
//						mMonsterState == eMonsterState::Chase)
//					{
//						mMonsterState = eMonsterState::Hit;
//
//					}
//				}
//			}
//
//			UpperCharge* upperCharge = dynamic_cast<UpperCharge*>(_other->GetOwner());
//			if (upperCharge != nullptr && mMonsterState != eMonsterState::Dead)
//			{
//				std::set<GameObject*>* attList = upperCharge->GetAttackList();
//
//				if (attList->find(this) == attList->end())
//				{
//					mPilotPapulatusHitSound->Play(false);
//					attList->insert(this);
//					if (mMonsterState == eMonsterState::Idle ||
//						mMonsterState == eMonsterState::Move ||
//						mMonsterState == eMonsterState::Chase)
//					{
//						mMonsterState = eMonsterState::Hit;
//
//					}
//
//				}
//			}
//
//			Rush* rush = dynamic_cast<Rush*>(_other->GetOwner());
//			if (rush != nullptr && mMonsterState != eMonsterState::Dead)
//			{
//				std::set<GameObject*>* attList = rush->GetAttackList();
//
//				if (attList->find(this) == attList->end())
//				{
//					mPilotPapulatusHitSound->Play(false);
//					attList->insert(this);
//					if (mMonsterState == eMonsterState::Idle ||
//						mMonsterState == eMonsterState::Move ||
//						mMonsterState == eMonsterState::Chase)
//					{
//						mMonsterState = eMonsterState::Hit;
//
//					}
//
//				}
//			}
//
//			ComboDeathFaultScreen* ComboDeathFault = dynamic_cast<ComboDeathFaultScreen*>(_other->GetOwner());
//			if (ComboDeathFault != nullptr && mMonsterState != eMonsterState::Dead)
//			{
//				std::set<GameObject*>* attList = ComboDeathFault->GetAttackList();
//
//				if (attList->find(this) == attList->end())
//				{
//					mPilotPapulatusHitSound->Play(false);
//					attList->insert(this);
//					if (mMonsterState == eMonsterState::Idle ||
//						mMonsterState == eMonsterState::Move ||
//						mMonsterState == eMonsterState::Chase)
//					{
//						mMonsterState = eMonsterState::Hit;
//
//					}
//				}
//			}
//		}
//		Player* player = dynamic_cast<Player*>(_other->GetOwner());
//		if (player != nullptr && player->IsInvincible() == false)
//		{
//			DamageManager* damage = new DamageManager();
//			object::ActiveSceneAddGameObject(enums::eLayerType::UI, damage);
//			damage->SetPosition(math::Vector2(player->GetPositionX(), player->GetPositionY() - 28.0f));
//			damage->PlayMonsterDamageAnimation(this->GetMonstersInfo().mDamage);
//
//		}
//	}
//
//	void PilotPapulatus::OnCollisionStay(Collider* _other)
//	{
//	}
//
//	void PilotPapulatus::OnCollisionExit(Collider* _other)
//	{
//	}
//
//}