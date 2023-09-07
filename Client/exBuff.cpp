#include "exBuff.h"
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
#include "exComboSynergyBody.h"

namespace ex
{
	Buff::Buff(GameObject* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
		, mBuff(nullptr)
		, mComboSynergyBody(nullptr)
	{
		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mCollider = AddComponent<Collider>();
		mBuff = ResourceManager::Load<Sound>(L"BuffSound", L"..\\Resources\\Maple\\Sound\\Player\\player_Buff.wav");
		mBuff->Play(false);

		mAnimator->CreateAnimationFolder(L"PlayerBuff",
			L"..\\Resources\\Maple\\Image\\Player2\\Skill\\Buff");

		mAnimator->PlayAnimation(L"PlayerBuff", false);

		mComboSynergyBody = new ComboSynergyBody(mOwner);
		object::ActiveSceneAddGameObject(enums::eLayerType::Buff, mComboSynergyBody);
	}

	Buff::~Buff()
	{
	}

	void Buff::Initialize()
	{
	}

	void Buff::Update()
	{
		math::Vector2 playerPos = SceneManager::GetPlayer()->GetPosition();
		mTransform->SetPosition(playerPos);

		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
		GameObject::Update();
	}

	void Buff::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Buff::OnCollisionEnter(Collider* _other)
	{
	}

	void Buff::OnCollisionStay(Collider* _other)
	{
	}

	void Buff::OnCollisionExit(Collider* _other)
	{
	}
}