#pragma once
#include "exMonsters.h"

namespace ex
{
	class Sound;

	class MushMom : public Monsters
	{
	public:
		MushMom();
		virtual ~MushMom();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* _other) override;
		virtual void OnCollisionStay(Collider* _other) override;
		virtual void OnCollisionExit(Collider* _other) override;

		void SetMoveDelay(float _delay) { mMoveDelay = _delay; }
		float GetMoveDelay() { return mMoveDelay; }

		void SetMushMomInfo(MonstersInfo _info) { mMonstersInfo = _info; }
		MonstersInfo GetMushMomInfo() { return mMonstersInfo; }

		int GetSkillDamage() { return mSkillDamage; }

		bool IsMushMomHit() { return mbMushMomHit; }
		void SetMushMomHit(bool _data) { mbMushMomHit = _data; }
	
		void Idle();
		void Move();
		void Attack();
		void Chase();
		void Hit();
		void Dead();

	private:
		int		mSkillDamage;
		float	mAttackDelay;
		bool	mbMushMomHit;

		Sound* mMushMomHitSound;
		Sound* mMushMomDeadSound;
	};

}
