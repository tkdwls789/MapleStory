#pragma once
#include "exEffectManger.h"

namespace ex
{
	class Animator;
	class Collider;
	class Transform;
	class Sound;

	class ComboSynergyBody;

	class Buff : public EffectManger
	{
	public:
		Buff(GameObject* _owner);
		virtual ~Buff();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* _other) override;
		virtual void OnCollisionStay(Collider* _other) override;
		virtual void OnCollisionExit(Collider* _other) override;


	private:
		GameObject* mOwner;

		Animator* mAnimator;
		Collider* mCollider;
		Transform* mTransform;
		Sound* mBuff;

		ComboSynergyBody* mComboSynergyBody;
	};

}
