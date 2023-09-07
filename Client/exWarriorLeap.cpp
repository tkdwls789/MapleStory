#include "exWarriorLeap.h"
#include "exTexture.h"
#include "exResourceManager.h"
#include "exAnimator.h"
#include "exTransform.h"
#include "exCollider.h"
#include "exTime.h"
#include "exPlayer.h"
#include "exSceneManager.h"
#include "exCollisionManager.h"
#include "exObject.h"
#include "exSound.h"

namespace ex
{
	WarriorLeap::WarriorLeap(GameObject* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
		, mWarriorLeap(nullptr)
	{
		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mCollider = AddComponent<Collider>();


		//// png
		Texture* image = ResourceManager::Load<Texture>(L"LeftWarriorLeap"
			, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\WarriorLeap\\Left\\LeftWarriorLeap.png");

		//Texture* image = ResourceManager::Load<Texture>(L"LeftWarriorLeap"
		//		, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\WarriorLeap\\Left\\LeftWarriorLeap.bmp");

		mAnimator->CreateAnimation(L"LeftWarriorLeap", image, math::Vector2(0.0f, 0.0f), math::Vector2(352.0f, 216.0f)
			, math::Vector2(352.0f, 216.0f), 7, math::Vector2(0), 0.035f);

		// png
		image = ResourceManager::Load<Texture>(L"RightWarriorLeap"
			, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\WarriorLeap\\Right\\RightWarriorLeap.png");
		
		//image = ResourceManager::Load<Texture>(L"RightWarriorLeap"
		//	, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\WarriorLeap\\Right\\RightWarriorLeap.bmp");

		mAnimator->CreateAnimation(L"RightWarriorLeap", image, math::Vector2(2464.0f, 0.0f), math::Vector2(352.0f, 216.0f)
			, math::Vector2(-352.0f, 0.0f), 7, math::Vector2(0), 0.035f);

		mAnimator->SetScale(math::Vector2(0.65f, 0.65f));
		enums::eMoveDir playerDir = _owner->GetTransform()->GetMoveDir();
		math::Vector2 playerPos = _owner->GetPosition();

		if (playerDir == enums::eMoveDir::Left)
		{
			mTransform->SetPosition(math::Vector2(playerPos.x + 100.0f, playerPos.y + 20.0f));
			mAnimator->PlayAnimation(L"LeftWarriorLeap", false);
		}
		else
		{
			mTransform->SetPosition(math::Vector2(playerPos.x - 120.0f, playerPos.y + 20.0f));
			mAnimator->PlayAnimation(L"RightWarriorLeap", false);
		}

		mWarriorLeap = ResourceManager::Load<Sound>(L"WarriorLeapSound", L"..\\Resources\\Maple\\Sound\\Skill\\WarriorLeap.wav");
		mWarriorLeap->Play(false);
	}

	WarriorLeap::~WarriorLeap()
	{
	}

	void WarriorLeap::Initialize()
	{
	}

	void WarriorLeap::Update()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
		GameObject::Update();
	}

	void WarriorLeap::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void WarriorLeap::OnCollisionEnter(Collider* _other)
	{
	}

	void WarriorLeap::OnCollisionStay(Collider* _other)
	{
	}

	void WarriorLeap::OnCollisionExit(Collider* _other)
	{
	}
}