#include "exVonLeonSkill2.h"
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
	VonLeonSkill2::VonLeonSkill2(VonLeon* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
		, mVonLeonSkill2_Damege(0)
		, mVonLeonSkill2_Sound(nullptr)
		, mSkillDelay(0.0f)
	{
		mVonLeonSkill2_Info.AttackCount = 1;
		mVonLeonSkill2_Info.DamagePercentage = 9;
		mVonLeonSkill2_Damege = _owner->GetSkill2Damage();
		SetEffectInfo(mVonLeonSkill2_Info);

		mVonLeonSkill2_Sound = ResourceManager::Load<Sound>(L"VonLeonSkill2_Sound", L"..\\Resources\\Maple\\Sound\\Monster\\VonLeon\\VonLeon_Skill2.wav");
		mVonLeonSkill2_Sound->Play(false);

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

	VonLeonSkill2::~VonLeonSkill2()
	{
	}

	void VonLeonSkill2::Initialize()
	{
	}

	void VonLeonSkill2::Update()
	{
		mSkillDelay += Time::GetDeltaTime();
		if (mSkillDelay >= 1.1f)
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

	void VonLeonSkill2::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void VonLeonSkill2::OnCollisionEnter(Collider* _other)
	{
		Player* player = dynamic_cast<Player*>(_other->GetOwner());
		if (player != nullptr && player->IsInvincible() == false && player->GetState() != eState::Death)
		{
			for (size_t i = 1; i <= this->GetEffectInfo().AttackCount; i++)
			{
				DamageManager* damage = new DamageManager();
				object::ActiveSceneAddGameObject(enums::eLayerType::UI, damage);
				damage->SetPosition(math::Vector2(player->GetPositionX(), player->GetPositionY() - 28.0f * i));
				damage->PlayMonsterDamageAnimation(mVonLeonSkill2_Damege, this->GetEffectInfo().DamagePercentage);
			}
		}
	}

	void VonLeonSkill2::OnCollisionStay(Collider* _other)
	{
	}

	void VonLeonSkill2::OnCollisionExit(Collider* _other)
	{
	}
}