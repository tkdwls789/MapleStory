//#pragma once
//#include "exMonsters.h"
//
//namespace ex
//{
//	class Sound;
//
//	class PilotPapulatus : public Monsters
//	{
//	public:
//		PilotPapulatus();
//		virtual ~PilotPapulatus();
//
//		virtual void Initialize() override;
//		virtual void Update() override;
//		virtual void Render(HDC _hdc) override;
//
//		virtual void OnCollisionEnter(Collider* _other) override;
//		virtual void OnCollisionStay(Collider* _other) override;
//		virtual void OnCollisionExit(Collider* _other) override;
//
//		bool IsPilotPapulatusChaseOn() { return mbChaseOn; }
//		void SetPilotPapulatusHit(bool _data) { mbChaseOn = _data; }
//
//		void SetPilotPapulatusInfo(MonstersInfo _info) { mMonstersInfo = _info; }
//		MonstersInfo GetPilotPapulatusInfo() { return mMonstersInfo; }
//
//		int GetSkill1Damage() { return mSkill1Damage; }
//		int GetSkill2Damage() { return mSkill2Damage; }
//		int GetSkill3Damage() { return mSkill3Damage; }
//		int GetSkill4Damage() { return mSkill4Damage; }
//
//		void Idle();
//		void Move();
//		void Chase();
//		void Hit();
//		void Dead();
//		void Skill1();
//		void Skill2();
//		void Skill3();
//		void Skill4();
//		void Skill5();
//		void WakeUp();
//
//
//	private:
//		bool    mbChaseOn;
//		bool    mbSleepOn;
//		float	mAttackDelay;
//		float	mSkillDelay;
//		float	mSleepDelay;
//		float	mSkill3Delay;
//
//		int     mUsingSkillNumber;
//
//		int		mSkill1Damage;
//		int		mSkill2Damage;
//		int		mSkill3Damage;
//		int		mSkill4Damage;
//		Sound* mPilotPapulatusHitSound;
//		Sound* mPilotPapulatusDeadSound;
//	};
//
//}
