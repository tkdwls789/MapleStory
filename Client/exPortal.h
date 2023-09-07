#pragma once
#include "exGameObject.h"


namespace ex
{
	class Transform;
	class Collider;
	class Animator;
	class Sound;

	class Portal : public GameObject
	{
	public:
		Portal();
		virtual ~Portal();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* _other) override;
		virtual void OnCollisionStay(Collider* _other) override;
		virtual void OnCollisionExit(Collider* _other) override;

	private:
		Animator* mAnimator;
		Transform* mTransform;
		Collider* mCollider;
		Sound*	  mPortalSound;
		
	};

}
