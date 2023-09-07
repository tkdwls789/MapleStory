#include "exVonLeonSkill3.h"
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
#include "exStun.h"


namespace ex
{
	VonLeonSkill3::VonLeonSkill3(VonLeon* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
		, mVonLeonSkill3_Damege(0)
		, mVonLeonSkill3_Sound(nullptr)
		, mSkillDelay(0.0f)
	{
		mVonLeonSkill3_Info.AttackCount = 1;
		mVonLeonSkill3_Info.DamagePercentage = 9;
		mVonLeonSkill3_Damege = _owner->GetSkill3Damage();
		SetEffectInfo(mVonLeonSkill3_Info);

		mVonLeonSkill3_Sound = ResourceManager::Load<Sound>(L"VonLeonSkill3_Sound", L"..\\Resources\\Maple\\Sound\\Monster\\VonLeon\\VonLeon_Skill3.wav");
		mVonLeonSkill3_Sound->Play(false);

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

	VonLeonSkill3::~VonLeonSkill3()
	{
	}

	void VonLeonSkill3::Initialize()
	{
	}

	void VonLeonSkill3::Update()
	{
		mSkillDelay += Time::GetDeltaTime();
		if (mSkillDelay >= 1.1f)
		{
			mCollider->SetSize(math::Vector2(850.0f, 600.0f));
			mSkillDelay = 0.0f;
		}
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}

		GameObject::Update();
	}

	void VonLeonSkill3::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void VonLeonSkill3::OnCollisionEnter(Collider* _other)
	{
		Player* player = dynamic_cast<Player*>(_other->GetOwner());
		if (player != nullptr && player->IsInvincible() == false && player->GetState() != eState::Death)
		{
			player->SetStunCheck(true);
			Stun* stun = new Stun(player);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, stun);

			for (size_t i = 1; i <= this->GetEffectInfo().AttackCount; i++)
			{
				DamageManager* damage = new DamageManager();
				object::ActiveSceneAddGameObject(enums::eLayerType::UI, damage);
				damage->SetPosition(math::Vector2(player->GetPositionX(), player->GetPositionY() - 35.0f * i));
				damage->PlayMonsterDamageAnimation(mVonLeonSkill3_Damege, this->GetEffectInfo().DamagePercentage);
			}

		}
	}

	void VonLeonSkill3::OnCollisionStay(Collider* _other)
	{
	}

	void VonLeonSkill3::OnCollisionExit(Collider* _other)
	{
	}
}