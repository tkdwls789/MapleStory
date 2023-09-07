#pragma once
#include "exGameObject.h"

namespace ex
{
	class Transform;
	class Collider;
	class Animator;

	class Login : public GameObject
	{
	public:
		Login();
		virtual ~Login();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;


		virtual void OnCollisionEnter(class Collider* _other) override;
		virtual void OnCollisionStay(class Collider* _other) override;
		virtual void OnCollisionExit(class Collider* _other) override;

		static bool IsLoginCheck() { return mbLogin; }

	private:
		Transform* mTransform;
		Collider*  mCollider;
		Animator*  mAnimator;

		static bool	mbLogin;
	};

}