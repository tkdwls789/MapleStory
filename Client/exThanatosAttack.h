#pragma once
#include "exEffectManger.h"

namespace ex
{
	class Animator;
	class Collider;
	class Transform;
	class Thanatos;
	class Sound;

	class ThanatosAttack : public EffectManger
	{
	public:
		ThanatosAttack(Thanatos* _owner);
		virtual ~ThanatosAttack();

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

		EffectInfo mThanatosAttackInfo;
		int	   mThanatosAttackDamege;
		Sound* mThanatosAttackSound;
	};

}
