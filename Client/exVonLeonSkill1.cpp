#include "exVonLeonSkill1.h"
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
	VonLeonSkill1::VonLeonSkill1(VonLeon* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
		, mVonLeonSkill1_Damege(0)
		, mVonLeonSkill1_Sound(nullptr)
		, mSkillDelay(0.0f)
	{
		mVonLeonSkill1_Info.AttackCount = 1;
		mVonLeonSkill1_Info.DamagePercentage = 9;
		mVonLeonSkill1_Damege = _owner->GetSkill1Damage();
		SetEffectInfo(mVonLeonSkill1_Info);

		mVonLeonSkill1_Sound = ResourceManager::Load<Sound>(L"VonLeonSkill1_Sound", L"..\\Resources\\Maple\\Sound\\Monster\\VonLeon\\VonLeon_Skill1.wav");
		mVonLeonSkill1_Sound->Play(false);

		mAnimator = _owner->GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mCollider = AddComponent<Collider>();

		mCollider->SetSize(math::Vector2(0.0f, 0.0f));
		mTransform->SetPosition(_owner->GetPositionX(), _owner->GetPositionY());
		enums::eMoveDir vonLeonDir = _owner->GetComponent<Transform>()->GetMoveDir();

		if (vonLeonDir == enums::eMoveDir::Left)
		{
			mCollider->SetOffset(math::Vector2(0.0f, 100.0f));
		}
		else
		{
			mCollider->SetOffset(math::Vector2(0.0f, 100.0f));
		}
	}

	VonLeonSkill1::~VonLeonSkill1()
	{
	}

	void VonLeonSkill1::Initialize()
	{
	}

	void VonLeonSkill1::Update()
	{
		mSkillDelay += Time::GetDeltaTime();
		if (mSkillDelay >= 1.5f)
		{
			mCollider->SetSize(math::Vector2(700.0f, 300.0f));
			mSkillDelay = 0.0f;
		}
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}

		GameObject::Update();
	}

	void VonLeonSkill1::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void VonLeonSkill1::OnCollisionEnter(Collider* _other)
	{
		Player* player = dynamic_cast<Player*>(_other->GetOwner());
		if (player != nullptr && player->IsInvincible() == false && player->GetState() != eState::Death)
		{
			for (size_t i = 1; i <= this->GetEffectInfo().AttackCount; i++)
			{
				DamageManager* damage = new DamageManager();
				object::ActiveSceneAddGameObject(enums::eLayerType::UI, damage);
				damage->SetPosition(math::Vector2(player->GetPositionX(), player->GetPositionY() - 28.0f * i));
				damage->PlayMonsterDamageAnimation(mVonLeonSkill1_Damege, this->GetEffectInfo().DamagePercentage);
			}
		}
	}

	void VonLeonSkill1::OnCollisionStay(Collider* _other)
	{
	}

	void VonLeonSkill1::OnCollisionExit(Collider* _other)
	{
	}
}