#include "exPapulatusHpBar.h"
#include "exPapulatus.h"
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
	PapulatusHpBar::PapulatusHpBar(Papulatus* _owner)
		: mReductionHp(0.0f)
		, mPapulatusHp(0)
		, mPapulatusMaxHp(0)
		, mbHpBarOn(false)
	{
		mPapulatus = _owner;
		mPapulatusHpBar = ResourceManager::Load<Texture>(L"PapulatusHpBar", L"..\\Resources\\Maple\\Image\\UI\\Boss_HpBar.bmp");
	}

	PapulatusHpBar::~PapulatusHpBar()
	{
	}

	void PapulatusHpBar::Initialize()
	{
	}

	void PapulatusHpBar::Update()
	{
		mPapulatusHp = mPapulatus->GetPapulatusInfo().mHp;
		mPapulatusMaxHp = mPapulatus->GetMonstersInfo().mMaxHp;

		if ((int)mReductionHp >= mPapulatusHp)
		{
			mReductionHp -= (float)Time::GetDeltaTime() * 9000000.0f;
		}
		else
		{
			mReductionHp = (float)mPapulatusHp;
		}
		UI::Update();
	}

	void PapulatusHpBar::Render(HDC _hdc)
	{

		__int64 hp = mPapulatusHp;
		float fhp = (float)hp / mPapulatusMaxHp;

		if (hp < mPapulatusMaxHp && hp >= 0)
		{
			::TransparentBlt(_hdc, 75, 5, (int)(mPapulatusHpBar->GetWidth() * fhp), mPapulatusHpBar->GetHeight(), mPapulatusHpBar->GetHdc()
				, 0, 0, (int)(mPapulatusHpBar->GetWidth() * fhp), mPapulatusHpBar->GetHeight(), RGB(255, 0, 255));
		}




		UI::Render(_hdc);
	}

	void PapulatusHpBar::OnCollisionEnter(Collider* _other)
	{
	}

	void PapulatusHpBar::OnCollisionStay(Collider* _other)
	{
	}

	void PapulatusHpBar::OnCollisionExit(Collider* _other)
	{
	}
}
