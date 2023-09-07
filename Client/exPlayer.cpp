#include "exPlayer.h"
#include "exInput.h" 
#include "exTime.h"
#include "exResourceManager.h"
#include "exTexture.h"
#include "exObject.h"
#include "exCollisionManager.h"
#include "exPortal.h"
#include "exSceneManager.h"
#include "exMonsters.h"
#include "exSound.h"
#include "exLevel.h"
#include "exStun.h"
#include "exBuff.h"

// Component
#include "exTransform.h"
#include "exRigidbody.h"
#include "exAnimator.h"
#include "exCollider.h"
// Skill
#include "exPlayerAttack.h"
#include "exWarriorLeap.h"
#include "exRaisingblow.h"
#include "exUpperCharge.h"
#include "exRush.h"
#include "exComboDeathFaultPlayer.h"
#include "exComboDeathFaultScreen.h"
#include "exComboSynergyBody.h"
#include "exLevelUp.h"


namespace ex
{
	Player::Player()
		: mAnimator(nullptr)
		, mTransform(nullptr)
		, mRigidbody(nullptr)
		, mCollider(nullptr)
		, mState(eState::End)
		, mbInvincible(false)
		, mbPortalState(false)
		, mbRopeState(false)
		, mbDoubleJump(false)
		, mJumpSound(nullptr)
		, mPortionSound(nullptr)
		, mbLevelUpCheck(false)
		, mLevelUpSound(nullptr)
		, mPlayerDeadSound(nullptr)
		, mbKnockBackCheck(true)
		, mbStunCheck(false)
		, mStunDelay(0.0f)
		, mhitDelay(0.0f)
		, mLevelArr{}
		, mbBuffCheck(false)
		, mBuff(nullptr)
	{
		srand(static_cast<unsigned int>(time(nullptr)));

		mInfo = new PlayerInfo();
		mInfo->mMaxHp = 70000;
		mInfo->mHp = 70000;
		mInfo->mMp = 20000;
		mInfo->mMaxMp = 20000;
		mInfo->mLevel = 200;
		mInfo->mMinDamage = 7300;
		mInfo->mMaxDamage = 15212;
		mInfo->mMaxExp = 100.0f;
		mInfo->mExp = 0.0f;

	}

	Player::~Player()
	{
		if (nullptr != mInfo)
		{
			delete mInfo;
			mInfo = nullptr;
		}
	}

	void Player::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mRigidbody = AddComponent<Rigidbody>();
		mCollider = AddComponent<Collider>();
		mTransform = GetComponent<Transform>();

