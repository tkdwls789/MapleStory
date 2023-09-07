#include "exMasterCronusAttack.h"
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
#include "exMasterCronus.h"
#include "exSound.h"


namespace ex
{
	MasterCronusAttack::MasterCronusAttack(MasterCronus* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
		, mMonsterSkillDamege(0)
		, mMasterCronusAttackSound(nullptr)
	{
		mMasterCronusSkillInfo.AttackCount = 1;
		mMasterCronusSkillInfo.DamagePercentage = 9;
		mMonsterSkillDamege = _owner->GetSkillDamage();
		SetEffectInfo(mMasterCronusSkillInfo);

		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mCollider = AddComponent<Collider>();

		mMasterCronusAttackSound = ResourceManager::Load<Sound>(L"MasterCronusAttackSound", L"..\\Resources\\Maple\\Sound\\Monster\\MasterCronus\\MasterCronus_Attack.wav");
		mMasterCronusAttackSound->Play(false);

		mAnimator->CreateAnimationFolder(L"MasterCronusLeftAttackEffect",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\MasterCronus\\AttackEffect\\Left", math::Vector2(0.0f, 0.0f), 0.05f);

		mAnimator->CreateAnimationFolder(L"MasterCronusRightAttackEffect",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\MasterCronus\\AttackEffect\\Right", math::Vector2(0.0f, 0.0f), 0.05f);

		mAnimator->SetScale(math::Vector2(1.3f, 1.3f));
		enums::eMoveDir masterCronusDir = _owner->GetTransform()->GetMoveDir();

		mCollider->SetSize(math::Vector2(100.0f, 100.0f));
		math::Vector2 playerPos = SceneManager::GetPlayer()->GetPosition();
		mTransform->SetPosition(math::Vector2(playerPos.x, playerPos.y));

		if (masterCronusDir == enums::eMoveDir::Left)
		{
			//mCollider->SetOffset(math::Vector2(-130.0f, -23.0f));
			mAnimator->PlayAnimation(L"MasterCronusLeftAttackEffect", false);
		}
		else
		{
			//mCollider->SetOffset(math::Vector2(130.0f, -23.0f));
			mAnimator->PlayAnimation(L"MasterCronusRightAttackEffect", false);
		}

	}

	MasterCronusAttack::~MasterCronusAttack()
	{
	}

	void MasterCronusAttack::Initialize()
	{
	}

	void MasterCronusAttack::Update()
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

	void MasterCronusAttack::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void MasterCronusAttack::OnCollisionEnter(Collider* _other)
	{
		Player* player = dynamic_cast<Player*>(_other->GetOwner());
		if (player != nullptr && player->IsInvincible() == false)
		{
			for (size_t i = 1; i <= this->GetEffectInfo().AttackCount; i++)
			{
				DamageManager* damage = new DamageManager();
				object::ActiveSceneAddGameObject(enums::eLayerType::UI, damage);
				damage->SetPosition(math::Vector2(player->GetPositionX(), player->GetPositionY() - 28.0f * i));
				damage->PlayMonsterDamageAnimation(mMonsterSkillDamege, this->GetEffectInfo().DamagePercentage);
			}
		}
	}

	void MasterCronusAttack::OnCollisionStay(Collider* _other)
	{

	}

	void MasterCronusAttack::OnCollisionExit(Collider* _other)
	{
	}
}