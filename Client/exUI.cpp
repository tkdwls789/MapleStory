#include "exUI.h"
#include "exPlayer.h"
#include "exInput.h" 
#include "exTime.h"
#include "exResourceManager.h"
#include "exTexture.h"
#include "exObject.h"
#include "exCollisionManager.h"
#include "exSceneManager.h"
// Component
#include "exTransform.h"
#include "exAnimator.h"
#include "exCollider.h"

namespace ex
{
	UI::UI()
	{
		mTransform = GetComponent<Transform>();
		mCollider = AddComponent<Collider>();
		mAnimator = AddComponent<Animator>();
	}

	UI::~UI()
	{
	}

	void UI::Initialize()
	{
	}

	void UI::Update()
	{
		GameObject::Update();
	}

	void UI::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void UI::OnCollisionEnter(Collider* _other)
	{
	}

	void UI::OnCollisionStay(Collider* _other)
	{
	}

	void UI::OnCollisionExit(Collider* _other)
	{
	}
}
