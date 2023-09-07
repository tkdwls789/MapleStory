#include "exLogin.h"
#include "exFloor.h"
#include "exTransform.h"
#include "exAnimator.h"
#include "exCollider.h"
#include "exInput.h"

namespace ex
{
	bool Login::mbLogin = false;

	Login::Login()
	{
		mTransform = GetComponent<Transform>();
		mCollider = AddComponent<Collider>();
		mAnimator = AddComponent<Animator>();
	}

	Login::~Login()
	{

	}

	void Login::Initialize()
	{
		mAnimator->CreateAnimationFolder(L"Login",
			L"..\\Resources\\Maple\\Image\\Logo\\Login");
		mAnimator->CreateAnimationFolder(L"LoginNomal",
			L"..\\Resources\\Maple\\Image\\Logo\\LoginNomal");

		mCollider->SetSize(math::Vector2(90.0f, 90.0f));
		mAnimator->SetScale(math::Vector2(1.75f, 1.75f));
		mTransform->SetPosition(math::Vector2(770.0f, 372.0f));
	}

	void Login::Update()
	{
		math::Vector2 loginPos = mTransform->GetPosition();
		math::Vector2 loginSize = mCollider->GetSize();
		math::Vector2 mousePos = Input::GetMousePos();

		math::Vector2 left = loginPos - loginSize / 2;
		math::Vector2 right = loginPos + loginSize / 2;

		// 마우스 pos가 login 안에 들어오면
		if (left.x <= mousePos.x && mousePos.x <= right.x &&
			left.y <= mousePos.y && mousePos.y <= right.y)
		{
			mAnimator->PlayAnimation(L"Login", true);
			if (Input::GetKeyDown(eKeyCode::LButton))
			{
				mbLogin = true;
			}
		}
		else
		{
			mAnimator->PlayAnimation(L"LoginNomal", true);
			mbLogin = false;
		}

		GameObject::Update();
	}

	void Login::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Login::OnCollisionEnter(Collider* _other)
	{
	}

	void Login::OnCollisionStay(Collider* _other)
	{
	}

	void Login::OnCollisionExit(Collider* _other)
	{
	}

}