		// 왼쪽 애니메이션
		Texture* image = ResourceManager::Load<Texture>(L"PlayerLeftIdle"
			, L"..\\Resources\\Maple\\Image\\Player2\\Left\\Bmp\\Player_Left_Idle.bmp");
		mAnimator->CreateAnimation(L"PlayerLeftIdle", image, math::Vector2(0.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(224.0f, 156.0f), 3, math::Vector2(-23.0f, 0.0f));

		image = ResourceManager::Load<Texture>(L"PlayerLeftMove"
			, L"..\\Resources\\Maple\\Image\\Player2\\Left\\Bmp\\Player_Left_Move.bmp");
		mAnimator->CreateAnimation(L"PlayerLeftMove", image, math::Vector2(0.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(224.0f, 156.0f), 4, math::Vector2(-23.0f, 0.0f));

		image = ResourceManager::Load<Texture>(L"PlayerLeftDown"
			, L"..\\Resources\\Maple\\Image\\Player2\\Left\\Bmp\\Player_Left_Down.bmp");
		mAnimator->CreateAnimation(L"PlayerLeftDown", image, math::Vector2(0.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(224.0f, 156.0f), 1, math::Vector2(-23.0f, 0.0f));

		image = ResourceManager::Load<Texture>(L"PlayerLeftJump"
			, L"..\\Resources\\Maple\\Image\\Player2\\Left\\Bmp\\Player_Left_Jump.bmp");
		mAnimator->CreateAnimation(L"PlayerLeftJump", image, math::Vector2(0.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(224.0f, 156.0f), 1, math::Vector2(-23.0f, 0.0f));

		image = ResourceManager::Load<Texture>(L"PlayerLeftHit"
			, L"..\\Resources\\Maple\\Image\\Player2\\Left\\Bmp\\Player_Left_Hit.bmp");
		mAnimator->CreateAnimation(L"PlayerLeftHit", image, math::Vector2(0.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(224.0f, 156.0f), 3, math::Vector2(-23.0f, 0.0f));

		image = ResourceManager::Load<Texture>(L"PlayerLeftAttack"
			, L"..\\Resources\\Maple\\Image\\Player2\\Left\\Bmp\\Player_Left_Attack.bmp");
		mAnimator->CreateAnimation(L"PlayerLeftAttack", image, math::Vector2(0.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(224.0f, 156.0f), 3, math::Vector2(-23.0f, 0.0f), 0.14f);

		// 왼쪽 스킬 애니메이션
		image = ResourceManager::Load<Texture>(L"PlayerLeftRaisingBlow"
			, L"..\\Resources\\Maple\\Image\\Player2\\Left\\Bmp\\Skill\\RaisingBlow\\Left\\Player_Left_RaisingBlow.bmp");
		mAnimator->CreateAnimation(L"PlayerLeftRaisingBlow", image, math::Vector2(0.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(224.0f, 156.0f), 11, math::Vector2(0.0f, 0.0f), 0.04f);

		image = ResourceManager::Load<Texture>(L"PlayerLeftUpperCharge"
			, L"..\\Resources\\Maple\\Image\\Player2\\Left\\Bmp\\Skill\\UpperCharge\\Left\\Player_Left_UpperCharge.bmp");
		mAnimator->CreateAnimation(L"PlayerLeftUpperCharge", image, math::Vector2(0.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(224.0f, 156.0f), 9, math::Vector2(0.0f, 0.0f), 0.03f);

		image = ResourceManager::Load<Texture>(L"PlayerLeftRush"
			, L"..\\Resources\\Maple\\Image\\Player2\\Left\\Bmp\\Skill\\Rush\\Left\\Player_Left_Rush.bmp");
		mAnimator->CreateAnimation(L"PlayerLeftRush", image, math::Vector2(0.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(224.0f, 156.0f), 7, math::Vector2(0.0f, 0.0f), 0.05f);

		image = ResourceManager::Load<Texture>(L"PlayerLeftComboDeathFault"
			, L"..\\Resources\\Maple\\Image\\Player2\\Left\\Bmp\\Skill\\ComboDeathFault\\Left\\Player_Left_ComboDeathFault.bmp");
		mAnimator->CreateAnimation(L"PlayerLeftComboDeathFault", image, math::Vector2(0.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(224.0f, 156.0f), 21, math::Vector2(0.0f, 0.0f), 0.05f);


		// 오른쪽 애니메이션
		image = ResourceManager::Load<Texture>(L"PlayerRightIdle"
			, L"..\\Resources\\Maple\\Image\\Player2\\Right\\Bmp\\Player_Right_Idle.bmp");
		mAnimator->CreateAnimation(L"PlayerRightIdle", image, math::Vector2(0.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(224.0f, 156.0f), 3);

		image = ResourceManager::Load<Texture>(L"PlayerRightMove"
			, L"..\\Resources\\Maple\\Image\\Player2\\Right\\Bmp\\Player_Right_Move.bmp");
		mAnimator->CreateAnimation(L"PlayerRightMove", image, math::Vector2(0.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(224.0f, 156.0f), 4);

		image = ResourceManager::Load<Texture>(L"PlayerRightDown"
			, L"..\\Resources\\Maple\\Image\\Player2\\Right\\Bmp\\Player_Right_Down.bmp");
		mAnimator->CreateAnimation(L"PlayerRightDown", image, math::Vector2(0.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(224.0f, 156.0f), 1);

		image = ResourceManager::Load<Texture>(L"PlayerRightJump"
			, L"..\\Resources\\Maple\\Image\\Player2\\Right\\Bmp\\Player_Right_Jump.bmp");
		mAnimator->CreateAnimation(L"PlayerRightJump", image, math::Vector2(0.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(224.0f, 156.0f), 1);

		image = ResourceManager::Load<Texture>(L"PlayerRightHit"
			, L"..\\Resources\\Maple\\Image\\Player2\\Right\\Bmp\\Player_Right_Hit.bmp");
		mAnimator->CreateAnimation(L"PlayerRightHit", image, math::Vector2(0.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(224.0f, 156.0f), 3);

		image = ResourceManager::Load<Texture>(L"PlayerRightAttack"
			, L"..\\Resources\\Maple\\Image\\Player2\\Right\\Bmp\\Player_Right_Attack.bmp");
		mAnimator->CreateAnimation(L"PlayerRightAttack", image, math::Vector2(672.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(-224.0f, 0.0f), 3, math::Vector2(0.f, 0.f), 0.14f);

		// 오른쪽 스킬 애니메이션
		image = ResourceManager::Load<Texture>(L"PlayerRightRaisingBlow"
			, L"..\\Resources\\Maple\\Image\\Player2\\Left\\Bmp\\Skill\\RaisingBlow\\Right\\Player_Right_RaisingBlow.bmp");
		mAnimator->CreateAnimation(L"PlayerRightRaisingBlow", image, math::Vector2(2464.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(-224.0f, 0.0f), 11, math::Vector2(0.0f, 0.0f), 0.04f);

		image = ResourceManager::Load<Texture>(L"PlayerRightUpperCharge"
			, L"..\\Resources\\Maple\\Image\\Player2\\Left\\Bmp\\Skill\\UpperCharge\\Right\\Player_Right_UpperCharge.bmp");
		mAnimator->CreateAnimation(L"PlayerRightUpperCharge", image, math::Vector2(2016.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(-224.0f, 0.0f), 9, math::Vector2(0.0f, 0.0f), 0.03f);

		image = ResourceManager::Load<Texture>(L"PlayerRightRush"
			, L"..\\Resources\\Maple\\Image\\Player2\\Left\\Bmp\\Skill\\Rush\\Right\\Player_Right_Rush.bmp");
		mAnimator->CreateAnimation(L"PlayerRightRush", image, math::Vector2(2016.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(-224.0f, 0.0f), 9, math::Vector2(0.0f, 0.0f), 0.05f);

		image = ResourceManager::Load<Texture>(L"PlayerRightComboDeathFault"
			, L"..\\Resources\\Maple\\Image\\Player2\\Left\\Bmp\\Skill\\ComboDeathFault\\Right\\Player_Right_ComboDeathFault.bmp");
		mAnimator->CreateAnimation(L"PlayerRightComboDeathFault", image, math::Vector2(4704.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(-224.0f, 0.0f), 21, math::Vector2(0.0f, 0.0f), 0.05f);

		// 로프
		image = ResourceManager::Load<Texture>(L"PlayerRopeMove"
			, L"..\\Resources\\Maple\\Image\\Player2\\Left\\Bmp\\Player_Rope.bmp");
		mAnimator->CreateAnimation(L"PlayerRopeMove", image, math::Vector2(0.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(224.0f, 156.0f), 2, math::Vector2(-23.0f, 0.0f));

		// 이미지 미리 로드
		PlayerSkillLoad();

		// 플레이어 Dead
		image = ResourceManager::Load<Texture>(L"PlayerDead"
			, L"..\\Resources\\Maple\\Image\\Dead\\Tomb.bmp");
		mAnimator->CreateAnimation(L"PlayerDead", image, math::Vector2(0.0f, 0.0f), math::Vector2(101.0f, 47.0f)
			, math::Vector2(101.0f, 47.0f), 20, math::Vector2(0.0f, 25.0f), 0.05f);


		// Player Sound
		mJumpSound = ResourceManager::Load<Sound>(L"PlayerJump", L"..\\Resources\\Maple\\Sound\\Player\\Player_Jump.wav");
		mPortionSound = ResourceManager::Load<Sound>(L"PlayerPortion", L"..\\Resources\\Maple\\Sound\\Player\\Player_Portion.wav");
		mPlayerDeadSound = ResourceManager::Load<Sound>(L"PlayerDieSound", L"..\\Resources\\Maple\\Sound\\Player\\Player_Die.wav");


		mTransform->SetMoveDir(enums::eMoveDir::Right);
		mCollider->SetSize(math::Vector2(45.0f, 70.0f));
		mCollider->SetOffset(math::Vector2(-12.0f, 10.0f));
		mState = eState::Idle;

	}

	void Player::Update()
	{
		float num = mRigidbody->GetFriction();
		math::Vector2 vel = mRigidbody->GetVelocity();
		math::Vector2 velLimit = mRigidbody->GetLimitedVeloctyX();
		math::Vector2 pos = mTransform->GetPosition();
		float minDamage = mInfo->mMinDamage;
		float maxDamage = mInfo->mMaxDamage;

		PlayLevelUI();

		// 플레이어가 떨어졌을시 
		if (Input::GetKeyDown(eKeyCode::P))
		{
			enums::eMoveDir playerDir = mTransform->GetMoveDir();
			mTransform->SetPosition(math::Vector2(mTransform->GetPositionX(), 260.0f));
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftJump", false);
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightJump", false);
			}
			mState = eState::Fall;
		}

		if (mbLevelUpCheck)
		{
			LevelUp* playerLevelUp = new LevelUp(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, playerLevelUp);
			mInfo->mLevel += 1;

			mInfo->mHp = mInfo->mMaxHp;
			mInfo->mMp = mInfo->mMaxMp;

			mbLevelUpCheck = false;
		}

		if (Input::GetKeyDown(eKeyCode::H) && mState != eState::Death)
		{
			mPortionSound->Play(false);
			mInfo->mHp += mInfo->mMaxHp / 2;

			if (mInfo->mHp > mInfo->mMaxHp)
			{
				mInfo->mHp = mInfo->mMaxHp;
			}
		}

		math::Vector2 playerPos = mTransform->GetPosition();

		if (mbInvincible)
		{
			mhitDelay += Time::GetDeltaTime();
			if (mhitDelay >= 1.0f)
			{
				mbInvincible = false;
				mhitDelay = 0.0f;
				//mState = eState::Idle;
			}
		}
		if (mState == eState::Jump || mState == eState::Rope || mState == eState::DoubleJump || mState == eState::UpperCharge)
		{
			CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Floor, false);
		}
		else
		{
			CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Floor, true);
		}

		if (mState == eState::Jump || mState == eState::Rope || mState == eState::DoubleJump ||
			mState == eState::UpperCharge || mState == eState::Rush || mState == eState::ComboDeathFault ||
			mState == eState::Death)
		{
			CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Monster, false);
		}
		else
		{
			CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Monster, true);
		}

		if (mState == eState::Death)
		{
			CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Effect, false);
		}
		else
		{
			CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Effect, true);
		}

		if (mbStunCheck)
		{
			mState = eState::Stun;
		}

		switch (mState)
		{
		case Player::eState::Idle:
			Idle();
			break;
		case Player::eState::Move:
			Move();
			break;
		case Player::eState::Jump:
			Jump();
			break;
		case Player::eState::DoubleJump:
			DoubleJump();
			break;
		case Player::eState::Down:
			Down();
			break;
		case Player::eState::Fall:
			Fall();
			break;
		case Player::eState::Rope:
			Rope();
			break;
		case Player::eState::Attack:
			Attack();
			break;
		case Player::eState::JumpAttack:
			JumpAttack();
			break;
		case Player::eState::RaisingBlow:
			RaisingBlow();
			break;
		case Player::eState::UpperCharge:
			Uppercharge();
			break;
		case Player::eState::Rush:
			PlayerRush();
			break;
		case Player::eState::ComboDeathFault:
			ComboDeathFault();
			break;
		case Player::eState::Hit:
			Hit();
			break;
		case Player::eState::Death:
			Death();
			break;
		case Player::eState::Buff:
			PlayerBuff();
			break;
		case Player::eState::Stun:
			Stun();
			break;
		case Player::eState::End:
			break;
		default:
			break;
		}

		GameObject::Update();
	}

	void Player::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Player::Idle()
	{
		enums::eMoveDir playerDir = mTransform->GetMoveDir();
		math::Vector2 velocity = mRigidbody->GetVelocity();
		math::Vector2 pos = mTransform->GetPosition();
		mbKnockBackCheck = true;

		// 좌우 Idle 상태
		if (playerDir == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"PlayerLeftIdle", true);
		}
		else if (playerDir == enums::eMoveDir::Right)
		{
			mAnimator->PlayAnimation(L"PlayerRightIdle", true);
		}

		// Rope, Down, Right, Left 키 입력 이동 상태
		if (Input::GetKeyDown(eKeyCode::Right))
		{
			mAnimator->PlayAnimation(L"PlayerRightMove", true);
			mTransform->SetMoveDir(enums::eMoveDir::Right);
			mState = eState::Move;
		}
		if (Input::GetKeyDown(eKeyCode::Left))
		{
			mAnimator->PlayAnimation(L"PlayerLeftMove", true);
			mTransform->SetMoveDir(enums::eMoveDir::Left);
			mState = eState::Move;
		}
		if (Input::GetKeyDown(eKeyCode::Up) && mbRopeState) // 로프와 충돌 했다면
		{
			mAnimator->PlayAnimation(L"PlayerRopeMove", true);
			pos.y -= 200.0f * Time::GetDeltaTime();
			mState = eState::Rope;
		}
		if (Input::GetKeyDown(eKeyCode::Down))
		{
			if (playerDir == enums::eMoveDir::Right)
			{
				mAnimator->PlayAnimation(L"PlayerRightDown", true);
				mState = eState::Down;
			}
			else if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftDown", true);
				mState = eState::Down;
			}

			if (mbRopeState)
			{
				mAnimator->PlayAnimation(L"PlayerRopeMove", true);
				pos.y += 200.0f * Time::GetDeltaTime();
				mState = eState::Rope;
			}

			mTransform->SetPosition(pos);
			mRigidbody->SetVelocity(velocity);
		}


		// Idle상태일때 점프키 입력
		if (Input::GetKeyDown(eKeyCode::Jump) || Input::GetKeyPressed(eKeyCode::Jump))
		{
			mRigidbody->SetGround(false);
			velocity.y = -700.0f;
			if (playerDir == enums::eMoveDir::Right)
			{
				mAnimator->PlayAnimation(L"PlayerRightJump", true);
				mState = eState::Jump;
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerLeftJump", true);
				mState = eState::Jump;
			}

			mJumpSound->Play(false);
			mRigidbody->SetVelocity(velocity);
		}

		// 기본 공격 키 
		if (Input::GetKeyDown(eKeyCode::Ctrl) || Input::GetKeyPressed(eKeyCode::Ctrl))
		{
			if (playerDir == enums::eMoveDir::Right)
			{
				mAnimator->PlayAnimation(L"PlayerRightAttack", false);
				mState = eState::Attack;
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerLeftAttack", false);
				mState = eState::Attack;
			}
			PlayerAttack* playerAttack = new PlayerAttack(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, playerAttack);
		}

		// 레이징 블로우
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyPressed(eKeyCode::A))
		{
			Raisingblow* raisingBlow = new Raisingblow(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, raisingBlow);
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftRaisingBlow", false);
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightRaisingBlow", false);
			}
			mState = eState::RaisingBlow;
		}

		// 어퍼 차지
		if (Input::GetKeyDown(eKeyCode::S) || Input::GetKeyPressed(eKeyCode::S))
		{
			UpperCharge* upperCharge = new UpperCharge(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, upperCharge);
			mRigidbody->SetGround(false);
			velocity.y = -1310.0f;
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftUpperCharge", false);
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightUpperCharge", false);
			}
			mState = eState::UpperCharge;
			mRigidbody->SetVelocity(velocity);
		}

		// 돌진
		if (Input::GetKeyDown(eKeyCode::D) || Input::GetKeyPressed(eKeyCode::D))
		{
			Rush* rush = new Rush(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, rush);
			if (playerDir == enums::eMoveDir::Left)
			{
				velocity.x = -900.0f;
				mAnimator->PlayAnimation(L"PlayerLeftRush", false);
			}
			else
			{
				velocity.x = 900.0f;
				mAnimator->PlayAnimation(L"PlayerRightRush", false);
			}
			mState = eState::Rush;
			mRigidbody->SetVelocity(velocity);
		}

		// 콤보 데스폴트
		if (Input::GetKeyDown(eKeyCode::F) || Input::GetKeyPressed(eKeyCode::F))
		{
			mbInvincible = true;
			ComboDeathFaultPlayer* comboDeath = new ComboDeathFaultPlayer(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, comboDeath);
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftComboDeathFault", false);
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightComboDeathFault", false);
			}
			mState = eState::ComboDeathFault;
			mRigidbody->SetVelocity(velocity);
		}

		// 콤보 시너지
		if (Input::GetKeyDown(eKeyCode::Z))
		{
			if (playerDir == enums::eMoveDir::Left && mbBuffCheck == false)
			{
				mAnimator->PlayAnimation(L"PlayerLeftHit", false);
			}
			else if (playerDir == enums::eMoveDir::Right && mbBuffCheck == false)
			{
				mAnimator->PlayAnimation(L"PlayerRightHit", false);
			}

			if (mbBuffCheck == false)
			{
				mBuff = new Buff(this);
				object::ActiveSceneAddGameObject(enums::eLayerType::Effect, mBuff);
				mInfo->mMinDamage += 4000.0f;
				mInfo->mMaxDamage += 4000.0f;
				mbBuffCheck = true;
			}
			else if (mbBuffCheck)
			{
				mbBuffCheck = false;
				mBuff = nullptr;
				mInfo->mMinDamage -= 4000.0f;
				mInfo->mMaxDamage -= 4000.0f;
			}

			mState = eState::Buff;
			mRigidbody->SetVelocity(velocity);
		}

		if (Input::GetKeyPressed(eKeyCode::Down) && Input::GetKeyDown(eKeyCode::Jump))
		{
			mRigidbody->SetGround(false);
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftJump", true);
				mState = eState::Fall;
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightJump", true);
				mState = eState::Fall;
			}
			mJumpSound->Play(false);
		}
	}

	void Player::Move()
	{
		math::Vector2 pos = mTransform->GetPosition();
		enums::eMoveDir playerDir = mTransform->GetMoveDir();
		math::Vector2 velocity = mRigidbody->GetVelocity();

		if (Input::GetKeyPressed(eKeyCode::Left))
		{
			//velocity.x = -200.0f;
			pos.x += -200.0f * Time::GetDeltaTime();
			mTransform->SetMoveDir(enums::eMoveDir::Left);

		}
		if (Input::GetKeyPressed(eKeyCode::Right))
		{
			//velocity.x = 200.0f;
			pos.x += 200.0f * Time::GetDeltaTime();
			mTransform->SetMoveDir(enums::eMoveDir::Right);
		}

		// 이동중 공격 상태
		if (Input::GetKeyPressed(eKeyCode::Right) && Input::GetKeyDown(eKeyCode::Ctrl))
		{
			PlayerAttack* playerAttack = new PlayerAttack(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, playerAttack);
			mAnimator->PlayAnimation(L"PlayerRightAttack", false);
			mRigidbody->SetVelocity(0.0f);
			mState = eState::Attack;
		}
		if (Input::GetKeyPressed(eKeyCode::Left) && Input::GetKeyDown(eKeyCode::Ctrl))
		{
			PlayerAttack* playerAttack = new PlayerAttack(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, playerAttack);
			mAnimator->PlayAnimation(L"PlayerLeftAttack", false);
			mRigidbody->SetVelocity(0.0f);
			mState = eState::Attack;
		}

		// 레이징 블로우
		if (Input::GetKeyPressed(eKeyCode::Left) && Input::GetKeyDown(eKeyCode::A))
		{
			Raisingblow* raisingBlow = new Raisingblow(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, raisingBlow);
			mAnimator->PlayAnimation(L"PlayerLeftRaisingBlow", false);
			mState = eState::RaisingBlow;
		}
		if (Input::GetKeyPressed(eKeyCode::Right) && Input::GetKeyDown(eKeyCode::A))
		{
			Raisingblow* raisingBlow = new Raisingblow(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, raisingBlow);
			mAnimator->PlayAnimation(L"PlayerRightRaisingBlow", false);
			mState = eState::RaisingBlow;
		}

		// 어퍼 차지
		if (Input::GetKeyDown(eKeyCode::S) || Input::GetKeyPressed(eKeyCode::S))
		{
			mRigidbody->SetGround(false);
			velocity.x = 0.0f;
			velocity.y = -1310.0f;
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftUpperCharge", false);
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightUpperCharge", false);
			}
			UpperCharge* upperCharge = new UpperCharge(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, upperCharge);
			mState = eState::UpperCharge;
			mRigidbody->SetVelocity(velocity);
		}

		// 돌진
		if (Input::GetKeyDown(eKeyCode::D) || Input::GetKeyPressed(eKeyCode::D))
		{
			mRigidbody->SetVelocityX(0.0f);
			Rush* rush = new Rush(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, rush);
			if (playerDir == enums::eMoveDir::Left)
			{
				velocity.x = -850.0f;
				mAnimator->PlayAnimation(L"PlayerLeftRush", false);
			}
			else
			{
				velocity.x = 850.0f;
				mAnimator->PlayAnimation(L"PlayerRightRush", false);
			}
			mState = eState::Rush;
			mRigidbody->SetVelocity(velocity);
		}

		// 콤보 데스폴트
		if (Input::GetKeyDown(eKeyCode::F) || Input::GetKeyPressed(eKeyCode::F))
		{
			mbInvincible = true;
			ComboDeathFaultPlayer* comboDeath = new ComboDeathFaultPlayer(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, comboDeath);
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftComboDeathFault", false);
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightComboDeathFault", false);
			}
			mState = eState::ComboDeathFault;
			mRigidbody->SetVelocity(velocity);
		}

		// 좌우 이동중 점프
		if ((Input::GetKeyPressed(eKeyCode::Right) && Input::GetKeyDown(eKeyCode::Jump)) ||
			(Input::GetKeyPressed(eKeyCode::Right) && Input::GetKeyPressed(eKeyCode::Jump)))
		{
			mRigidbody->SetGround(false);
			velocity.x = 350.0f;
			velocity.y = -680.0f;
			mState = eState::Jump;
			mAnimator->PlayAnimation(L"PlayerRightJump", true);
			mJumpSound->Play(false);
		}
		else if ((Input::GetKeyPressed(eKeyCode::Left) && Input::GetKeyDown(eKeyCode::Jump)) ||
			(Input::GetKeyPressed(eKeyCode::Left) && Input::GetKeyPressed(eKeyCode::Jump)))
		{
			mRigidbody->SetGround(false);
			velocity.x = -350.0f;
			velocity.y = -680.0f;
			mState = eState::Jump;
			mAnimator->PlayAnimation(L"PlayerLeftJump", true);
			mJumpSound->Play(false);
		}

		// 좌우 키 입력 중 반대 방향 키 입력 시 Idle상태로 전환
		if (Input::GetKeyPressed(eKeyCode::Right) && Input::GetKeyDown(eKeyCode::Left))
		{
			mAnimator->PlayAnimation(L"PlayerRightIdle", true);
			mState = eState::Idle;
			velocity = math::Vector2(0.0f, 0.0f);
		}
		if (Input::GetKeyPressed(eKeyCode::Left) && Input::GetKeyDown(eKeyCode::Right))
		{
			mAnimator->PlayAnimation(L"PlayerLeftIdle", true);
			mState = eState::Idle;
			velocity = math::Vector2(0.0f, 0.0f);
		}

		// 키 안누른 상태
		if ((!Input::GetKeyPressed(eKeyCode::Up)) &&
			(!Input::GetKeyPressed(eKeyCode::Left)) &&
			(!Input::GetKeyPressed(eKeyCode::Down)) &&
			!Input::GetKeyPressed(eKeyCode::Right))
		{
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftIdle", true);
				mState = eState::Idle;
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightIdle", true);
				mState = eState::Idle;
			}
			mRigidbody->SetVelocityX(0.0f);
		}

		mTransform->SetPosition(pos);
		mRigidbody->SetVelocity(velocity);
	}

	void Player::Down()
	{
		enums::eMoveDir playerDir = mTransform->GetMoveDir();
		math::Vector2 velocity = mRigidbody->GetVelocity();

		if (playerDir == enums::eMoveDir::Right)
		{
			mAnimator->PlayAnimation(L"PlayerRightDown", true);
		}
		else if (playerDir == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"PlayerLeftDown", true);
		}


		// 밑에 누르고 좌우 이동키 누르면 방향에 따라 move
		if (Input::GetKeyPressed(eKeyCode::Down) && Input::GetKeyDown(eKeyCode::Right))
		{
			mTransform->SetMoveDir(enums::eMoveDir::Right);
			mAnimator->PlayAnimation(L"PlayerRightMove", true);
			mState = eState::Move;
		}
		else if (Input::GetKeyPressed(eKeyCode::Down) && Input::GetKeyDown(eKeyCode::Left))
		{
			mTransform->SetMoveDir(enums::eMoveDir::Left);
			mAnimator->PlayAnimation(L"PlayerLeftMove", true);
			mState = eState::Move;
		}

		if (Input::GetKeyPressed(eKeyCode::Down) && Input::GetKeyDown(eKeyCode::Jump))
		{
			mRigidbody->SetGround(false);
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftJump", true);
				mState = eState::Fall;
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightJump", true);
				mState = eState::Fall;
			}
			mJumpSound->Play(false);
		}


		// 밑에 키 Up상태면 다시 Idle상태로 돌아오게 만듬
		if (Input::GetKeyUp(eKeyCode::Down))
		{
			if (playerDir == enums::eMoveDir::Left)
			{
				mTransform->SetMoveDir(enums::eMoveDir::Left);
				mAnimator->PlayAnimation(L"PlayerLeftIdle", true);
				mState = eState::Idle;
			}
			else
			{
				mTransform->SetMoveDir(enums::eMoveDir::Right);
				mAnimator->PlayAnimation(L"PlayerRightIdle", true);
				mState = eState::Idle;
			}

		}
	}

	void Player::Rope()
	{
		math::Vector2 pos = mTransform->GetPosition();
		enums::eMoveDir playerDir = mTransform->GetMoveDir();
		math::Vector2 velocity = mRigidbody->GetVelocity();
		mRigidbody->SetGround(false);

		// 로프 상태에 오면 더블점프 초기화
		mbDoubleJump = false;
		if (Input::GetKeyPressed(eKeyCode::Up) || Input::GetKeyDown(eKeyCode::Up))
		{
			mAnimator->PlayAnimation(L"PlayerRopeMove", true);
			pos.y -= 200.0f * Time::GetDeltaTime();
		}
		else if (Input::GetKeyPressed(eKeyCode::Down) || Input::GetKeyDown(eKeyCode::Down))
		{
			mAnimator->PlayAnimation(L"PlayerRopeMove", true);
			pos.y += 200.0f * Time::GetDeltaTime();
		}


		if (Input::GetKeyPressed(eKeyCode::Left) && Input::GetKeyDown(eKeyCode::Jump))
		{
			mAnimator->PlayAnimation(L"PlayerLeftJump", true);
			velocity.x = -300.0f;
			velocity.y = -200.0f;
			mState = eState::Jump;
			mRigidbody->SetVelocity(velocity);
			mJumpSound->Play(false);
		}
		if (Input::GetKeyPressed(eKeyCode::Right) && Input::GetKeyDown(eKeyCode::Jump))
		{
			mAnimator->PlayAnimation(L"PlayerRightJump", true);
			velocity.x = 300.0f;
			velocity.y = -200.0f;
			mState = eState::Jump;
			mRigidbody->SetVelocity(velocity);
			mJumpSound->Play(false);
		}
		mTransform->SetPosition(pos);

	}


	void Player::Attack()
	{
		enums::eMoveDir playerDir = mTransform->GetMoveDir();

		// 이동중 공격
		if (Input::GetKeyPressed(eKeyCode::Right) && Input::GetKeyDown(eKeyCode::Ctrl))
		{
			mAnimator->PlayAnimation(L"PlayerRightAttack", false);
		}

		if (Input::GetKeyPressed(eKeyCode::Left) && Input::GetKeyDown(eKeyCode::Ctrl))
		{
			mAnimator->PlayAnimation(L"PlayerLeftAttack", false);
		}

		if (Input::GetKeyPressed(eKeyCode::Jump) || Input::GetKeyDown(eKeyCode::Jump))
		{
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftAttack", false);
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightAttack", false);
			}
			mJumpSound->Play(false);
		}

		bool IsComplete = mAnimator->IsActiveAnimationComplete();
		if (IsComplete)
		{
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftIdle", true);
				mState = eState::Idle;
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightIdle", true);
				mState = eState::Idle;
			}
		}
	}

	void Player::Jump()
	{
		enums::eMoveDir playerDir = mTransform->GetMoveDir();
		math::Vector2 velocity = mRigidbody->GetVelocity();


		// 점프중 좌우 움직이게 
		if (Input::GetKeyDown(eKeyCode::Right) || Input::GetKeyPressed(eKeyCode::Right))
		{
			mAnimator->PlayAnimation(L"PlayerRightJump", true);
			mTransform->SetMoveDir(enums::eMoveDir::Right);

		}
		if (Input::GetKeyDown(eKeyCode::Left) || Input::GetKeyPressed(eKeyCode::Left))
		{
			mAnimator->PlayAnimation(L"PlayerLeftJump", true);
			mTransform->SetMoveDir(enums::eMoveDir::Left);

		}

		if (mbRopeState && Input::GetKeyPressed(eKeyCode::Up))
		{
			mAnimator->PlayAnimation(L"PlayerRopeMove", true);
			mState = eState::Rope;
		}

		// 점프 + 공격
		if (Input::GetKeyDown(eKeyCode::Ctrl) || Input::GetKeyPressed(eKeyCode::Ctrl))
		{
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftAttack", false);
				PlayerAttack* playerAttack = new PlayerAttack(this);
				object::ActiveSceneAddGameObject(enums::eLayerType::Effect, playerAttack);
				mState = eState::JumpAttack;
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightAttack", false);
				PlayerAttack* playerAttack = new PlayerAttack(this);
				object::ActiveSceneAddGameObject(enums::eLayerType::Effect, playerAttack);
				mState = eState::JumpAttack;
			}
		}


		// mbDoubleJump 가 false일때 점프를 누르면 더블점프
		if (false == mbDoubleJump && Input::GetKeyDown(eKeyCode::Jump))
		{
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftJump", true);
				velocity.x = -700.0f;
				velocity.y = -300.0f;
				mState = eState::DoubleJump;
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightJump", true);
				velocity.x = 700.0f;
				velocity.y = -300.0f;
				mState = eState::DoubleJump;
			}
			WarriorLeap* warriorLeap = new WarriorLeap(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, warriorLeap);
			mRigidbody->SetVelocity(velocity);
		}


		// 포물선에서 내려오는 상태면 떨어지는상태로 변경해준다
		if (velocity.y >= 0 && mState != eState::Rope)
		{
			mState = eState::Fall;
		}


		//mRigidbody->SetVelocity(velocity);
	}

	void Player::JumpAttack()
	{
		enums::eMoveDir playerDir = mTransform->GetMoveDir();

		bool bCheck = mAnimator->IsActiveAnimationComplete();

		if (bCheck)
		{
			mState = eState::Fall;
		}
	}

	void Player::DoubleJump()
	{
		math::Vector2 velocity = mRigidbody->GetVelocity();
		enums::eMoveDir playerDir = mTransform->GetMoveDir();

		// 더블 점프를 사용했기때문에 
		// true로 변경
		mbDoubleJump = true;

		if (velocity.y >= 0 && mState != eState::Rope)
		{
			mState = eState::Fall;
		}

		if (mbRopeState && Input::GetKeyPressed(eKeyCode::Up))
		{
			mAnimator->PlayAnimation(L"PlayerRopeMove", true);
			mState = eState::Rope;
		}
	}

	void Player::Hit()
	{
		math::Vector2 velocity = mRigidbody->GetVelocity();
		enums::eMoveDir playerDir = mTransform->GetMoveDir();

		mbDoubleJump = false;
		if (velocity.y > 0.0f)
		{
			velocity.x = 0.0f;
		}

		if (mbInvincible)
		{
			if (mhitDelay >= 1.5f)
			{
				mbInvincible = false;
				mhitDelay = 0.0f;
				mState = eState::Idle;
			}
		}
		else
		{
			mState = eState::Idle;
		}

		if (playerDir == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"PlayerLeftHit", true);
		}
		else if (playerDir == enums::eMoveDir::Right)
		{
			mAnimator->PlayAnimation(L"PlayerRightHit", true);
		}

		if (Input::GetKeyDown(eKeyCode::Left) || Input::GetKeyPressed(eKeyCode::Left))
		{
			mAnimator->PlayAnimation(L"PlayerLeftMove", true);
			mState = eState::Move;
		}
		if (Input::GetKeyDown(eKeyCode::Right) || Input::GetKeyPressed(eKeyCode::Right))
		{
			mAnimator->PlayAnimation(L"PlayerRightMove", true);
			mState = eState::Move;
		}

		if (Input::GetKeyDown(eKeyCode::Ctrl) || Input::GetKeyPressed(eKeyCode::Ctrl))
		{
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftAttack", false);
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightAttack", false);
			}
			PlayerAttack* playerAttack = new PlayerAttack(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, playerAttack);
			mState = eState::Attack;
		}

		// 레이징 블로우
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyPressed(eKeyCode::A))
		{
			Raisingblow* raisingBlow = new Raisingblow(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, raisingBlow);
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftRaisingBlow", false);
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightRaisingBlow", false);
			}
			mState = eState::RaisingBlow;
		}

		// 어퍼 차지
		if (Input::GetKeyDown(eKeyCode::S) || Input::GetKeyPressed(eKeyCode::S))
		{
			mRigidbody->SetGround(false);
			mState = eState::UpperCharge;
			UpperCharge* upperCharge = new UpperCharge(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, upperCharge);
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftUpperCharge", false);
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightUpperCharge", false);
			}
			velocity.y = -1310.0f;
			mRigidbody->SetVelocityY(velocity.y);
		}

		// 돌진
		if (Input::GetKeyDown(eKeyCode::D) || Input::GetKeyPressed(eKeyCode::D))
		{
			Rush* rush = new Rush(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, rush);
			if (playerDir == enums::eMoveDir::Left)
			{
				velocity.x = -900.0f;
				mAnimator->PlayAnimation(L"PlayerLeftRush", false);
			}
			else
			{
				velocity.x = 900.0f;
				mAnimator->PlayAnimation(L"PlayerRightRush", false);
			}
			mState = eState::Rush;
			mRigidbody->SetVelocity(velocity);
		}

		// 콤보 데스폴트
		if (Input::GetKeyDown(eKeyCode::F) || Input::GetKeyPressed(eKeyCode::F))
		{
			mbInvincible = true;
			ComboDeathFaultPlayer* comboDeath = new ComboDeathFaultPlayer(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, comboDeath);
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftComboDeathFault", false);
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightComboDeathFault", false);
			}
			mState = eState::ComboDeathFault;
			mRigidbody->SetVelocity(velocity);
		}

		if (Input::GetKeyDown(eKeyCode::Jump) || Input::GetKeyPressed(eKeyCode::Jump))
		{
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftJump", false);
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightJump", false);
			}
			mState = eState::Jump;
		}

		if (Input::GetKeyDown(eKeyCode::Down) || Input::GetKeyPressed(eKeyCode::Down))
		{
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftDown", false);
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightDown", false);
			}
			mState = eState::Down;
		}

		if (mInfo->mHp <= 0)
		{
			mInfo->mExp /= 2.0f;
			mAnimator->PlayAnimation(L"PlayerDead", false);
			mPlayerDeadSound->Play(false);
			mState = eState::Death;
		}
		mRigidbody->SetVelocity(velocity);
	}

	void Player::Death()
	{
		mRigidbody->SetVelocity(0.0f);
		mbBuffCheck = false;
		if (Input::GetKeyDown(eKeyCode::R))
		{
			enums::eMoveDir playerDir = mTransform->GetMoveDir();
			mTransform->SetPosition(mTransform->GetPositionX(), mTransform->GetPositionY() - 400.0f);
			mInfo->mHp = mInfo->mMaxHp;
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftJump", false);
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightJump", false);
			}
			mState = eState::Fall;
		}

	}


	void Player::RaisingBlow()
	{
		enums::eMoveDir playerDir = mTransform->GetMoveDir();
		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (bCheck)
		{
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftIdle", true);
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightIdle", true);
			}
			mState = eState::Idle;
		}
		bool bGround = mRigidbody->GetGround();
	}

	void Player::Uppercharge()
	{
		enums::eMoveDir playerDir = mTransform->GetMoveDir();
		math::Vector2 velocity = mRigidbody->GetVelocity();
		bool bCheck = mAnimator->IsActiveAnimationComplete();
		// 애니메이션 재생이 끝낫으면
		if (bCheck)
		{
			bool bGround = mRigidbody->GetGround();

			if (bGround)
			{
				if (playerDir == enums::eMoveDir::Left)
				{
					mAnimator->PlayAnimation(L"PlayerLeftIdle", true);
				}
				else
				{
					mAnimator->PlayAnimation(L"PlayerRightIdle", true);
				}
				mState = eState::Idle;
				mRigidbody->SetVelocityX(0.0f);
			}
			else if (mbRopeState && Input::GetKeyPressed(eKeyCode::Up))
			{
				mAnimator->PlayAnimation(L"PlayerRopeMove", true);
				mState = eState::Rope;
			}
			else
			{
				if (playerDir == enums::eMoveDir::Left)
				{
					mAnimator->PlayAnimation(L"PlayerLeftJump", true);
				}
				else
				{
					mAnimator->PlayAnimation(L"PlayerRightJump", true);
				}
				mState = eState::Jump;
			}
		}

		if (false == mbDoubleJump && Input::GetKeyDown(eKeyCode::Jump))
		{
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftJump", true);
				velocity.x = -700.0f;
				velocity.y = -300.0f;
				mState = eState::DoubleJump;
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightJump", true);
				velocity.x = 700.0f;
				velocity.y = -300.0f;
				mState = eState::DoubleJump;
			}
			WarriorLeap* warriorLeap = new WarriorLeap(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, warriorLeap);
			mRigidbody->SetVelocity(velocity);
		}

	}

	void Player::PlayerRush()
	{
		bool bCheck = mAnimator->IsActiveAnimationComplete();
		enums::eMoveDir playerDir = mTransform->GetMoveDir();
		if (bCheck)
		{
			mRigidbody->SetVelocityX(0.0f);
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftIdle", true);
				mState = eState::Idle;
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightIdle", true);
				mState = eState::Idle;
			}
		}
	}

	void Player::ComboDeathFault()
	{
		enums::eMoveDir playerDir = mTransform->GetMoveDir();
		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (bCheck)
		{
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftIdle", true);
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightIdle", true);
			}
			mState = eState::Idle;
		}
		bool bGround = mRigidbody->GetGround();
		if (bGround)
		{
			mRigidbody->SetVelocityX(0.0f);
		}
	}

	void Player::ComboSynergyBody()
	{
		enums::eMoveDir playerDir = mTransform->GetMoveDir();
		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (bCheck)
		{
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftIdle", true);
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightIdle", true);
			}
			mState = eState::Idle;
		}
	}

	void Player::PlayerBuff()
	{
		enums::eMoveDir playerDir = mTransform->GetMoveDir();
		if (mBuff != nullptr)
		{
			bool bCheck = mBuff->GetComponent<Animator>()->IsActiveAnimationComplete();
			if (bCheck)
			{
				if (playerDir == enums::eMoveDir::Left)
				{
					mAnimator->PlayAnimation(L"PlayerLeftIdle", true);
				}
				else
				{
					mAnimator->PlayAnimation(L"PlayerRightIdle", true);
				}
			}
		}
		mState = eState::Idle;

	}

	void Player::Fall()
	{
		enums::eMoveDir playerDir = mTransform->GetMoveDir();
		math::Vector2 velocity = mRigidbody->GetVelocity();

		// fall상태 중 좌우 방향키 입력
		if (Input::GetKeyDown(eKeyCode::Right))
		{
			mAnimator->PlayAnimation(L"PlayerRightJump", true);
			mTransform->SetMoveDir(enums::eMoveDir::Right);

		}
		if (Input::GetKeyDown(eKeyCode::Left))
		{
			mAnimator->PlayAnimation(L"PlayerLeftJump", true);
			mTransform->SetMoveDir(enums::eMoveDir::Left);

		}

		// mbDoubleJump 가 false일때 점프를 누르면
		if (false == mbDoubleJump && Input::GetKeyDown(eKeyCode::Jump))
		{
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftJump", true);
				velocity.x = -600.0f;
				velocity.y = -300.0f;
				mState = eState::DoubleJump;
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightJump", true);
				velocity.x = 600.0f;
				velocity.y = -300.0f;
				mState = eState::DoubleJump;
			}
			WarriorLeap* warriorLeap = new WarriorLeap(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, warriorLeap);
			mRigidbody->SetVelocity(velocity);
		}


		// 땅에 닿은 상태
		bool bGround = mRigidbody->GetGround();
		if (bGround)
		{
			mRigidbody->SetVelocityX(0.0f);
			// 땅에 닿으면 더블점프 초기화
			mbDoubleJump = false;
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftIdle", true);
				mState = eState::Idle;
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightIdle", true);
				mState = eState::Idle;
			}
		}

		if (mbRopeState && Input::GetKeyPressed(eKeyCode::Up))
		{
			mAnimator->PlayAnimation(L"PlayerRopeMove", true);
			mState = eState::Rope;
		}

		if (bGround && Input::GetKeyPressed(eKeyCode::Left))
		{
			mAnimator->PlayAnimation(L"PlayerLeftMove", true);
			mState = eState::Move;
		}
		else if (bGround && Input::GetKeyPressed(eKeyCode::Right))
		{
			mAnimator->PlayAnimation(L"PlayerRightMove", true);
			mState = eState::Move;
		}

		// 점프 + 공격
		if (Input::GetKeyDown(eKeyCode::Ctrl) || Input::GetKeyPressed(eKeyCode::Ctrl))
		{
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftAttack", false);
				mState = eState::JumpAttack;
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightAttack", false);
				mState = eState::JumpAttack;
			}
		}

		// 레이징 블로우
		if (bGround == false)
		{

			if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyPressed(eKeyCode::A))
			{
				Raisingblow* raisingBlow = new Raisingblow(this);
				object::ActiveSceneAddGameObject(enums::eLayerType::Effect, raisingBlow);
				if (playerDir == enums::eMoveDir::Left)
				{
					mAnimator->PlayAnimation(L"PlayerLeftRaisingBlow", false);
				}
				else
				{
					mAnimator->PlayAnimation(L"PlayerRightRaisingBlow", false);
				}
				mState = eState::RaisingBlow;
			}
		}
	}

	void Player::OnCollisionEnter(Collider* _other)
	{
		Monsters* monsters = dynamic_cast<Monsters*>(_other->GetOwner());
		if (nullptr != monsters && mbInvincible == false)
		{
			float monstersPosX = monsters->GetPositionX();
			float playerPosX = mTransform->GetPositionX();
			math::Vector2 velocity = mRigidbody->GetVelocity();
			if (velocity.y <= 0.0f && mbKnockBackCheck)
			{
				if (playerPosX <= monstersPosX &&
					mState != eState::Rush &&
					mState != eState::UpperCharge)
				{
					mRigidbody->SetVelocityX(-200.0f);
				}
				else
				{
					mRigidbody->SetVelocityX(200.0f);
				}
				mbKnockBackCheck = false;
			}
			mCollider->SetCollisionType(true);
		}
	}
	void Player::OnCollisionStay(Collider* _other)
	{
		Monsters* monsters = dynamic_cast<Monsters*>(_other->GetOwner());
		if (nullptr != monsters && mbInvincible == false)
		{
			mCollider->SetCollisionType(true);
		}
	}
	void Player::OnCollisionExit(Collider* _other)
	{
		mCollider->SetCollisionType(false);
	}

	void Player::PlayLevelUI()
	{
		int temp = mInfo->mLevel;
		// 플레이어 레벨의 Len구하기
		std::string numStr = std::to_string(temp);
		int levelLen = static_cast<int>(numStr.length());

		// 데미지를 뒤에부터 하나씩 받기위해 만든 배열
		for (size_t i = 0; i < levelLen; ++i)
		{
			int remainder = temp % 10;
			mLevelArr.push_back(remainder);
			temp /= 10;
		}

		// 배열 다시 뒤집어서 정렬
		reverse(mLevelArr.begin(), mLevelArr.end());

		SceneManager::GetLevel_1()->PlayLevelAnimation(mLevelArr[0]);
		SceneManager::GetLevel_2()->PlayLevelAnimation(mLevelArr[1]);
		SceneManager::GetLevel_3()->PlayLevelAnimation(mLevelArr[2]);
	}

	void Player::Stun()
	{
		enums::eMoveDir playerDir = mTransform->GetMoveDir();
		if (playerDir == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"PlayerLeftHit", false);
		}
		else
		{
			mAnimator->PlayAnimation(L"PlayerRightHit", false);
		}

		mStunDelay += Time::GetDeltaTime();
		if (mStunDelay >= 2.5f)
		{
			mState = eState::Idle;
			mbStunCheck = false;
			mStunDelay = 0.0f;
		}

	}

	void Player::PlayerSkillLoad()
	{
		// 레이징 블로우
		ResourceManager::Load<Texture>(L"LeftRaisingblow"
			, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\Raisingblow\\Left\\LeftRaisingblow.png");
		ResourceManager::Load<Texture>(L"RightRaisingblow"
			, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\Raisingblow\\Right\\RightRaisingblow.png");

		// 어퍼 차지
		ResourceManager::Load<Texture>(L"LeftUpperCharge"
			, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\UpperCharge\\Left\\Left_UpperCharge.png");
		ResourceManager::Load<Texture>(L"RightUpperCharge"
			, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\UpperCharge\\Right\\Right_UpperCharge.png");

		// 돌진
		ResourceManager::Load<Texture>(L"LeftRush"
			, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\Rush\\Left\\Left_Rush.png");
		ResourceManager::Load<Texture>(L"RightRush"
			, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\Rush\\Right\\Right_Rush.png");

		// 콤보 데스폴트
		ResourceManager::Load<Texture>(L"LeftComboDeathFault"
			, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\ComboDeathFault\\ComboDeathFault_Player\\Left\\Player_Left_ComboDeathFault.png");
		ResourceManager::Load<Texture>(L"RightComboDeathFault"
			, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\ComboDeathFault\\ComboDeathFault_Player\\Right\\Player_Right_ComboDeathFault.png");
		// 콤보 데스폴트 스크린
		ResourceManager::Load<Texture>(L"ComboDeathFaultLeftScreen"
			, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\ComboDeathFault\\ComboDeathFault_Screen\\Left\\Left_ComboDeathFault_Screen.png");
		ResourceManager::Load<Texture>(L"ComboDeathFaultRightScreen"
			, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\ComboDeathFault\\ComboDeathFault_Screen\\Right\\Right_ComboDeathFault_Screen.png");


		// 콤보 시너지 바디
		ResourceManager::Load<Texture>(L"ComboSynergyBody"
			, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\ComboSynergy\\Body\\ComboSynergy_Body.png");

		// 콤보 시너지 이펙트
		ResourceManager::Load<Texture>(L"ComboSynergyEffect_0"
			, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\ComboSynergy\\Effect\\ComboSynergy_000.png");

		ResourceManager::Load<Texture>(L"ComboSynergyEffect_1"
			, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\ComboSynergy\\Effect\\ComboSynergy_001.png");

		ResourceManager::Load<Texture>(L"ComboSynergyEffect_2"
			, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\ComboSynergy\\Effect\\ComboSynergy_002.png");

		ResourceManager::Load<Texture>(L"ComboSynergyEffect_3"
			, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\ComboSynergy\\Effect\\ComboSynergy_003.png");

		ResourceManager::Load<Texture>(L"ComboSynergyEffect_4"
			, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\ComboSynergy\\Effect\\ComboSynergy_004.png");

		ResourceManager::Load<Texture>(L"ComboSynergyIcon"
			, L"..\\Resources\\Maple\\Image\\UI\\BuffUI\\ComboSynergyIcon.png");


		// 플레이어 데미지 스킨
		ResourceManager::Load<Texture>(L"PlayerDamage_0"
			, L"..\\Resources\\Maple\\Image\\UI\\DamageSkin\\Player\\Player_0.png");
		
		ResourceManager::Load<Texture>(L"PlayerDamage_1"
			, L"..\\Resources\\Maple\\Image\\UI\\DamageSkin\\Player\\Player_1.png");
		

		ResourceManager::Load<Texture>(L"PlayerDamage_2"
			, L"..\\Resources\\Maple\\Image\\UI\\DamageSkin\\Player\\Player_2.png");
		

		ResourceManager::Load<Texture>(L"PlayerDamage_3"
			, L"..\\Resources\\Maple\\Image\\UI\\DamageSkin\\Player\\Player_3.png");
	
		ResourceManager::Load<Texture>(L"PlayerDamage_4"
			, L"..\\Resources\\Maple\\Image\\UI\\DamageSkin\\Player\\Player_4.png");
		
		ResourceManager::Load<Texture>(L"PlayerDamage_5"
			, L"..\\Resources\\Maple\\Image\\UI\\DamageSkin\\Player\\Player_5.png");
		
		ResourceManager::Load<Texture>(L"PlayerDamage_6"
			, L"..\\Resources\\Maple\\Image\\UI\\DamageSkin\\Player\\Player_6.png");

		ResourceManager::Load<Texture>(L"PlayerDamage_7"
			, L"..\\Resources\\Maple\\Image\\UI\\DamageSkin\\Player\\Player_7.png");

		ResourceManager::Load<Texture>(L"PlayerDamage_8"
			, L"..\\Resources\\Maple\\Image\\UI\\DamageSkin\\Player\\Player_8.png");

		 ResourceManager::Load<Texture>(L"PlayerDamage_9"
			, L"..\\Resources\\Maple\\Image\\UI\\DamageSkin\\Player\\Player_9.png");
		

	}

}
