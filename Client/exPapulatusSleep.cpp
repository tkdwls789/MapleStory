#include "exPapulatusSleep.h"
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
#include "exPapulatus.h"
#include "exSound.h"
#include "exPapulatusSleep.h"


namespace ex
{
	PapulatusSleep::PapulatusSleep(Papulatus* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
		, mPapulatusSleep_Sound(nullptr)
		, mPapulatusSleep_Heal(1000000)
	{
		mPapulatusSleep_Sound = ResourceManager::Load<Sound>(L"PapulatusSleep_Sound", L"..\\Resources\\Maple\\Sound\\Monster\\Papulatus\\Papulatus_Sleep.wav");
		mPapulatusSleep_Sound->Play(false);

		mAnimator = _owner->GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mCollider = AddComponent<Collider>();

	}

	PapulatusSleep::~PapulatusSleep()
	{
	}

	void PapulatusSleep::Initialize()
	{
	}

	void PapulatusSleep::Update()
	{		
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}

		GameObject::Update();
	}

	void PapulatusSleep::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void PapulatusSleep::OnCollisionEnter(Collider* _other)
	{
	}

	void PapulatusSleep::OnCollisionStay(Collider* _other)
	{
	}

	void PapulatusSleep::OnCollisionExit(Collider* _other)
	{
	}
}