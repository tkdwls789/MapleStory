#pragma once
#include "exEffectManger.h"

namespace ex
{
	class Animator;
	class Collider;
	class Transform;
	class Animation;
	class Sound;

	class ComboDeathFaultHit : public EffectManger
	{
	public:
		ComboDeathFaultHit(GameObject* _owner);
		virtual ~ComboDeathFaultHit();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* _other) override;
		virtual void OnCollisionStay(Collider* _other) override;
		virtual void OnCollisionExit(Collider* _other) override;

	private:
		GameObject* mOwner;

		Animator* mAnimator;
		Transform* mTransform;
		Sound* mComboDeathFaultHitSound;
	};

}
