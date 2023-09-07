#pragma once
#include "exGameObject.h"

namespace ex
{
	class Transform;
	class Animator;
	class Collider;
	class Rigidbody;

	class Monsters :public GameObject
	{
	public:
		struct MonstersInfo
		{
			__int64 mHp;
			__int64 mMaxHp;
			int mDamage;
			int mLevel;
			float mSpeed;
			float mExp;
		};

		Monsters();
		virtual ~Monsters();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(class Collider* _other) override;
		virtual void OnCollisionStay(class Collider* _other) override;
		virtual void OnCollisionExit(class Collider* _other) override;

		void SetAnimator(Animator* _animator) { mAnimator = _animator; }
		void SetTransform(Transform* _transform) { mTransform = _transform; }
		void SetRigidbodyr(Rigidbody* _rigidbody) { mRigidbody = _rigidbody; }
		void SetAnimator(Collider* _collider) { mCollider = _collider; }
		void SetMonsterState(eMonsterState _state) { mMonsterState = _state; }
		void SetMonsterDir(enums::eMoveDir _dir) { mDirection = _dir; }

		Transform* GetTransform() { return mTransform; }


		eMonsterState GetMonstersState() { return mMonsterState; }
		void SetMonstersState(eMonsterState _state) { mMonsterState = _state; }

		MonstersInfo GetMonstersInfo() { return mMonstersInfo; }
		void SetMonstersInfo(MonstersInfo _monsters) { mMonstersInfo = _monsters; }

		void ReductiongHp(int _damage) { mMonstersInfo.mHp -= _damage;}
	protected:
		enums::eMoveDir mDirection;
		Animator* mAnimator;
		Transform* mTransform;
		Rigidbody* mRigidbody;
		Collider* mCollider;

		eMonsterState mMonsterState;
		MonstersInfo mMonstersInfo;

		float mIdleDelay;
		float mMoveDelay;
		float mMoveTime;
		float mHitDelay;
	};
}