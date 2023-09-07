#include "exSkillSlot.h"
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
	SkillSlot::SkillSlot()
	{
		mSkillSlot = ResourceManager::Load<Texture>(L"PlayerSkillSlot", L"..\\Resources\\Maple\\Image\\UI\\QuickSlot_Back.png");

		mAnimator->CreateAnimation(L"PlayerSkillSlot", mSkillSlot, math::Vector2(0.0f, 0.0f), math::Vector2(243.0f, 79.0f)
			, math::Vector2(243.0f, 79.0f), 1);
		mTransform->SetPosition(math::Vector2(1157.0f, 666.0f));
		mAnimator->SetAffectedCamera(false);
		mAnimator->SetScale(math::Vector2(1.0f, 1.0f));
		mAnimator->PlayAnimation(L"PlayerSkillSlot", false);
	}

	SkillSlot::~SkillSlot()
	{
	}

	void SkillSlot::Initialize()
	{
	}

	void SkillSlot::Update()
	{
		UI::Update();
	}

	void SkillSlot::Render(HDC _hdc)
	{
		UI::Render(_hdc);
	}

	void SkillSlot::OnCollisionEnter(Collider* _other)
	{
	}

	void SkillSlot::OnCollisionStay(Collider* _other)
	{
	}

	void SkillSlot::OnCollisionExit(Collider* _other)
	{
	}
}
