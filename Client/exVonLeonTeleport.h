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

	class VonLeonTeleport : public EffectManger
	{
	public:
		VonLeonTeleport(VonLeon* _owner);
		virtual ~VonLeonTeleport();

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
		VonLeon* mVonLeon;

		Animator* mAnimator;
		Collider* mCollider;
		Transform* mTransform;
		Rigidbody* mRigidbody;

		EffectInfo mVonLeonTeleport_Info;
		int	   mVonLeonTeleport_Damege;
		Sound* mVonLeonTeleport_Sound;
	};

}
