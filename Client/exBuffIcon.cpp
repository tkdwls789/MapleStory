#include "exBuffIcon.h"
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
	BuffIcon::BuffIcon()
	{
		mBuffIcon = ResourceManager::Load<Texture>(L"ComboSynergyIcon"
			, L"..\\Resources\\Maple\\Image\\UI\\BuffUI\\ComboSynergyIcon.png");

		mAnimator->CreateAnimation(L"ComboSynergyIcon", mBuffIcon, math::Vector2(0.0f, 0.0f), math::Vector2(32.0f, 32.0f)
			, math::Vector2(32.0f, 32.0f), 1);

		mTransform->SetPosition(math::Vector2(1260.0f, 20.0f));
		mAnimator->SetAffectedCamera(false);


		mAnimator->PlayAnimation(L"ComboSynergyIcon", false);
	}

	BuffIcon::~BuffIcon()
	{
	}

	void BuffIcon::Initialize()
	{
	}

	void BuffIcon::Update()
	{
		Player* player = SceneManager::GetPlayer();

		if (player->IsBuffCheck() == false)
		{
			Destroy(this);
		}
		GameObject::Update();
	}

	void BuffIcon::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void BuffIcon::OnCollisionEnter(Collider* _other)
	{
	}

	void BuffIcon::OnCollisionStay(Collider* _other)
	{
	}

	void BuffIcon::OnCollisionExit(Collider* _other)
	{
	}
}
