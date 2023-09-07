#include "exPapulatusSkill2.h"
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
#include "exPapulatusSkillArea.h"

namespace ex
{
	PapulatusSkill2::PapulatusSkill2(Papulatus* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
		, mPapulatusSkill2_Damege(0)
		, mPapulatusSkill2_Sound(nullptr)
		, mSkillDelay(0.0f)
	{
		mPapulatusSkill2_Info.AttackCount = 1;
		mPapulatusSkill2_Info.DamagePercentage = 9;
		mPapulatusSkill2_Damege = 2412;
		SetEffectInfo(mPapulatusSkill2_Info);

		mPapulatusSkill2_Sound = ResourceManager::Load<Sound>(L"PapulatusSkill2_Sound", L"..\\Resources\\Maple\\Sound\\Monster\\Papulatus\\Papulatus_Skill2.wav");
		mPapulatusSkill2_Sound->Play(false);

		mAnimator = _owner->GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mCollider = AddComponent<Collider>();

		mTransform->SetPosition(_owner->GetPositionX(), _owner->GetPositionY());
		enums::eMoveDir papulatusDir = _owner->GetComponent<Transform>()->GetMoveDir();

		if (papulatusDir == enums::eMoveDir::Left)
		{
			mCollider->SetOffset(math::Vector2(-100.0f, -50.0f));
		}
		else
		{
			mCollider->SetOffset(math::Vector2(100.0f, -50.0f));
		}
	}

	PapulatusSkill2::~PapulatusSkill2()
	{
	}

	void PapulatusSkill2::Initialize()
	{
	}

	void PapulatusSkill2::Update()
	{
		mSkillDelay += Time::GetDeltaTime();
		if (mSkillDelay >= 1.3f)
		{
			mCollider->SetSize(math::Vector2(550.0f, 200.0f));
			mSkillDelay = 0.0f;
		}
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}

		GameObject::Update();
	}

	void PapulatusSkill2::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void PapulatusSkill2::OnCollisionEnter(Collider* _other)
	{
		Player* player = dynamic_cast<Player*>(_other->GetOwner());
		if (player != nullptr && player->IsInvincible() == false)
		{
			for (size_t i = 1; i <= this->GetEffectInfo().AttackCount; i++)
			{
				DamageManager* damage = new DamageManager();
				object::ActiveSceneAddGameObject(enums::eLayerType::UI, damage);
				damage->SetPosition(math::Vector2(player->GetPositionX(), player->GetPositionY() - 28.0f * i));
				damage->PlayMonsterDamageAnimation(mPapulatusSkill2_Damege, this->GetEffectInfo().DamagePercentage);
			}
		}
	}

	void PapulatusSkill2::OnCollisionStay(Collider* _other)
	{
	}

	void PapulatusSkill2::OnCollisionExit(Collider* _other)
	{
	}
}