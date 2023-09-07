#pragma once
#include "exMonsters.h"

namespace ex
{
	class Transform;
	class Animator;
	class Collider;
	class Rigidbody;
	class Sound;

	class Robo : public Monsters
	{
	public:
		Robo();
		virtual ~Robo();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* _other) override;
		virtual void OnCollisionStay(Collider* _other) override;
		virtual void OnCollisionExit(Collider* _other) override;

		void SetMoveDelay(float _delay) { mMoveDelay = _delay; }
		float GetMoveDelay() { return mMoveDelay; }

		void Idle();
		void Move();
		void Chase();
		void Hit();
		void Dead();

	private:
		Sound* mRoboHitSound;
		Sound* mRoboDeadSound;
	};

}
