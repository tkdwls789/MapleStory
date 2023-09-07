#include "exMushMomSkill.h"
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
#include "exMushMom.h"
#include "exSound.h"


namespace ex
{
	MushMomSkill::MushMomSkill(MushMom* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
		, mMonsterSkillDamege(0)
		, mMushMomSkillSound(nullptr)
	{
		mMushMomSkillInfo.AttackCount = 1;
		mMushMomSkillInfo.DamagePercentage = 9;
		mMonsterSkillDamege = _owner->GetSkillDamage();
		SetEffectInfo(mMushMomSkillInfo);

		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mCollider = AddComponent<Collider>();

		mAnimator->CreateAnimationFolder(L"MushMomLeftAttackEffect",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\MushMom\\AttackEffect\\Left", math::Vector2(0.0f, -45.0f), 0.03f);

		mAnimator->CreateAnimationFolder(L"MushMomRightAttackEffect",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\MushMom\\AttackEffect\\Right",math::Vector2(0.0f,-45.0f), 0.03f);

		mMushMomSkillSound = ResourceManager::Load<Sound>(L"MushMomSkillSound", L"..\\Resources\\Maple\\Sound\\Monster\\MushMom\\MushMom_Attack.wav");
		mMushMomSkillSound->Play(false);

		mAnimator->SetScale(math::Vector2(1.3f, 1.3f));
		enums::eMoveDir MushmomDir = _owner->GetTransform()->GetMoveDir();

		mCollider->SetSize(math::Vector2(950.0f, 50.0f));
		math::Vector2 MushmomPos = _owner->GetPosition();
		mTransform->SetPosition(math::Vector2(MushmomPos.x, MushmomPos.y + 75.0f));

		if (MushmomDir == enums::eMoveDir::Left)
		{
			//mCollider->SetOffset(math::Vector2(-130.0f, -23.0f));
			mAnimator->PlayAnimation(L"MushMomLeftAttackEffect", false);
		}
		else
		{
			//mCollider->SetOffset(math::Vector2(130.0f, -23.0f));
			mAnimator->PlayAnimation(L"MushMomRightAttackEffect", false);
		}

	}

	MushMomSkill::~MushMomSkill()
	{
	}

	void MushMomSkill::Initialize()
	{
	}

	void MushMomSkill::Update()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}

		//eMonsterState monsterState = monsterState;
		//bool bCheck = mAnimator->IsActiveAnimationComplete();
		//if (monsterState == eMonsterState::Attack)
		//{
		//	// 충돌 이벤트구현
		//}
		//else
		//{
		//	// 어택이 끝나면 초기화해줌
		//	mAttackList.clear();
		//}
		GameObject::Update();
	}

	void MushMomSkill::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void MushMomSkill::OnCollisionEnter(Collider* _other)
	{
		Player* player = dynamic_cast<Player*>(_other->GetOwner());
		if (player != nullptr && player->IsInvincible() == false)
		{
			float playerPos = player->GetPositionX();
			float monsterPos = mOwner->GetPositionX();
			if (playerPos <= monsterPos)
			{
				player->GetComponent<Rigidbody>()->SetVelocity(math::Vector2(-100.0f, 0.0f));
			}
			else
			{
				player->GetComponent<Rigidbody>()->SetVelocity(math::Vector2(100.0f, 0.0f));
			}
			for (size_t i = 1; i <= this->GetEffectInfo().AttackCount; i++)
			{
				DamageManager* damage = new DamageManager();
				object::ActiveSceneAddGameObject(enums::eLayerType::UI, damage);
				damage->SetPosition(math::Vector2(player->GetPositionX(), player->GetPositionY() - 28.0f * i));
				damage->PlayMonsterDamageAnimation(mMonsterSkillDamege, this->GetEffectInfo().DamagePercentage);
			}
		}
	}

	void MushMomSkill::OnCollisionStay(Collider* _other)
	{

	}

	void MushMomSkill::OnCollisionExit(Collider* _other)
	{
	}
}