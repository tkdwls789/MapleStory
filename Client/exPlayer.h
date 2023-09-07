#pragma once
#include "exGameObject.h"


namespace ex
{
	class GameEffect;
	class Transform;
	class Animator;
	class Collider;
	class Rigidbody;
	class Texture;
	class Sound;
	class Stun;
	class Buff;

	class Player : public GameObject
	{
	private:
		struct PlayerInfo
		{
			int mHp;
			int mMaxHp;
			int mMp;
			int mMaxMp;
			int mLevel;
			float mMaxExp;
			float mExp;
			float mMinDamage;
			float mMaxDamage;

		};

	public:
		Player();
		virtual ~Player();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* _other) override;
		virtual void OnCollisionStay(Collider* _other) override;
		virtual void OnCollisionExit(Collider* _other) override;

		eState GetState() { return mState; }
		void SetState(eState _state) { mState = _state; }

		PlayerInfo* GetInfo() { return mInfo; }

		bool IsPotalState() { return mbPortalState; }
		void SetPotalState(bool _state) { mbPortalState = _state; }

		bool IsRopeState() { return mbRopeState; }
		void SetRopeState(bool _state) { mbRopeState = _state; }

		bool IsInvincible() { return mbInvincible; }
		void SetInvincible(bool _data) { mbInvincible = _data; }

		bool IsLevelUpCheck() { return mbLevelUpCheck; }
		void SetLevelUpCheck(bool _data) { mbLevelUpCheck = _data; }
		
		bool IsStunCheck() { return mbStunCheck; }
		void SetStunCheck(bool _data) { mbStunCheck = _data; }

		bool IsBuffCheck() { return mbBuffCheck; }
		void SetBuffCheck(bool _data) { mbBuffCheck = _data; }

		Buff* GetPlayerBuff() { return mBuff; }

		void Idle();
		void Move();
		void Down();
		void Rope();
		void Attack();
		void Fall();
		void Jump();
		void JumpAttack();
		void DoubleJump();
		void Hit();
		void Death();
		void RaisingBlow();
		void Uppercharge();
		void PlayerRush();
		void ComboDeathFault();
		void ComboSynergyBody();
		void PlayerBuff();

		void PlayLevelUI();
		void PlayerSkillLoad();
		void Stun();

	private:
		Animator*		mAnimator;
		Transform*		mTransform;
		Rigidbody*		mRigidbody;
		Collider*		mCollider;

		eState			mState;
		PlayerInfo*		mInfo;
		Buff*			mBuff;
		Sound*			mJumpSound;
		Sound*			mPortionSound;
		Sound*			mLevelUpSound;
		Sound*			mPlayerDeadSound;
		 
		bool			mbStunCheck;
		bool			mbDoubleJump;
		bool			mbPortalState;
		bool			mbRopeState;
		bool			mbInvincible;
		bool			mbLevelUpCheck;
		bool			mbKnockBackCheck;
		bool		    mbBuffCheck;

		float			mhitDelay;
		float			mStunDelay;

		std::vector<int> mLevelArr;

	};
}
