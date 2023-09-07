#include "exVonLeonSkill5.h"
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
	VonLeonSkill5::VonLeonSkill5(VonLeon* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
		, mVonLeonSkill5_Damege(0)
		, mVonLeonSkill5_Sound(nullptr)
		, mSkillDelay(0.0f)
	{
		mVonLeonSkill5_Info.AttackCount = 1;
		mVonLeonSkill5_Info.DamagePercentage = 1;
		mVonLeonSkill5_Damege = 12671;
		SetEffectInfo(mVonLeonSkill5_Info);

		mVonLeonSkill5_Sound = ResourceManager::Load<Sound>(L"VonLeonSkill5_Sound", L"..\\Resources\\Maple\\Sound\\Monster\\VonLeon\\VonLeon_Skill5.wav");
		mVonLeonSkill5_Sound->Play(false);

		mAnimator = _owner->GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mCollider = AddComponent<Collider>();

		mCollider->SetSize(math::Vector2(0.0f, 0.0f));
		mTransform->SetPosition(_owner->GetPositionX(), _owner->GetPositionY());
		enums::eMoveDir vonLeonDir = _owner->GetComponent<Transform>()->GetMoveDir();

		if (vonLeonDir == enums::eMoveDir::Left)
		{
			mCollider->SetOffset(math::Vector2(-100.0f, 100.0f));
		}
		else
		{
			mCollider->SetOffset(math::Vector2(100.0f, 100.0f));
		}
	}

	VonLeonSkill5::~VonLeonSkill5()
	{
	}

	void VonLeonSkill5::Initialize()
	{
	}

	void VonLeonSkill5::Update()
	{
		mSkillDelay += Time::GetDeltaTime();
		if (mSkillDelay >= 1.1f)
		{
			mCollider->SetSize(math::Vector2(600.0f, 300.0f));
			mSkillDelay = 0.0f;
		}
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}

		GameObject::Update();
	}

	void VonLeonSkill5::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void VonLeonSkill5::OnCollisionEnter(Collider* _other)
	{
		Player* player = dynamic_cast<Player*>(_other->GetOwner());
		if (player != nullptr && player->IsInvincible() == false && player->GetState() != eState::Death)
		{
			float playerPos = player->GetPositionX();
			float monsterPos = mOwner->GetPositionX();

			if (playerPos <= monsterPos &&
				player->GetState() != eState::Rush &&
				player->GetState() != eState::UpperCharge)
			{
				player->GetComponent<Rigidbody>()->SetVelocity(math::Vector2(-700.0f, 0.0f));
			}
			else
			{
				player->GetComponent<Rigidbody>()->SetVelocity(math::Vector2(700.0f, 0.0f));
			}
			for (size_t i = 1; i <= this->GetEffectInfo().AttackCount; i++)
			{
				DamageManager* damage = new DamageManager();
				object::ActiveSceneAddGameObject(enums::eLayerType::UI, damage);
				damage->SetPosition(math::Vector2(player->GetPositionX(), player->GetPositionY() - 28.0f * i));
				damage->PlayMonsterDamageAnimation(mVonLeonSkill5_Damege, this->GetEffectInfo().DamagePercentage);
			}
		}
	}

	void VonLeonSkill5::OnCollisionStay(Collider* _other)
	{
	}

	void VonLeonSkill5::OnCollisionExit(Collider* _other)
	{
	}
}