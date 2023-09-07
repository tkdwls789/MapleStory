#include "exRush.h"
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
	Rush::Rush(GameObject* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
		, mRushSound(nullptr)
	{

		mRushInfo.AttackCount = 1;
		mRushInfo.DamagePercentage = 305;
		SetEffectInfo(mRushInfo);

		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mCollider = AddComponent<Collider>();

		//// png
		Texture* image = ResourceManager::Load<Texture>(L"LeftRush"
			, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\Rush\\Left\\Left_Rush.png");

		mAnimator->CreateAnimation(L"LeftRush", image, math::Vector2(0.0f, 0.0f), math::Vector2(798.0f,435.0f)
			, math::Vector2(798.0f, 435.0f), 14, math::Vector2(0), 0.05f);

		//// png
		image = ResourceManager::Load<Texture>(L"RightRush"
			, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\Rush\\Right\\Right_Rush.png");

		mAnimator->CreateAnimation(L"RightRush", image, math::Vector2(11172.0f, 0.0f), math::Vector2(798.0f, 435.0f)
			, math::Vector2(-798.0f, 0.0f), 14, math::Vector2(0), 0.05f);

		mAnimator->SetScale(math::Vector2(1.0f, 1.0f));
		enums::eMoveDir playerDir = _owner->GetTransform()->GetMoveDir();
		math::Vector2 playerPos = _owner->GetPosition();

		mCollider->SetSize(math::Vector2(300.0f, 100.0f));
		mTransform->SetPosition(math::Vector2(playerPos));

		if (playerDir == enums::eMoveDir::Left)
		{
			mCollider->SetOffset(math::Vector2(-140.0f, -17.0f));
			mAnimator->PlayAnimation(L"LeftRush", false);
		}
		else
		{
			mCollider->SetOffset(math::Vector2(110.0f, -17.0f));
			mAnimator->PlayAnimation(L"RightRush", false);
		}

		mRushSound = ResourceManager::Load<Sound>(L"RushSound", L"..\\Resources\\Maple\\Sound\\Skill\\Rush.wav");
		mRushSound->Play(false);
	}

	Rush::~Rush()
	{
	}

	void Rush::Initialize()
	{
	}

	void Rush::Update()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
		math::Vector2 playerPos = SceneManager::GetPlayer()->GetComponent<Transform>()->GetPosition();
		mTransform->SetPosition(math::Vector2(playerPos));

		eState playerState = SceneManager::GetPlayer()->GetState();
		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (playerState == eState::RaisingBlow)
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

	void Rush::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Rush::OnCollisionEnter(Collider* _other)
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

	void Rush::OnCollisionStay(Collider* _other)
	{
	}

	void Rush::OnCollisionExit(Collider* _other)
	{
	}
}