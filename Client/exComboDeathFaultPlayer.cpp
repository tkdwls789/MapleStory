#include "exComboDeathFaultPlayer.h"
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
#include "exAnimation.h"
#include "exMonsters.h"
#include "exDamageManager.h"
#include "exComboDeathFaultScreen.h"
#include "exSound.h"

namespace ex
{
	ComboDeathFaultPlayer::ComboDeathFaultPlayer(GameObject* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
		, mComboDeathFaultSound(nullptr)
	{
		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();

		//// png
		Texture* image = ResourceManager::Load<Texture>(L"LeftComboDeathFault"
			, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\ComboDeathFault\\ComboDeathFault_Player\\Left\\Player_Left_ComboDeathFault.png");

		mAnimator->CreateAnimation(L"LeftComboDeathFault", image, math::Vector2(0.0f, 0.0f), math::Vector2(1311.0f, 464.0f)
			, math::Vector2(1311.0f, 464.0f), 24, math::Vector2(-33.0f,0.0f), 0.05f);

		//// png
		image = ResourceManager::Load<Texture>(L"RightComboDeathFault"
			, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\ComboDeathFault\\ComboDeathFault_Player\\Right\\Player_Right_ComboDeathFault.png");

		mAnimator->CreateAnimation(L"RightComboDeathFault", image, math::Vector2(31464.0f, 0.0f), math::Vector2(1311.0f, 464.0f)
			, math::Vector2(-1311.0f, 0.0f), 24, math::Vector2(33.0f, 0.0f), 0.05f);

		mAnimator->SetScale(math::Vector2(0.85f, 0.70f));
		enums::eMoveDir playerDir = _owner->GetTransform()->GetMoveDir();
		math::Vector2 playerPos = _owner->GetPosition();

		mTransform->SetPosition(math::Vector2(playerPos));

		if (playerDir == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"LeftComboDeathFault", false);
		}
		else
		{
			mAnimator->PlayAnimation(L"RightComboDeathFault", false);
		}

		mComboDeathFaultSound = ResourceManager::Load<Sound>(L"ComboDeathFaultSound", L"..\\Resources\\Maple\\Sound\\Skill\\ComboDeathFault.wav");
		mComboDeathFaultSound->Play(false);

	}

	ComboDeathFaultPlayer::~ComboDeathFaultPlayer()
	{
	}

	void ComboDeathFaultPlayer::Initialize()
	{
	}

	void ComboDeathFaultPlayer::Update()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Player* player = SceneManager::GetPlayer();
			ComboDeathFaultScreen* comboDeathFaultScreen = new ComboDeathFaultScreen(player);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, comboDeathFaultScreen);
			Destroy(this);
		}
		GameObject::Update();
	}

	void ComboDeathFaultPlayer::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void ComboDeathFaultPlayer::OnCollisionEnter(Collider* _other)
	{
	}

	void ComboDeathFaultPlayer::OnCollisionStay(Collider* _other)
	{

	}

	void ComboDeathFaultPlayer::OnCollisionExit(Collider* _other)
	{
	}
}