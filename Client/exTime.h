#pragma once
#include "exCommonInclude.h"

namespace ex
{
	class Time
	{
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC _hdc);

		__forceinline static float GetDeltaTime() { return mDeltaTime; }

	private:

		static LARGE_INTEGER mCpuFrequency;
		static LARGE_INTEGER mPrevFrequency;
		static LARGE_INTEGER mCurFrequency;
		static float mDeltaTime;


	};


}
