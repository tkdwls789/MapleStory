#pragma once
#include "exEffectManger.h"

namespace ex
{
	class Animator;
	class Collider;
	class Transform;
	class Rigidbody;
	class VonLeon;
	class Sound;

	class VonLeonTeleportAfter : public EffectManger
	{
	public:
		VonLeonTeleportAfter(VonLeon* _owner);
		virtual ~VonLeonTeleportAfter();

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
		Rigidbody* mRigidbody;

		EffectInfo mVonLeonTeleportAfter_Info;
	};

}
