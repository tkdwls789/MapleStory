#include "exVonLeonTeleportAfter.h"
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
#include "exDamageManager.h"
#include "exVonLeon.h"
#include "exSound.h"


namespace ex
{
	VonLeonTeleportAfter::VonLeonTeleportAfter(VonLeon* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
		, mVonLeonTeleportAfter_Info{}
	{

		mAnimator = mOwner->GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mCollider = AddComponent<Collider>();
		mRigidbody = mOwner->GetComponent<Rigidbody>();

		float playerPosX = SceneManager::GetPlayer()->GetPositionX();
		float monsterPosX = mOwner->GetPositionX();
		if (playerPosX <= monsterPosX)
		{
			mAnimator->PlayAnimation(L"VonLeonLeftTeleportAfter", false);
		}
		else
		{
			mAnimator->PlayAnimation(L"VonLeonRightTeleportAfter", false);
		}

		mRigidbody->SetGround(true);
		mOwner->SetPosition(playerPosX, 360.0f);
	}

	VonLeonTeleportAfter::~VonLeonTeleportAfter()
	{
	}

	void VonLeonTeleportAfter::Initialize()
	{
	}

	void VonLeonTeleportAfter::Update()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			mOwner->GetComponent<Collider>()->SetSize(math::Vector2(400.0f, 520.0f));
			Destroy(this);
		}

		GameObject::Update();
	}

	void VonLeonTeleportAfter::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void VonLeonTeleportAfter::OnCollisionEnter(Collider* _other)
	{
	}

	void VonLeonTeleportAfter::OnCollisionStay(Collider* _other)
	{
	}

	void VonLeonTeleportAfter::OnCollisionExit(Collider* _other)
	{
	}
}