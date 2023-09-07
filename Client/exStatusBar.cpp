#include "exStatusBar.h"
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
	StatusBar::StatusBar()
	{
		mStatusBar = ResourceManager::Load<Texture>(L"PlayerStatusBar", L"..\\Resources\\Maple\\Image\\UI\\StatusBar.bmp");

		mAnimator->CreateAnimation(L"PlayerStatusBar", mStatusBar, math::Vector2(0.0f, 0.0f), math::Vector2(204.0f, 70.0f)
			, math::Vector2(204.0f, 70.0f), 1);
		mTransform->SetPosition(math::Vector2(640.0f, 671.0f));
		mAnimator->SetAffectedCamera(false);
		mAnimator->SetScale(math::Vector2(1.0f, 1.0f));
		mAnimator->PlayAnimation(L"PlayerStatusBar", false);
	}

	StatusBar::~StatusBar()
	{
	}

	void StatusBar::Initialize()
	{
	}

	void StatusBar::Update()
	{
		UI::Update();
	}

	void StatusBar::Render(HDC _hdc)
	{
		UI::Render(_hdc);
	}

	void StatusBar::OnCollisionEnter(Collider* _other)
	{
	}

	void StatusBar::OnCollisionStay(Collider* _other)
	{
	}

	void StatusBar::OnCollisionExit(Collider* _other)
	{
	}
}
