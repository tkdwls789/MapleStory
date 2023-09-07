#include "exMushMomHpBar.h"
#include "exMushMom.h"
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
	MushMomHpBar::MushMomHpBar(MushMom* _owner)
		: mReductionHp(0.0f)
		, mMushMomHp(0)
		, mMushMomMaxHp(0)
		, mbMushMomHpBarOn(false)
	{
		mMushMom = _owner;
		mMushMomHpBar = ResourceManager::Load<Texture>(L"MushMomHpBar", L"..\\Resources\\Maple\\Image\\UI\\Boss_HpBar.bmp");
	}

	MushMomHpBar::~MushMomHpBar()
	{
	}

	void MushMomHpBar::Initialize()
	{
	}

	void MushMomHpBar::Update()
	{
		mMushMomHp = mMushMom->GetMushMomInfo().mHp;
		mMushMomMaxHp = mMushMom->GetMonstersInfo().mMaxHp;

		if ((int)mReductionHp >= mMushMomHp)
		{
			mReductionHp -= (float)Time::GetDeltaTime() * 9000000.0f;
		}
		else
		{
			mReductionHp = (float)mMushMomHp;
		}
		UI::Update();
	}

	void MushMomHpBar::Render(HDC _hdc)
	{

		__int64 hp = mMushMomHp;
		float fhp = (float)hp / mMushMomMaxHp;

		if (hp < mMushMomMaxHp && hp >= 0)
		{
			::TransparentBlt(_hdc, 75, 5, (int)(mMushMomHpBar->GetWidth() * fhp), mMushMomHpBar->GetHeight(), mMushMomHpBar->GetHdc()
				, 0, 0, (int)(mMushMomHpBar->GetWidth() * fhp), mMushMomHpBar->GetHeight(), RGB(255, 0, 255));
		}




		UI::Render(_hdc);
	}

	void MushMomHpBar::OnCollisionEnter(Collider* _other)
	{
	}

	void MushMomHpBar::OnCollisionStay(Collider* _other)
	{
	}

	void MushMomHpBar::OnCollisionExit(Collider* _other)
	{
	}
}
