#include "exEndScene.h"
#include "exSpriteRenderer.h"
#include "exObject.h"
#include "exInput.h"
#include "exTexture.h"
#include "exResourceManager.h"
#include "exSound.h"
#include "exBackGround.h"
#include "exTransform.h"
#include "exCamera.h"
#include "exAnimator.h"
#include "exCollisionManager.h"
#include "exPlayer.h"



namespace ex
{
	EndScene::EndScene()
		: mEndSound(nullptr)
	{
	}

	EndScene::~EndScene()
	{
	}

	void EndScene::Initialize()
	{
	}

	void EndScene::Update()
	{
		Scene::Update();
	}

	void EndScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);
	}
	void EndScene::SceneIN()
	{
		Texture* image = ResourceManager::Load<Texture>(L"EndBackGroundImgae"
			, L"..\\Resources\\Maple\\Image\\Logo\\EndScene.bmp");

		BackGround* bg = object::Instantiate<BackGround>(enums::eLayerType::Background);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(math::Vector2(1.0f, 1.0f));
		bgsr->SetAffectCamera(true);
		//bgsr->SetAlpha(0.2f);
		bg->GetComponent<Transform>()->SetPosition(math::Vector2(640.0f, 360.0f));


		Player* player = SceneManager::GetPlayer();

		player->SetBuffCheck(false);
		
		mEndSound = ResourceManager::Load<Sound>(L"EndSound", L"..\\Resources\\Maple\\Sound\\Stage\\Title.wav");
		mEndSound->Play(true);

		Camera::SetTarget(nullptr);
		Camera::FadeIn(1.f, RGB(0, 0, 0));
	}

	void EndScene::SceneOut()
	{
		//mEndSound->Stop(true);
		//Camera::SetTarget(nullptr);
		CollisionManager::Clear();
	}
}
