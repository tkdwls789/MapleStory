#pragma once
#include "exMonsters.h"

namespace ex
{
	class Sound;

	class VonLeon : public Monsters
	{
	public:
		VonLeon();
		virtual ~VonLeon();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* _other) override;
		virtual void OnCollisionStay(Collider* _other) override;
		virtual void OnCollisionExit(Collider* _other) override;

		bool IsVonLeonChaseOn() { return mbChaseOn; }
		void SetVonLeonHit(bool _data) { mbChaseOn = _data; }

		void SetVonLeonInfo(MonstersInfo _info) { mMonstersInfo = _info; }
		MonstersInfo GetVonLeonInfo() { return mMonstersInfo; }

		int GetSkill1Damage() { return mSkill1Damage; }
		int GetSkill2Damage() { return mSkill2Damage; }
		int GetSkill3Damage() { return mSkill3Damage; }
		int GetSkill4Damage() { return mSkill4Damage; }

		void Idle();
		void Chase();
		void Hit();
		void Dead();
		void Skill1();
		void Skill2();
		void Skill3();
		void Skill4();
		void Skill5();
		void Teleport();


	private:
		bool    mbChaseOn;

		float	mAttackDelay;
		float	mSkillDelay;
		float	mSleepDelay;
		float	mSkill3Delay;

		int     mUsingSkillNumber;

		int		mSkill1Damage;
		int		mSkill2Damage;
		int		mSkill3Damage;
		int		mSkill4Damage;
		Sound* mVonLeonHitSound;
		Sound* mVonLeonDeadSound;
	};

}
