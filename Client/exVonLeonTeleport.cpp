#include "exVonLeonTeleport.h"
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
#include "exVonLeonTeleportAfter.h"


namespace ex
{
	VonLeonTeleport::VonLeonTeleport(VonLeon* _owner)
		: EffectManger(_owner)
		, mVonLeon(_owner)
		, mVonLeonTeleport_Damege(0)
		, mVonLeonTeleport_Sound(nullptr)
		, mVonLeonTeleport_Info{}
	{
		mVonLeonTeleport_Sound = ResourceManager::Load<Sound>(L"VonLeonTeleport_Sound", L"..\\Resources\\Maple\\Sound\\Monster\\VonLeon\\VonLeon_Teleport.wav");
		mVonLeonTeleport_Sound->Play(false);

		mAnimator = mVonLeon->GetComponent<Animator>();
		mTransform = mVonLeon->GetComponent<Transform>();
		mCollider = mVonLeon->GetComponent<Collider>();
		mRigidbody = mVonLeon->GetComponent<Rigidbody>();

		mCollider->SetSize(0.0f, 0.0f);
		mRigidbody->SetGround(true);
		mVonLeon->GetComponent<Collider>()->SetSize(math::Vector2(0.0f, 0.0f));
	}

	VonLeonTeleport::~VonLeonTeleport()
	{
	}

	void VonLeonTeleport::Initialize()
	{
	}

	void VonLeonTeleport::Update()
	{
		mTransform->SetPositionY(360.0f);

		if (mAnimator->IsActiveAnimationComplete())
		{
			VonLeonTeleportAfter* vonLeonTeleportAfter = new VonLeonTeleportAfter(mVonLeon);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, vonLeonTeleportAfter);
			Destroy(this);
		}

		GameObject::Update();
	}

	void VonLeonTeleport::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void VonLeonTeleport::OnCollisionEnter(Collider* _other)
	{
	}

	void VonLeonTeleport::OnCollisionStay(Collider* _other)
	{
	}

	void VonLeonTeleport::OnCollisionExit(Collider* _other)
	{
	}
}