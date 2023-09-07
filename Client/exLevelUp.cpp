#include "exLevelUp.h"
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
	LevelUp::LevelUp(GameObject* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
		, mLevelUpSound(nullptr)
	{
		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mCollider = AddComponent<Collider>();

		mAnimator->CreateAnimationFolder(L"PlayerLevelUp",
			L"..\\Resources\\Maple\\Image\\Player2\\LevelUp");
		mAnimator->SetAffectedCamera(true);
		mAnimator->SetScale(math::Vector2(1.3f, 1.3f));
		mAnimator->PlayAnimation(L"PlayerLevelUp", false);

		mLevelUpSound = ResourceManager::Load<Sound>(L"PlayerLevelUpSound",
			L"..\\Resources\\Maple\\Sound\\Player\\Player_LevelUp.wav");
		mLevelUpSound->Play(false);

	}

	LevelUp::~LevelUp()
	{
	}

	void LevelUp::Initialize()
	{
	}

	void LevelUp::Update()
	{
		math::Vector2 playerPos = SceneManager::GetPlayer()->GetPosition();
		mTransform->SetPosition(playerPos.x, playerPos.y - 210.0f);

		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
		GameObject::Update();
	}

	void LevelUp::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void LevelUp::OnCollisionEnter(Collider* _other)
	{
	}

	void LevelUp::OnCollisionStay(Collider* _other)
	{
	}

	void LevelUp::OnCollisionExit(Collider* _other)
	{
	}
}