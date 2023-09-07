#pragma once
#include "exCommonInclude.h"


namespace ex
{
	class Application
	{

	public:
		Application();
		~Application();

		void Initialize(HWND _Hwnd);
		void Run();
		void Update();
		void Render();
		void Release();

		//Hwnd(윈도우 핸들)을 반환한다.
		HWND GetHwnd() { return mHwnd; }
		HDC GetHdc() { return mHdc; }

		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }
		math::Vector2 GetSize() { return math::Vector2(static_cast<float>(mWidth), static_cast<float>(mHeight)); }

	private:
		HWND	 mHwnd;
		HDC		 mHdc;
		UINT	 mWidth;
		UINT	 mHeight;

		HDC		 mBackHdc;
		HBITMAP	 mBackBuffer;

	};
}


