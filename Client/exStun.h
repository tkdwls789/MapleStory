#pragma once
#include "exEffectManger.h"

namespace ex
{
    class Transform;
	class Animator;

	class Stun : public EffectManger
	{
	public:
		Stun(GameObject* _owner);
		virtual ~Stun();

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
		float      mConditionDelay;

	};

}
