#include "exApplication.h"
#include "exInput.h"
#include "exTime.h"
#include "exTitleScene.h"
#include "exSceneManager.h"
#include "exCamera.h"
#include "exCollisionManager.h"
#include "exSoundManager.h"
#include "exResourceManager.h"


ex::Application::Application()
	: mHwnd(NULL)
	, mHdc(NULL)
	, mBackBuffer(NULL)
	, mBackHdc(NULL)
	, mWidth(0)
	, mHeight(0)
{
	
}

ex::Application::~Application()
{

}

void ex::Application::Initialize(HWND Hwnd)
{
	mHwnd = Hwnd;
	mHdc = ::GetDC(mHwnd);
	
	mWidth = 1280;
	mHeight = 720;

	RECT rc = { 0, 0, static_cast<LONG>(mWidth), static_cast<LONG>(mHeight)};
	::AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	::SetWindowPos(mHwnd,
		nullptr, 0, 0,
		rc.right - rc.left, 
		rc.bottom - rc.top,
		0);

	::ShowWindow(mHwnd, true);

	// 내가 설정한 윈도우 해상도와  동일한 비트맵 생성
	mBackBuffer = ::CreateCompatibleBitmap(mHdc, mWidth, mHeight);

	// 새로 생성한 비트맵을 가리키는 DC 생성
	mBackHdc = ::CreateCompatibleDC(mHdc);

	// 새로 생성한 비트맵과 DC를 서로 연결
	HBITMAP defaultBitmap = (HBITMAP)::SelectObject(mBackHdc, mBackBuffer);

	// 기존 디폴트 비트맵 삭제
	::DeleteObject(defaultBitmap);

	Time::Initialize();
	Input::Initialize();
	Camera::Initialize();
	SoundManager::Initialize();
	CollisionManager::Initialize();
	SceneManager::Initialize();
}

void ex::Application::Run()
{
	Update();
	Render();
}

void ex::Application::Update()
{
	Time::Update();
	Input::Update();
	Camera::Update();
	CollisionManager::Update();
	SceneManager::Update();

}


void ex::Application::Render()
{
	// 배경색 변경
	HBRUSH brush = CreateSolidBrush(RGB(125, 125, 125));
	HBRUSH oldBrush = (HBRUSH)SelectObject(mBackHdc, brush);
	// 사각형으로 덮어쓰기
	::Rectangle(mBackHdc, -1, -1, mWidth + 1, mHeight + 1);

	CollisionManager::Render(mBackHdc);
	SceneManager::Render(mBackHdc);
	Camera::Render(mBackHdc);
	Time::Render(mBackHdc);

	::BitBlt(mHdc, 0, 0, mWidth, mHeight,
		mBackHdc, 0, 0, SRCCOPY);
}

void ex::Application::Release()
{
	// 매니저 클래스들은 객체가 생성이 되지않기 때문에 소멸자가 호출되지않음 해제 함수를 따로 만들어서 처리해야함 
	// 윈도우핸들, DC 삭제
	ReleaseDC(mHwnd, mHdc);

	DeleteDC(mBackHdc);
	DeleteObject(mBackBuffer);
}








