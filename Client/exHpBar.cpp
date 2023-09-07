#include "exHpBar.h"
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
	HpBar::HpBar()
		: mReductionHp(0.0f)
	{
		mMiddleHpBar = ResourceManager::Load<Texture>(L"PlayerMiddleHpBar", L"..\\Resources\\Maple\\Image\\UI\\PlayerMiddleHpBar.bmp");

		mHpBar = ResourceManager::Load<Texture>(L"PlayerHPBar", L"..\\Resources\\Maple\\Image\\UI\\PlayerHPBar.bmp");
	}

	HpBar::~HpBar()
	{
	}

	void HpBar::Initialize()
	{
	}

	void HpBar::Update()
	{
		if ((int)mReductionHp >= SceneManager::GetPlayer()->GetInfo()->mHp)
		{
			mReductionHp -= (float)Time::GetDeltaTime() * 20000.0f;
		}
		else
		{
			mReductionHp = (float)SceneManager::GetPlayer()->GetInfo()->mHp;
		}
		UI::Update();
	}

	void HpBar::Render(HDC _hdc)
	{
		Player* player = SceneManager::GetPlayer();
		int hp = player->GetInfo()->mHp;
		float fhp = (float)hp / player->GetInfo()->mMaxHp;

		::TransparentBlt(_hdc
			, 563, 664
			,(int)(mMiddleHpBar->GetWidth() * (mReductionHp / player->GetInfo()->mMaxHp))
			, mMiddleHpBar->GetHeight()
			, mMiddleHpBar->GetHdc()
			, 0, 0
			, (int)(mMiddleHpBar->GetWidth() * (mReductionHp / player->GetInfo()->mMaxHp))
			, mMiddleHpBar->GetHeight()
			, RGB(255, 0, 255));

		::TransparentBlt(_hdc
			, 563, 664
			,(int)(mHpBar->GetWidth() * fhp)
			, mHpBar->GetHeight()
			, mHpBar->GetHdc()
			, 0, 0
			, (int)(mHpBar->GetWidth() * fhp)
			, mHpBar->GetHeight()
			, RGB(255, 0, 255));


		
		UI::Render(_hdc);
	}

	void HpBar::OnCollisionEnter(Collider* _other)
	{
	}

	void HpBar::OnCollisionStay(Collider* _other)
	{
	}

	void HpBar::OnCollisionExit(Collider* _other)
	{
	}
}
