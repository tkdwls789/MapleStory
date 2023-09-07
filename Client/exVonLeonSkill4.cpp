#include "exVonLeonSkill4.h"
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
	VonLeonSkill4::VonLeonSkill4(VonLeon* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
		, mVonLeonSkill4_Damege(0)
		, mVonLeonSkill4_Sound(nullptr)
		, mSkillDelay(0.0f)
	{
		mVonLeonSkill4_Info.AttackCount = 1;
		mVonLeonSkill4_Info.DamagePercentage = 1;
		mVonLeonSkill4_Damege = 9999999;
		SetEffectInfo(mVonLeonSkill4_Info);

		mVonLeonSkill4_Sound = ResourceManager::Load<Sound>(L"VonLeonSkill4_Sound", L"..\\Resources\\Maple\\Sound\\Monster\\VonLeon\\VonLeon_Skill4.wav");
		mVonLeonSkill4_Sound->Play(false);

		mAnimator = _owner->GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mCollider = AddComponent<Collider>();

		mCollider->SetSize(math::Vector2(0.0f, 0.0f));
		mTransform->SetPosition(_owner->GetPositionX(), _owner->GetPositionY());
		enums::eMoveDir vonLeonDir = _owner->GetComponent<Transform>()->GetMoveDir();

		if (vonLeonDir == enums::eMoveDir::Left)
		{
			mCollider->SetOffset(math::Vector2(0.0f, 210.0f));
		}
		else
		{
			mCollider->SetOffset(math::Vector2(0.0f, 210.0f));
		}
	}

	VonLeonSkill4::~VonLeonSkill4()
	{
	}

	void VonLeonSkill4::Initialize()
	{
	}

	void VonLeonSkill4::Update()
	{
		mSkillDelay += Time::GetDeltaTime();
		if (mSkillDelay >= 2.0f)
		{
			mCollider->SetSize(math::Vector2(1150.0f, 100.0f));
			mSkillDelay = 0.0f;
		}
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}

		GameObject::Update();
	}

	void VonLeonSkill4::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void VonLeonSkill4::OnCollisionEnter(Collider* _other)
	{
		Player* player = dynamic_cast<Player*>(_other->GetOwner());
		if (player != nullptr && player->IsInvincible() == false && player->GetState() != eState::Death)
		{
			for (size_t i = 1; i <= this->GetEffectInfo().AttackCount; i++)
			{
				DamageManager* damage = new DamageManager();
				object::ActiveSceneAddGameObject(enums::eLayerType::UI, damage);
				damage->SetPosition(math::Vector2(player->GetPositionX(), player->GetPositionY() - 28.0f * i));
				damage->PlayMonsterDamageAnimation(mVonLeonSkill4_Damege, this->GetEffectInfo().DamagePercentage);
			}
		}
	}

	void VonLeonSkill4::OnCollisionStay(Collider* _other)
	{
	}

	void VonLeonSkill4::OnCollisionExit(Collider* _other)
	{
	}
}