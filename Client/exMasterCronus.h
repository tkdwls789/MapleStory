#pragma once
#include "exMonsters.h"

namespace ex
{
	class Transform;
	class Animator;
	class Collider;
	class Rigidbody;
	class Sound;

	class MasterCronus : public Monsters
	{
	public:
		MasterCronus();
		virtual ~MasterCronus();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* _other) override;
		virtual void OnCollisionStay(Collider* _other) override;
		virtual void OnCollisionExit(Collider* _other) override;

		void SetMoveDelay(float _delay) { mMoveDelay = _delay; }
		float GetMoveDelay() { return mMoveDelay; }
		int GetSkillDamage() { return mSkillDamage; }

		void Idle();
		void Move();
		void Attack();
		void Chase();
		void Hit();
		void Dead();

	private:
		int		mSkillDamage;
		float	mAttackDelay;

		Sound* mMasterCronusHitSound;
		Sound* mMasterCronusDeadSound;
	};

}
