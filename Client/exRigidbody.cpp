#include "exRigidbody.h"
#include "exTime.h"
#include "exGameObject.h"
#include "exTransform.h"
#include "exSceneManager.h"
#include "exPlayer.h"

namespace ex
{
	Rigidbody::Rigidbody()
		: Component(enums::eComponentType::Rigidbody)
		, mMass(1.0f)
		, mFriction(600.0f)
		, mbGround(false)
		, mAccelation(500.0f)
	{
		mLimitedVelocty.x = 2000.0f;
		mLimitedVelocty.y = 2000.0f;
		mGravity = math::Vector2(0.0f, 2000.0f);
	}

	Rigidbody::~Rigidbody()
	{
	}

	void Rigidbody::Initialize()
	{
	}

	void Rigidbody::Update()
	{

		Player* player = SceneManager::GetPlayer();
		//이동
		// F = M x A
		// A = F / M
		mAccelation = mForce / mMass;

		// 속도에 가속도를 더한다
		mVelocity += mAccelation * Time::GetDeltaTime();

		if (mbGround)
		{
			// 땅위에 있을때
			math::Vector2 gravity = mGravity;
			gravity.Normalize();
			float dot = math::Dot(mVelocity, gravity);
			mVelocity -= gravity * dot;
		}
		else if(player->GetState() != GameObject::eState::Rope)
		{
			// 공중에 있을 때
			mVelocity += mGravity * Time::GetDeltaTime();
		}

		// 최대 속도 제한
		math::Vector2 gravity = mGravity;
		gravity.Normalize();
		float dot = math::Dot(mVelocity, gravity);
		gravity = gravity * dot;

		math::Vector2 sideVelocity = mVelocity - gravity;
		if (mLimitedVelocty.y < gravity.Length())
		{
			gravity.Normalize();
			gravity *= mLimitedVelocty.y;
		}

		if (mLimitedVelocty.x < sideVelocity.Length())
		{
			sideVelocity.Normalize();
			sideVelocity *= mLimitedVelocty.x;
		}
		mVelocity = gravity + sideVelocity;

		// 마찰력 조건 ( 적용된 힘이 없고, 속도가 0 이 아닐 )
		if (!(mVelocity == math::Vector2::Zero))
		{
			// 속도에 반대 방향으로 마찰력을 적용
			math::Vector2 friction = -mVelocity;
			friction = friction.Normalize() * mFriction * mMass * Time::GetDeltaTime();

			// 마찰력으로 인한 속도 감소량이 현재 속도보다 더 큰 경우
			if (mVelocity.Length() < friction.Length())
			{
				// 속도를 0 로 만든다.
				mVelocity = math::Vector2(0.f, 0.f);
			}
			else
			{
				// 속도에서 마찰력으로 인한 반대방향으로 속도를 차감한다.
				mVelocity += friction;
			}
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		pos = pos + mVelocity * Time::GetDeltaTime();
		tr->SetPosition(pos);
		mForce.Clear();
	}

	void Rigidbody::Render(HDC hdc)
	{
	}

}