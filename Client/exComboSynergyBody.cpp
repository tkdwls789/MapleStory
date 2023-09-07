#include "exComboSynergyBody.h"
#include "exTexture.h"
#include "exResourceManager.h"
#include "exAnimator.h"
#include "exTransform.h"
#include "exCollider.h"
#include "exTime.h"
#include "exPlayer.h"
#include "exSceneManager.h"
#include "exCollisionManager.h"
#include "exObject.h"
#include "exSound.h"
#include "exComboSynergyEffect.h"
#include "exBuffIcon.h"

namespace ex
{
	ComboSynergyBody::ComboSynergyBody(GameObject* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
	{
		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mCollider = AddComponent<Collider>();

		Player* player = SceneManager::GetPlayer();
		//// png
		Texture* image = ResourceManager::Load<Texture>(L"ComboSynergyBody"
			, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\ComboSynergy\\Body\\ComboSynergy_Body.png");

		mAnimator->CreateAnimation(L"ComboSynergyBody", image, math::Vector2(0.0f, 0.0f), math::Vector2(111.0f, 112.0f)
			, math::Vector2(111.0f, 112.0f), 1, math::Vector2(-14.0f, 0.0f), 0.1f);

		mAnimator->PlayAnimation(L"ComboSynergyBody", false);
		enums::eMoveDir playerDir = SceneManager::GetPlayer()->GetComponent<Transform>()->GetMoveDir();
		mTransform->SetPosition(player->GetPosition());

		ComboSynergyEffect* effect_0 = new ComboSynergyEffect(0);
		object::ActiveSceneAddGameObject(enums::eLayerType::BuffEffect, effect_0);

		ComboSynergyEffect* effect_1 = new ComboSynergyEffect(1);
		object::ActiveSceneAddGameObject(enums::eLayerType::BuffEffect, effect_1);

		ComboSynergyEffect* effect_2 = new ComboSynergyEffect(2);
		object::ActiveSceneAddGameObject(enums::eLayerType::BuffEffect, effect_2);

		ComboSynergyEffect* effect_3 = new ComboSynergyEffect(3);
		object::ActiveSceneAddGameObject(enums::eLayerType::BuffEffect, effect_3);

		ComboSynergyEffect* effect_4 = new ComboSynergyEffect(4);
		object::ActiveSceneAddGameObject(enums::eLayerType::BuffEffect, effect_4);

		BuffIcon* buffIcon = new BuffIcon();
		object::ActiveSceneAddGameObject(enums::eLayerType::BuffUI, buffIcon);
	}

	ComboSynergyBody::~ComboSynergyBody()
	{
	}

	void ComboSynergyBody::Initialize()
	{
	}

	void ComboSynergyBody::Update()
	{
		Player* player = SceneManager::GetPlayer();
		math::Vector2 playerPos = player->GetPosition();

		bool bCheck = player->IsBuffCheck();
		if (bCheck == false)
		{
			Destroy(this);
		}
		else
		{
			mTransform->SetPosition(playerPos);
		}
		GameObject::Update();
	}

	void ComboSynergyBody::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void ComboSynergyBody::OnCollisionEnter(Collider* _other)
	{
	}

	void ComboSynergyBody::OnCollisionStay(Collider* _other)
	{
	}

	void ComboSynergyBody::OnCollisionExit(Collider* _other)
	{
	}
}