#include "exMpBar.h"
#include "exPlayer.h"
#include "exInput.h" 
#include "exTime.h"
#include "exResourceManager.h"
#include "exTexture.h"
#include "exObject.h"
#include "exCollisionManager.h"
#include "exSceneManager.h"
#include "exSpriteRenderer.h"
// Component
#include "exTransform.h"
#include "exAnimator.h"
#include "exCollider.h"


namespace ex
{
	MpBar::MpBar()
		: mReductionMp(0.0f)
	{
		mMiddleMpBar = ResourceManager::Load<Texture>(L"PlayerMiddleMpBar", L"..\\Resources\\Maple\\Image\\UI\\PlayerMiddleMpBar.bmp");
		mMpBar = ResourceManager::Load<Texture>(L"PlayerMpBar", L"..\\Resources\\Maple\\Image\\UI\\PlayerMpBar.bmp");

	}

	MpBar::~MpBar()
	{
	}

	void MpBar::Initialize()
	{
	}

	void MpBar::Update()
	{
		if ((int)mReductionMp >= SceneManager::GetPlayer()->GetInfo()->mMp)
		{
			mReductionMp -= (float)Time::GetDeltaTime() * 1000.f;
		}
		else
		{
			mReductionMp = (float)SceneManager::GetPlayer()->GetInfo()->mMp;
		}
		UI::Update();
	}

	void MpBar::Render(HDC _hdc)
	{

		Player* player = SceneManager::GetPlayer();
		int Mp = player->GetInfo()->mMp;
		float fhp = (float)Mp / player->GetInfo()->mMaxMp;

		::TransparentBlt(_hdc, 563, 680, (int)(mMiddleMpBar->GetWidth() * (mReductionMp / player->GetInfo()->mMaxMp)), mMiddleMpBar->GetHeight(), mMiddleMpBar->GetHdc()
			, 0, 0, (int)(mMiddleMpBar->GetWidth() * (mReductionMp / player->GetInfo()->mMaxMp)), mMiddleMpBar->GetHeight(), RGB(255, 0, 255));

		::TransparentBlt(_hdc, 563, 680, (int)(mMpBar->GetWidth() * (mReductionMp / player->GetInfo()->mMaxMp)), mMpBar->GetHeight(), mMpBar->GetHdc()
			, 0, 0, (int)(mMpBar->GetWidth() * (mReductionMp / player->GetInfo()->mMaxMp)), mMpBar->GetHeight(), RGB(255, 0, 255));

		UI::Render(_hdc);
	}

	void MpBar::OnCollisionEnter(Collider* _other)
	{
	}

	void MpBar::OnCollisionStay(Collider* _other)
	{
	}

	void MpBar::OnCollisionExit(Collider* _other)
	{
	}
}
