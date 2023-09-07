#include "exStun.h"
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
#include "exMonsters.h"

namespace ex
{
	Stun::Stun(GameObject* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
		, mConditionDelay(0.0f)
	{
		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();

		mAnimator->CreateAnimationFolder(L"StunEffect",
			L"..\\Resources\\Maple\\Image\\Player2\\Stun",math::Vector2(0.0f,0.0f), 0.37f);

		mAnimator->PlayAnimation(L"StunEffect", false);
		math::Vector2 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		mTransform->SetPosition(pos);

		enums::eMoveDir dir = GetOwner()->GetComponent<Transform>()->GetMoveDir();

		if (dir == enums::eMoveDir::Left)
		{
			mTransform->SetPosition(pos.x + 22.0f, pos.y - 15.0f);
		}
		else
		{
			mTransform->SetPosition(pos.x - 22.0f, pos.y - 15.0f);
		}
	}

	Stun::~Stun()
	{
	}

	void Stun::Initialize()
	{
	}

	void Stun::Update()
	{
		Player* player = SceneManager::GetPlayer();
		math::Vector2 pos = player->GetPosition();
		enums::eMoveDir dir = GetOwner()->GetComponent<Transform>()->GetMoveDir();
		mTransform->SetPosition(math::Vector2(pos.x, pos.y - 20.0f));

		bool bStunCheck = player->IsStunCheck();
		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (bCheck && bStunCheck == false)
		{
			Destroy(this);
		}
		else
		{
			if (bCheck)
			{
				mAnimator->PlayAnimation(L"StunEffect", false);
			}

		}
		GameObject::Update();

	}

	void Stun::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}


	void Stun::OnCollisionEnter(Collider* _other)
	{
	}

	void Stun::OnCollisionStay(Collider* _other)
	{
	}

	void Stun::OnCollisionExit(Collider* _other)
	{
	}
}
