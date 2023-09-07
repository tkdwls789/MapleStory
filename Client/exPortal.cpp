#include "exPortal.h"
#include "exResourceManager.h"
#include "exTexture.h"
#include "exAnimator.h"
#include "exSceneManager.h"
#include "exInput.h"
#include "exCollider.h"
#include "exPlayer.h"
#include "exTransform.h"
#include "exSound.h"

namespace ex
{
	Portal::Portal()
		: mPortalSound(nullptr)
	{
		mPortalSound = ResourceManager::Load<Sound>(L"PortalSound", L"..\\Resources\\Maple\\Sound\\Portal\\Portal.wav");
		mPortalSound->SetVolume(100.0f);
	}
	Portal::~Portal()
	{
	}
	void Portal::Initialize()
	{

		mAnimator = AddComponent<Animator>();
		mCollider = AddComponent<Collider>();
		mAnimator->CreateAnimationFolder(L"Portal",
			L"..\\Resources\\Maple\\Image\\Portal", math::Vector2(0.0f, -50.0f));

		// 포탈 collider 사이즈 설정
		mCollider->SetSize(math::Vector2(45.0f, 80.0f));
		// 포탈 스케일 설정
		mAnimator->SetScale(math::Vector2(0.8f, 0.8f));

		mAnimator->PlayAnimation(L"Portal", true);
	}

	void Portal::Update()
	{
		//Animator* potalAt = GetComponent<Animator>();
		//potalAt->PlayAnimation(L"Potal", true);

		GameObject::Update();
	}

	void Portal::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Portal::OnCollisionEnter(Collider* _other)
	{
		Player* player = dynamic_cast<Player*>(_other->GetOwner());

		if (player != nullptr)
		{
			player->SetPotalState(true);
		}

	}
	void Portal::OnCollisionStay(Collider* _other)
	{
		bool portalState = SceneManager::GetPlayer()->IsPotalState();
		std::wstring ActiveSceneName = SceneManager::GetActiveScene()->GetName();
		if (portalState && Input::GetKeyDown(eKeyCode::Up))
		{
			mPortalSound->Play(false);
			if (ActiveSceneName == L"StageScene")
			{
				SceneManager::LoadScene(L"MushMomScene");
			}
			else if (ActiveSceneName == L"MushMomScene")
			{
				SceneManager::LoadScene(L"Stage2Scene");
				SceneManager::SetPortalCheck(false);
			}
			else if (ActiveSceneName == L"Stage2Scene")
			{
				SceneManager::LoadScene(L"Stage3Scene");
			}
			else if (ActiveSceneName == L"Stage3Scene")
			{
				SceneManager::LoadScene(L"BossScene");
			}
			else if (ActiveSceneName == L"BossScene")
			{
				SceneManager::LoadScene(L"BossScene2");
			}
			else if (ActiveSceneName == L"BossScene2")
			{
				SceneManager::LoadScene(L"EndScene");
			}
		}
	}
	void Portal::OnCollisionExit(Collider* _other)
	{
		Player* player = dynamic_cast<Player*>(_other->GetOwner());

		if (player != nullptr)
		{
			player->SetPotalState(false);
		}
		std::wstring ActiveSceneName = SceneManager::GetActiveScene()->GetName();
		ActiveSceneName.clear();
	}
}