#pragma once
#include "exGameObject.h"

namespace ex
{

	class BackGround : public GameObject
	{
	public:
		BackGround();
		virtual ~BackGround();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		void SetLimitLeft(float _left) { mCameraLimitLeft = _left; }
		float GetLimitLeft() { return mCameraLimitLeft; }

		void SetLimitRight(float _right) { mCameraLimitRight = _right; }
		float GetLimitRight() { return mCameraLimitRight; }

		void SetLimitUp(float _up) { mCameraLimitUp = _up; }
		float GetLimitUp() { return mCameraLimitUp; }
		
		void SetLimitDown(float _down) { mCameraLimitDown = _down; }
		float GetLimitDown() { return mCameraLimitDown; }

		void SetAutoCameraLimit();

	private:
		float mCameraLimitLeft;
		float mCameraLimitRight;
		float mCameraLimitUp;
		float mCameraLimitDown;

	};

}
