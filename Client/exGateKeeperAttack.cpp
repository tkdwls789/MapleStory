#include "exGateKeeperAttack.h"
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
#include "exGateKeeper.h"
#include "exSound.h"

namespace ex
{
	GateKeeperAttack::GateKeeperAttack(GateKeeper* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
		, mGateKeeperAttackDamege(0)
		, mGateKeeperAttackSound(nullptr)
	{
		mGateKeeperAttackInfo.AttackCount = 1;
		mGateKeeperAttackInfo.DamagePercentage = 9;
		mGateKeeperAttackDamege = _owner->GetSkillDamage();
		SetEffectInfo(mGateKeeperAttackInfo);

		mGateKeeperAttackSound = ResourceManager::Load<Sound>(L"GateKeeperAttackSound", L"..\\Resources\\Maple\\Sound\\Monster\\GateKeeper\\GateKeeper_Attack.wav");
		mGateKeeperAttackSound->Play(false);

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

	GateKeeperAttack::~GateKeeperAttack()
	{
	}

	void GateKeeperAttack::Initialize()
	{
	}

	void GateKeeperAttack::Update()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}

		GameObject::Update();
	}

	void GateKeeperAttack::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void GateKeeperAttack::OnCollisionEnter(Collider* _other)
	{
		Player* player = dynamic_cast<Player*>(_other->GetOwner());
		if (player != nullptr && player->IsInvincible() == false)
		{
			for (size_t i = 1; i <= this->GetEffectInfo().AttackCount; i++)
			{
				DamageManager* damage = new DamageManager();
				object::ActiveSceneAddGameObject(enums::eLayerType::UI, damage);
				damage->SetPosition(math::Vector2(player->GetPositionX(), player->GetPositionY() - 28.0f * i));
				damage->PlayMonsterDamageAnimation(mGateKeeperAttackDamege, this->GetEffectInfo().DamagePercentage);
			}
		}
	}

	void GateKeeperAttack::OnCollisionStay(Collider* _other)
	{

	}

	void GateKeeperAttack::OnCollisionExit(Collider* _other)
	{
	}
}