#pragma once
#include "exEffectManger.h"

namespace ex
{
	class Animator;
	class Transform;
	class Collider;

	class ComboDeathFaultScreen : public EffectManger
	{
	public:
		ComboDeathFaultScreen(GameObject* _owner);
		virtual ~ComboDeathFaultScreen();

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
		Transform* mTransform;
		Collider* mCollider;

		EffectInfo mComboDeathFaultInfo;
	};

}
