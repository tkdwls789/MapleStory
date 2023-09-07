#pragma once
#include "exComponent.h"

namespace ex
{
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		~Rigidbody();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC _hdc);


		void AddForce(math::Vector2 _force) { mForce += _force; }
		void SetMass(float _mass) { mMass = _mass; }

		void  SetFriction(float _friction) { mFriction = _friction; }
		float GetFriction() { return mFriction; }

		void SetGround(bool _ground) { mbGround = _ground; }
		bool GetGround() { return mbGround; }

		math::Vector2 GetVelocity() { return mVelocity; }
		void SetVelocity(math::Vector2 _velocity) { mVelocity = _velocity; }

		void SetVelocityY(float _velocity) { mVelocity.y = _velocity; }
		void SetVelocityX(float _velocity) { mVelocity.x = _velocity; }

		math::Vector2 GetGravity() { return mGravity; }
		void SetGravity(math::Vector2 _gravity) { mGravity = _gravity; }

		void SetLimitedVeloctyX(float _limited) { mLimitedVelocty.x = _limited; }
		float GetLimitedVeloctyX() { return mLimitedVelocty.x; }
		

	private:
		// 무게
		float mMass;
		// 마찰력
		float mFriction;
		//// 정지 마찰력
		//float mStaticFriction;
		//// 운동 마찰력
		//float mKineticFrction;
	
		// 계수
		//float mCoefficentFrction;

		// 힘
		math::Vector2 mForce;
		// 가속도
		math::Vector2 mAccelation;
		// 속도
		math::Vector2 mVelocity;
		// 중력 가속도
		math::Vector2 mGravity;

		// 가속도가 붙은 후 최대 속도를 제한하는 리미트 변수
		math::Vector2 mLimitedVelocty;

		// true -> 땅에 붙은 상태 false -> 공중에 뜬 상태
		bool mbGround;
	};

}
