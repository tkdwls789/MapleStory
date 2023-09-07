#pragma once
#include "exComponent.h"

namespace ex
{
	class Transform : public Component
	{
	public:
		Transform();
		virtual ~Transform();

		virtual void Initialize()  override;
		virtual void Update()  override;
		virtual void Render(HDC _hdc)  override;

		// Vector2(x,y) 위치정보를 가지고있을 m_Pos변수를 세팅해주는 함수
		void SetPosition(const math::Vector2& _pos) { mPos = _pos; }
		void SetPosition(float _x, float _y) { mPos = math::Vector2(_x, _y); }

		// 각각 입력을 받을 수 있게
		void SetPositionX(float _x) { mPos.x = _x; }
		void SetPositionY(float _y) { mPos.y = _y; }

		// 세팅한 위치정보를 가지고있는 m_Pos 변수를 가져오는 함수
		math::Vector2 GetPosition() { return mPos; }

		// 각각 반환 받을 수 있게
		float GetPositionX() { return mPos.x; }
		float GetPositionY() { return mPos.y; }

		// 회전할 각도를 가질 m_Rotation 변수를 세팅하는 함수
		void SetRotation(float _rotation) { mRotation = _rotation; }

		// 세팅한 각도를 들고있는 m_Rotation을 가져오는 함수
		float GetRotation() { return mRotation; }

		void SetMoveDir(enums::eMoveDir _dir) { mMoveDir = _dir; }
		enums::eMoveDir GetMoveDir() { return mMoveDir; }

	private:
		math::Vector2	mPos;
		enums::eMoveDir mMoveDir;
		float			mRotation;
	};
}
