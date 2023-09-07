#include "exUpperCharge.h"
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
#include "exSound.h"

namespace ex
{
	UpperCharge::UpperCharge(GameObject* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
		, mUpperChargeSound(nullptr)
	{
		mUpperChargeInfo.AttackCount = 1;
		mUpperChargeInfo.DamagePercentage = 304;
		SetEffectInfo(mUpperChargeInfo);

		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mCollider = AddComponent<Collider>();


		// png
		Texture* image = ResourceManager::Load<Texture>(L"LeftUpperCharge"
			, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\UpperCharge\\Left\\Left_UpperCharge.png");

		mAnimator->CreateAnimation(L"LeftUpperCharge", image, math::Vector2(0.0f, 0.0f), math::Vector2(604.0f, 604.0f)
			, math::Vector2(604.0f, 604.0f), 14, math::Vector2(0), 0.035f);

		// png
		image = ResourceManager::Load<Texture>(L"RightUpperCharge"
			, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\UpperCharge\\Right\\Right_UpperCharge.png");

		mAnimator->CreateAnimation(L"RightUpperCharge", image, math::Vector2(8456.0f, 0.0f), math::Vector2(604.0f, 604.0f)
			, math::Vector2(-604.0f, 0.0f), 14, math::Vector2(0), 0.035f);

		mAnimator->SetScale(math::Vector2(1.0f, 1.0f));
		mCollider->SetSize(math::Vector2(130.0f, 150.0f));
		mCollider->SetOffset(math::Vector2(0.0f, 30.0f));

		enums::eMoveDir playerDir = _owner->GetTransform()->GetMoveDir();
		math::Vector2 playerPos = _owner->GetPosition();


		if (playerDir == enums::eMoveDir::Left)
		{
			mTransform->SetPosition(math::Vector2(playerPos.x, playerPos.y - 90.0f));
			mAnimator->PlayAnimation(L"LeftUpperCharge", false);
		}
		else
		{
			mTransform->SetPosition(math::Vector2(playerPos.x, playerPos.y - 90.0f));
			mAnimator->PlayAnimation(L"RightUpperCharge", false);
		}

		mUpperChargeSound = ResourceManager::Load<Sound>(L"UpperChargeSound", L"..\\Resources\\Maple\\Sound\\Skill\\UpperCharge.wav");
		mUpperChargeSound->Play(false);

	}

	UpperCharge::~UpperCharge()
	{
	}

	void UpperCharge::Initialize()
	{
	}

	void UpperCharge::Update()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}

		eState playerState = SceneManager::GetPlayer()->GetState();
		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (playerState == eState::UpperCharge)
		{
			// 충돌 이벤트구현
		}
		else
		{
			// 어택이 끝나면 초기화해줌
			mAttackList.clear();
		}
		GameObject::Update();
	}

	void UpperCharge::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void UpperCharge::OnCollisionEnter(Collider* _other)
	{
		Monsters* monsters = dynamic_cast<Monsters*>(_other->GetOwner());
		if (monsters != nullptr)
		{
			for (size_t i = 1; i <= this->GetEffectInfo().AttackCount; i++)
			{
				if (monsters->GetMonstersState() != eMonsterState::Sleep &&
					monsters->GetMonstersState() != eMonsterState::WakeUp &&
					monsters->GetMonstersState() != eMonsterState::Dead)
				{
					DamageManager* damage = new DamageManager();
					object::ActiveSceneAddGameObject(enums::eLayerType::UI, damage);
					damage->SetPosition(math::Vector2(monsters->GetPositionX(), monsters->GetPositionY() - 28.0f * i));
					damage->PlayPlayerDamageAnimation(this->GetEffectInfo().DamagePercentage);
					monsters->ReductiongHp(damage->GetPlayerResultDamage());
				}
			}
		}
	}

	void UpperCharge::OnCollisionStay(Collider* _other)
	{
	}

	void UpperCharge::OnCollisionExit(Collider* _other)
	{
	}
}