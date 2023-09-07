#include "exPapulatusSkill5.h"
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
	PapulatusSkill5::PapulatusSkill5(Papulatus* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
		, mPapulatusSkill5_Sound(nullptr)
		, mPapulatusSkill5_Heal(1000000)
		, mCollider(nullptr)
		, mTransform(nullptr)
	{
		mPapulatusSkill5_Sound = ResourceManager::Load<Sound>(L"PapulatusSkill5_Sound", L"..\\Resources\\Maple\\Sound\\Monster\\Papulatus\\Papulatus_Skill5.wav");
		mPapulatusSkill5_Sound->Play(false);

		mAnimator = _owner->GetComponent<Animator>();

	}

	PapulatusSkill5::~PapulatusSkill5()
	{
	}

	void PapulatusSkill5::Initialize()
	{
	}

	void PapulatusSkill5::Update()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}

		GameObject::Update();
	}

	void PapulatusSkill5::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void PapulatusSkill5::OnCollisionEnter(Collider* _other)
	{
	}

	void PapulatusSkill5::OnCollisionStay(Collider* _other)
	{
	}

	void PapulatusSkill5::OnCollisionExit(Collider* _other)
	{
	}
}