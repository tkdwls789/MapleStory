#include "exVonLeonHuman.h"
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
#include "exFloor.h"
#include "exSound.h"
#include "exVonLeon.h"
#include "exVonLeonHpBar.h"

namespace ex
{
	VonLeonHuman::VonLeonHuman()
		:mVonLeonDial2_Sound(nullptr)
		, mbSoundCheck(true)
	{
		VonLeon* vonLeon = object::Instantiate<VonLeon>(enums::eLayerType::Monster);
		mVonLeon = vonLeon;
		mVonLeonDial2_Sound = ResourceManager::Load<Sound>(L"VonLeonDial2_Sound", L"..\\Resources\\Maple\\Sound\\Monster\\VonLeon\\VonLeon_Dial2.wav");
		mMonsterState = eMonsterState::Sleep;

		VonLeonHpBar* vonLeonHpBar = new VonLeonHpBar(vonLeon);
		object::ActiveSceneAddGameObject(enums::eLayerType::UI, vonLeonHpBar);
	}


	VonLeonHuman::~VonLeonHuman()
	{
	}

	void VonLeonHuman::Initialize()
	{
		// Left
		mAnimator->CreateAnimationFolder(L"VonLeonHumanIdle",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\VonLeon\\Human", math::Vector2(0.0f, -100.0f));

		mAnimator->CreateAnimationFolder(L"VonLeonTransform",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\VonLeon\\Appearance", math::Vector2(0.0f, -100.0f));

		mAnimator->PlayAnimation(L"VonLeonHumanIdle", false);
		mAnimator->SetAffectedCamera(true);
		mCollider->SetSize(math::Vector2(100.0f, 100.0f));
		mCollider->SetOffset(math::Vector2(20.0f, 80.0f));
		mTransform->SetPosition(math::Vector2(995.0f, 360.0f));
	}


	void VonLeonHuman::Update()
	{
		math::Vector2 playerPos = SceneManager::GetPlayer()->GetPosition();
		float distanceX = fabs(playerPos.x - this->GetPositionX());
		float distanceY = fabs(playerPos.y - this->GetPositionY());


		if (distanceX < 480.0f && distanceY < 200.0f)
		{
			if (mbSoundCheck)
			{
				mVonLeonDial2_Sound->Play(false);
				mbSoundCheck = false;
			}
			mAnimator->PlayAnimation(L"VonLeonTransform", false);

			bool bCheck = mAnimator->IsActiveAnimationComplete();
			if (bCheck)
			{
				mVonLeon->Initialize();
				Destroy(this);
			}
		}
		GameObject::Update();
	}

	void VonLeonHuman::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}


	void VonLeonHuman::OnCollisionEnter(Collider* _other)
	{
	}

	void VonLeonHuman::OnCollisionStay(Collider* _other)
	{
	}

	void VonLeonHuman::OnCollisionExit(Collider* _other)
	{
	}

}