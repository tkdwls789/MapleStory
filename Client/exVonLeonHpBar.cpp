#include "exVonLeonHpBar.h"
#include "exVonLeon.h"
#include "exInput.h" 
#include "exTime.h"
#include "exResourceManager.h"
#include "exTexture.h"
#include "exObject.h"
#include "exCollisionManager.h"
#include "exSceneManager.h"
#include "exSpriteRenderer.h"
#include "exVonLeon.h"
// Component
#include "exTransform.h"
#include "exAnimator.h"
#include "exCollider.h"


namespace ex
{
	VonLeonHpBar::VonLeonHpBar(VonLeon* _owner)
		: mReductionHp(0.0f)
		, mVonLeonHp(0)
		, mVonLeonMaxHp(0)
		, mbHpBarOn(false)
	{
		mVonLeon = _owner;
		mVonLeonHpBar = ResourceManager::Load<Texture>(L"VonLeonHpBar", L"..\\Resources\\Maple\\Image\\UI\\Boss_HpBar.bmp");
	}

	VonLeonHpBar::~VonLeonHpBar()
	{
	}

	void VonLeonHpBar::Initialize()
	{
	}

	void VonLeonHpBar::Update()
	{
		mVonLeonHp = mVonLeon->GetVonLeonInfo().mHp;
		mVonLeonMaxHp = mVonLeon->GetMonstersInfo().mMaxHp;

		if ((int)mReductionHp >= mVonLeonHp)
		{
			mReductionHp -= (float)Time::GetDeltaTime() * 9000000.0f;
		}
		else
		{
			mReductionHp = (float)mVonLeonHp;
		}
		UI::Update();
	}

	void VonLeonHpBar::Render(HDC _hdc)
	{
		__int64 hp = mVonLeonHp;
		float fhp = (float)hp / mVonLeonMaxHp;

		if (hp < mVonLeonMaxHp && hp >= 0)
		{
			::TransparentBlt(_hdc, 75, 5, (int)(mVonLeonHpBar->GetWidth() * fhp), mVonLeonHpBar->GetHeight(), mVonLeonHpBar->GetHdc()
				, 0, 0, (int)(mVonLeonHpBar->GetWidth() * fhp), mVonLeonHpBar->GetHeight(), RGB(255, 0, 255));
		}




		UI::Render(_hdc);
	}

	void VonLeonHpBar::OnCollisionEnter(Collider* _other)
	{
	}

	void VonLeonHpBar::OnCollisionStay(Collider* _other)
	{
	}

	void VonLeonHpBar::OnCollisionExit(Collider* _other)
	{
	}
}
