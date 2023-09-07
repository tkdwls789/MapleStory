#pragma once
#include "exEffectManger.h"

namespace ex
{
	class Animator;
	class Collider;
	class Transform;
	class GateKeeper;
	class Sound;

	class GateKeeperAttack : public EffectManger
	{
	public:
		GateKeeperAttack(GateKeeper* _owner);
		virtual ~GateKeeperAttack();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* _other) override;
		virtual void OnCollisionStay(Collider* _other) override;
		virtual void OnCollisionExit(Collider* _other) override;

		std::set<GameObject*>* GetAttackList() { return &mAttackList; }
	private:
		GameObject* mOwner;
		std::set<GameObject*> mAttackList;

		Animator* mAnimator;
		Collider* mCollider;
		Transform* mTransform;

		EffectInfo mGateKeeperAttackInfo;
		int	   mGateKeeperAttackDamege;
		Sound* mGateKeeperAttackSound;
	};

}
