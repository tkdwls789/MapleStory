#include "exComboDeathFaultHit.h"
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
#include "exAnimation.h"
#include "exMonsters.h"
#include "exSound.h"

namespace ex
{
	ComboDeathFaultHit::ComboDeathFaultHit(GameObject* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
		, mComboDeathFaultHitSound(nullptr)
	{
		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();

		mAnimator->CreateAnimationFolder(L"ComboDeathFaultHit"
			, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\ComboDeathFault\\Hit");

		math::Vector2 pos = _owner->GetPosition();

		mAnimator->SetScale(math::Vector2(1.0f, 1.0f));
		mTransform->SetPosition(math::Vector2(pos));
		mAnimator->PlayAnimation(L"ComboDeathFaultHit", false);

		mComboDeathFaultHitSound = ResourceManager::Load<Sound>(L"ComboDeathFaultHitSound", L"..\\Resources\\Maple\\Sound\\Skill\\ComboDeathFault_Hit.wav");
		mComboDeathFaultHitSound->Play(false);
	}

	ComboDeathFaultHit::~ComboDeathFaultHit()
	{
	}

	void ComboDeathFaultHit::Initialize()
	{
	}

	void ComboDeathFaultHit::Update()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
		GameObject::Update();
	}

	void ComboDeathFaultHit::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void ComboDeathFaultHit::OnCollisionEnter(Collider* _other)
	{
	}

	void ComboDeathFaultHit::OnCollisionStay(Collider* _other)
	{

	}

	void ComboDeathFaultHit::OnCollisionExit(Collider* _other)
	{
	}
}