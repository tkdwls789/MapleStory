#include "exExpBar.h"
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
	ExpBar::ExpBar()
		: mIncreaseExpBar(0.0f)
	{
		mEmptyExpBar = ResourceManager::Load<Texture>(L"PlayerEmptyExpBar", L"..\\Resources\\Maple\\Image\\UI\\PlayerEmptyExpBar_1280.bmp");
		mExpBar = ResourceManager::Load<Texture>(L"PlayerExpBar", L"..\\Resources\\Maple\\Image\\UI\\PlayerExpBar.bmp");

		mAnimator->CreateAnimation(L"PlayerEmptyExpBar", mEmptyExpBar, math::Vector2(0.0f, 0.0f), math::Vector2(1280.0f, 13.0f)
			, math::Vector2(1280.0f, 13.0f), 1);

		mTransform->SetPosition(math::Vector2(640.0f, 714.0f));
		mAnimator->SetAffectedCamera(false);


		mAnimator->PlayAnimation(L"PlayerEmptyExpBar", false);
	}

	ExpBar::~ExpBar()
	{
	}

	void ExpBar::Initialize()
	{
	}

	void ExpBar::Update()
	{
		Player* player = SceneManager::GetPlayer();
		float Exp = player->GetInfo()->mExp;
		float maxExp = player->GetInfo()->mMaxExp;

		if (Exp >= maxExp)
		{
			// 현재 경험치가 Max 경험치를 넘으면 레벨업조건 달성
			player->SetLevelUpCheck(true);
			player->GetInfo()->mExp -= maxExp;
			player->GetInfo()->mMaxExp *= 1.5f;
		}
		GameObject::Update();
	}

	void ExpBar::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);

		Player* player = SceneManager::GetPlayer();
		float Exp = player->GetInfo()->mExp;
		float fExp = (Exp / (player->GetInfo()->mMaxExp));

		::TransparentBlt(_hdc, 30, 708, (int)(mExpBar->GetWidth() * fExp), mExpBar->GetHeight(), mExpBar->GetHdc()
			, 0, 0, (int)(mExpBar->GetWidth() * fExp), mExpBar->GetHeight(), RGB(255, 0, 255));
	}

	void ExpBar::OnCollisionEnter(Collider* _other)
	{
	}

	void ExpBar::OnCollisionStay(Collider* _other)
	{
	}

	void ExpBar::OnCollisionExit(Collider* _other)
	{
	}
}
