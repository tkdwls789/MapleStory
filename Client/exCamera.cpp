#include "exCamera.h"
#include "exTexture.h"
#include "exApplication.h"
#include "exTransform.h"
#include "exInput.h"
#include "exTime.h"

extern ex::Application application;

namespace ex
{
	// static 변수 전역초기화
	math::Vector2			Camera::mResolution = math::Vector2::Zero;
	math::Vector2			Camera::mLookPosition = math::Vector2::Zero;
	math::Vector2			Camera::mDistance = math::Vector2::Zero;
	math::Vector2			Camera::mWidthLimit = math::Vector2::Zero;
	math::Vector2			Camera::mHeightLimit = math::Vector2::Zero;
	std::list<CameraEffect> Camera::mlistCamEffect = {};
	Texture*				Camera::mWhiteText = nullptr;
	Texture*				Camera::mBlackText = nullptr;
	float					Camera::mExceedX = 0.0f;
	float					Camera::mExceedY = 0.0f;

	bool Camera::mbColliderCheck = false;

	GameObject* Camera::mTargetObj = nullptr;
	//math::Vector2 Camera::mCameraLimit = math::Vector2::Zero;

	Camera::Camera()
	{
	}

	Camera::~Camera()
	{
	}

	void Camera::Initialize()
	{
		mResolution = application.GetSize();

		// LookPositon(카메라가 바라보는 위치)에 해상도x,y의 절반값(화면의 중심) 복사
		// math.h에서 operator/을 만들어서 가능
		mLookPosition = mResolution / 2.0f;

		mWhiteText = Texture::Create(L"WhiteTex", (UINT)mResolution.x, (UINT)mResolution.y, RGB(255, 255, 255));
		mBlackText = Texture::Create(L"BlackTex", (UINT)mResolution.x, (UINT)mResolution.y, RGB(0, 0, 0));

	}

	void Camera::Update()
	{
		if (Input::GetKeyDown(eKeyCode::Q))
		{
			if (mbColliderCheck)
			{
				mbColliderCheck = false;
			}
			else
			{
				mbColliderCheck = true;
			}

		}

		// 만약 GameObject* 타입 타겟이 있으면
		if (mTargetObj)
		{
			// 타겟의 이동값을 tr에 저장하겠다
			//Transform* tr = m_Target->GetComponent<Transform>();
			Transform* tr = mTargetObj->GetTransform();
			// tr(GameObject* mTarget)의 현재 좌표를 카메라가 바라보는 위치에 복사
			mLookPosition = tr->GetPosition();
		}
		else
		{
			// 타겟 설정이 nullptr이면 가운데를 바라보게 설정
			mLookPosition = math::Vector2(640.0f, 360.0f);
		}

		// 위에 if문이 성공했으면 GameObject의 m_LookPosition(현재좌표)에
		// 윈도우 창 해상도 x,y의 절반값(카메라가 바라보는 곳의 초기값)을 뺀 값을
		// m_Distance에 복사(카메라가 바라보는곳(해상도 중심)에서 GameObject가 있는 좌표에
		// 카메라가 바라보는 곳을 옮긴다
		// 즉 카메라가 바라보는 곳과 실제 윈도우 창에 그려지는 GameObject의 오차거리를 구해서 저장한다 
		mDistance = mLookPosition - (mResolution / 2.0f);

		// 이미지의 x의 왼쪽 최대 값 (이미지를 넘어서 윈도우 화면이 보이지않는 값)
		// 보다 작아지지 않게(왼쪽으로가면 -= x) 리미트 값으로 고정함
		if (mDistance.x <= mWidthLimit.x)
		{
			mExceedX = mWidthLimit.x - mDistance.x;
			mDistance.x = mWidthLimit.x;
		}
		else if (mDistance.x >= mWidthLimit.y)
		{
			mExceedX = mWidthLimit.y - mDistance.x;
			mDistance.x = mWidthLimit.y;
		}
		else
		{
			mExceedX = 0.0f;
		}

		if (mDistance.y <= mHeightLimit.x)
		{
			mExceedY = mHeightLimit.x - mDistance.y;
			mDistance.y = mHeightLimit.x;
		}
		else if (mDistance.y >= mHeightLimit.y)
		{
			mExceedY = mHeightLimit.y - mDistance.y;
			mDistance.y = mHeightLimit.y;
		}
		else
		{
			mExceedY = 0.0f;
		}
	}

	void Camera::Render(HDC _hdc)
	{
		// 이벤트 없으면 리턴
		if (mlistCamEffect.empty())
		{
			return;
		}

		CameraEffect& effect = mlistCamEffect.front();

		effect.curTime += Time::GetDeltaTime();

		float ratio = effect.curTime / effect.duration;

		if (ratio < 0.f)
		{
			ratio = 0.f;
		}
		if (ratio > 1.f)
		{
			ratio = 1.f;
		}

		int alpha = 0;

		// 이벤트에 따라서 알파값을 설정
		if (effect.eEffect == CAMERA_EFFECT::FADE_OUT)
		{
			alpha = (int)(255.f * ratio);
		}
		else if (effect.eEffect == CAMERA_EFFECT::FADE_IN)
		{
			alpha = (int)(255.f * (1.f - ratio));
		}
		else if (effect.eEffect == CAMERA_EFFECT::Pause)
		{
			alpha = (int)255.f;
		}

		// AlphaBlend 셋팅값 설정
		BLENDFUNCTION bf = {};
		bf.BlendOp = AC_SRC_OVER; // 원본과 대상 이미지를 합친다는 의미
		bf.BlendFlags = 0;
		bf.AlphaFormat = 0;
		bf.SourceConstantAlpha = alpha; // 고정 알파값 설정

		if (effect.textColor == RGB(255, 255, 255))
		{
			::AlphaBlend(_hdc,
				0, 0
				, (int)mWhiteText->GetWidth()
				, (int)mWhiteText->GetHeight()
				, mWhiteText->GetHdc()
				, 0, 0
				, (int)mWhiteText->GetWidth()
				, (int)mWhiteText->GetHeight()
				, bf);
		}
		else if (effect.textColor == RGB(0, 0, 0))
		{
			::AlphaBlend(_hdc,
				0, 0
				, (int)mBlackText->GetWidth()
				, (int)mBlackText->GetHeight()
				, mBlackText->GetHdc()
				, 0, 0
				, (int)mBlackText->GetWidth()
				, (int)mBlackText->GetHeight()
				, bf);
		}


		if (effect.curTime > effect.duration)
		{
			effect.eEffect = CAMERA_EFFECT::NONE;
			mlistCamEffect.pop_front();
		}
	}

	void Camera::FadeIn(float _duration, COLORREF _color)
	{
		CameraEffect ef = {};
		ef.eEffect = CAMERA_EFFECT::FADE_IN;
		ef.duration = _duration;
		ef.curTime = 0.f;
		ef.textColor = _color;

		mlistCamEffect.push_back(ef);
	}

	void Camera::FadeOut(float _duration, COLORREF _color)
	{
		CameraEffect ef = {};
		ef.eEffect = CAMERA_EFFECT::FADE_OUT;
		ef.duration = _duration;
		ef.curTime = 0.f;
		ef.textColor = _color;

		mlistCamEffect.push_back(ef);
	}

	void Camera::Pause(float _duration, COLORREF _color)
	{
		CameraEffect ef = {};
		ef.eEffect = CAMERA_EFFECT::Pause;
		ef.duration = _duration;
		ef.curTime = 0.f;
		ef.textColor = _color;

		mlistCamEffect.push_back(ef);
	}
}