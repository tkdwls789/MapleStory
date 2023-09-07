#include "exTime.h"

namespace ex
{

	LARGE_INTEGER Time::mCpuFrequency = {};
	LARGE_INTEGER Time::mPrevFrequency = {};
	LARGE_INTEGER Time::mCurFrequency = {};
	float Time::mDeltaTime = 0.f;


	void Time::Initialize()
	{
		// cpu 고유 진동수
		QueryPerformanceFrequency(&mCpuFrequency);

		// 프로그램 시작시 진동수
		QueryPerformanceCounter(&mPrevFrequency);
	}

	void Time::Update()
	{
		QueryPerformanceCounter(&mCurFrequency);

		float differenceFrequency =
			static_cast<float>(mCurFrequency.QuadPart - mPrevFrequency.QuadPart);

		mDeltaTime = differenceFrequency / static_cast<float>(mCpuFrequency.QuadPart);
		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
	}

	void Time::Render(HDC hdc)
	{
		//static float timeCheck = 0.0f;

		//timeCheck += m_DeltaTime;
		//if (timeCheck >= 1.0f)
		//{
		wchar_t szFloat[50] = {};
		float FPS = 1.0f / mDeltaTime;

		swprintf_s(szFloat, 50, L"FPS: %f", FPS);
		int strLen = static_cast<int>(wcsnlen_s(szFloat, 50));

		TextOut(hdc, 10, 10, szFloat, strLen);
		//timeCheck = 0.0f;
	//}
	}
}