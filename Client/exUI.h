#pragma once
#include "exGameObject.h"

namespace ex
{
	class Transform;
	class Collider;
	class Animator;

	class UI : public GameObject
	{
	public:
		UI();
		virtual ~UI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* _other) override;
		virtual void OnCollisionStay(Collider* _other) override;
		virtual void OnCollisionExit(Collider* _other) override;

	protected:
		Transform* mTransform;
		Collider* mCollider;
		Animator* mAnimator;




	};

}
