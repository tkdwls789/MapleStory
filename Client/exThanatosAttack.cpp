#include "exThanatosAttack.h"
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
#include "exThanatos.h"
#include "exSound.h"


namespace ex
{
	ThanatosAttack::ThanatosAttack(Thanatos* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
		, mThanatosAttackDamege(0)
		, mThanatosAttackSound(nullptr)
	{
		mThanatosAttackInfo.AttackCount = 1;
		mThanatosAttackInfo.DamagePercentage = 9;
		mThanatosAttackDamege = _owner->GetSkillDamage();
		SetEffectInfo(mThanatosAttackInfo);

		mThanatosAttackSound = ResourceManager::Load<Sound>(L"ThanatosAttackSound", L"..\\Resources\\Maple\\Sound\\Monster\\Thanatos\\Thanatos_Attack.wav");
		mThanatosAttackSound->Play(false);


		mAnimator = _owner->GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mCollider = AddComponent<Collider>();
		mCollider->SetSize(math::Vector2(400.0f, 100.0f));

		math::Vector2 gateKeeperPos = _owner->GetPosition();
		enums::eMoveDir gateKeeperDir = _owner->GetComponent<Transform>()->GetMoveDir();

		mTransform->SetPosition(math::Vector2(gateKeeperPos.x, gateKeeperPos.y));
		if (gateKeeperDir == enums::eMoveDir::Left)
		{
			mCollider->SetOffset(math::Vector2(-100.0f, 0.0f));
		}
		else
		{
			mCollider->SetOffset(math::Vector2(100.0f, 0.0f));
		}

	}

	ThanatosAttack::~ThanatosAttack()
	{
	}

	void ThanatosAttack::Initialize()
	{
	}

	void ThanatosAttack::Update()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}

		GameObject::Update();
	}

	void ThanatosAttack::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void ThanatosAttack::OnCollisionEnter(Collider* _other)
	{
		Player* player = dynamic_cast<Player*>(_other->GetOwner());
		if (player != nullptr && player->IsInvincible() == false)
		{
			for (size_t i = 1; i <= this->GetEffectInfo().AttackCount; i++)
			{
				DamageManager* damage = new DamageManager();
				object::ActiveSceneAddGameObject(enums::eLayerType::UI, damage);
				damage->SetPosition(math::Vector2(player->GetPositionX(), player->GetPositionY() - 28.0f * i));
				damage->PlayMonsterDamageAnimation(mThanatosAttackDamege, this->GetEffectInfo().DamagePercentage);
			}
		}
	}

	void ThanatosAttack::OnCollisionStay(Collider* _other)
	{

	}

	void ThanatosAttack::OnCollisionExit(Collider* _other)
	{
	}
}