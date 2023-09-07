#include "exRaisingblowHit.h"
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
	RaisingblowHit::RaisingblowHit(GameObject* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
		, mRaisingBlowHitSound(nullptr)
	{
		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
	
		mAnimator->CreateAnimationFolder(L"RaisingblowHit"
			, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\Raisingblow\\Hit");

		math::Vector2 pos = _owner->GetPosition();

		mAnimator->SetScale(math::Vector2(0.5f, 0.5f));
		mTransform->SetPosition(math::Vector2(pos));
		mAnimator->PlayAnimation(L"RaisingblowHit", false);

		mRaisingBlowHitSound = ResourceManager::Load<Sound>(L"RaisingBlowHit", L"..\\Resources\\Maple\\Sound\\Skill\\Ragingblow_Hit.wav");
		mRaisingBlowHitSound->Play(false);
	}

	RaisingblowHit::~RaisingblowHit()
	{
	}

	void RaisingblowHit::Initialize()
	{
	}

	void RaisingblowHit::Update()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
		GameObject::Update();
	}

	void RaisingblowHit::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void RaisingblowHit::OnCollisionEnter(Collider* _other)
	{
	}

	void RaisingblowHit::OnCollisionStay(Collider* _other)
	{

	}

	void RaisingblowHit::OnCollisionExit(Collider* _other)
	{
	}
}