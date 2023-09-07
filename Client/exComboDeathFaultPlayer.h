#pragma once
#include "exEffectManger.h"

namespace ex
{
	class Animator;
	class Transform;
	class Sound;

	class ComboDeathFaultPlayer : public EffectManger
	{
	public:
		ComboDeathFaultPlayer(GameObject* _owner);
		virtual ~ComboDeathFaultPlayer();

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
		Sound* mComboDeathFaultSound;
	};

}
