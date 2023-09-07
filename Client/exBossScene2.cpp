#include "exBossScene2.h"
#include "exPlayer.h"
#include "exSpriteRenderer.h"
#include "exObject.h"
#include "exResourceManager.h"
#include "exInput.h"
#include "exTexture.h"
#include "exTransform.h"
#include "exResourceManager.h"
#include "exBackGround.h"
#include "exCamera.h"
#include "exAnimator.h"
#include "exCollisionManager.h"
#include "exFloor.h"
#include "exPortal.h"
#include "exGatekeeper.h"
#include "exThanatos.h"
#include "exWall.h"
#include "exRope.h"
#include "exSound.h"
#include "exVonLeonHuman.h"

namespace ex
{
	BossScene2::BossScene2()
		: mBossScene2_Sound(nullptr)
		, mVonLeonDial_Sound(nullptr)
		, mPortal(nullptr)
		, mVonLeonHuman(nullptr)
	{
	}

	BossScene2::~BossScene2()
	{
	}

	void BossScene2::Initialize()
	{
		VonLeonHuman* humanVonLeon = object::Instantiate<VonLeonHuman>(enums::eLayerType::Monster);
		mVonLeonHuman = humanVonLeon;
		// 왼쪽 벽
		Wall* leftWall = object::Instantiate<Wall>(enums::eLayerType::Wall);
		Collider* leftwallCol = leftWall->AddComponent<Collider>();
		leftwallCol->SetSize(math::Vector2(300.0f, 1000.0f));
		Transform* leftwalltr = leftWall->GetComponent<Transform>();
		leftwalltr->SetPosition(math::Vector2(-1353.0f, 360.0f));

		// 오른쪽 벽
		Wall* RightWall = object::Instantiate<Wall>(enums::eLayerType::Wall);
		Collider* RightwallCol = RightWall->AddComponent<Collider>();
		RightwallCol->SetSize(math::Vector2(300.0f, 1000.0f));
		Transform* Rightwalltr = RightWall->GetComponent<Transform>();
		Rightwalltr->SetPosition(math::Vector2(2880.0f, 360.0f));

		// 바닥 1층
		Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* col1 = floor1->AddComponent<Collider>();
		Transform* tr1 = floor1->GetComponent<Transform>();
		col1->SetSize(math::Vector2(4300.0f, 200.0f));
		tr1->SetPosition(math::Vector2(640.0f, 652.0f));

		// 포탈
		mPortal = object::Instantiate<Portal>(enums::eLayerType::Potal);
		mPortal->Initialize();
		Transform* portalTr = mPortal->GetComponent<Transform>();
		//Test
		portalTr->SetPosition(math::Vector2(640.0f, 2062.0f));

	}

	void BossScene2::Update()
	{
		if (Input::GetKeyDown(eKeyCode::L))
		{
			mVonLeonHuman->Initialize();
		}
		bool bCheck = SceneManager::GetPortalCheck();
		if (bCheck)
		{
			mPortal->SetPosition(math::Vector2(2656.0f, 511.0f));
		}
		Scene::Update();
	}

	void BossScene2::Render(HDC _hdc)
	{
		Scene::Render(_hdc);
	}
	void BossScene2::SceneIN()
	{
		Texture* image = ResourceManager::Load<Texture>(L"VonLeonBackGroundImgae"
			, L"..\\Resources\\Maple\\Image\\Map\\BossStage3.bmp");

		BackGround* bg = object::Instantiate<BackGround>(enums::eLayerType::Background);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(math::Vector2(1.0f, 1.0f));
		bgsr->SetAffectCamera(true);
		//bgsr->SetAlpha(0.2f);
		bg->GetComponent<Transform>()->SetPosition(math::Vector2(640.0f, 360.f));

		bg->SetAutoCameraLimit();
		math::Vector2 widthLimit = math::Vector2(bg->GetLimitLeft(), bg->GetLimitRight());
		math::Vector2 heightLimit = math::Vector2(bg->GetLimitUp(), bg->GetLimitDown());
		Camera::SetLimitDistance(widthLimit, heightLimit);
		Camera::FadeIn(1.f, RGB(0, 0, 0));

		mVonLeonHuman->Initialize();

		Player* player = SceneManager::GetPlayer();

		// 게임오브젝트는 생성자에서 AddComponent<Transform>()을 선언함
		Transform* playerTF = player->GetComponent<Transform>();
		playerTF->SetPosition(math::Vector2(-1117.0f, 480.0f));
		//playerTF->SetPosition(math::Vector2(603.0f, 480.0f));
	
		// 플레이어가 중력을 받기위해 
		player->GetComponent<Rigidbody>()->SetGround(false);

		Animator* playerAt = player->GetComponent<Animator>();
		// 카메라의 영향을 true || false
		playerAt->SetAffectedCamera(true);

		// 씬에 들어갈때 카메라 타겟 플레이어한테 세팅
		Camera::SetTarget(player);

		mBossScene2_Sound = ResourceManager::Load<Sound>(L"VonLeonRoomSound", L"..\\Resources\\Maple\\Sound\\Stage\\VonLeonRoom.wav");
		mBossScene2_Sound->Play(true);

		mVonLeonDial_Sound = ResourceManager::Load<Sound>(L"VonLeonDial", L"..\\Resources\\Maple\\Sound\\Monster\\VonLeon\\VonLeon_Dial1.wav");
		mVonLeonDial_Sound->Play(false);


		// 씬에 들어갈때 충돌체크 세팅
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Floor, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Monster, enums::eLayerType::Effect, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Effect, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Potal, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Monster, enums::eLayerType::Floor, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Rope, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Wall, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Monster, enums::eLayerType::Wall, true);
	}
	void BossScene2::SceneOut()
	{
		mBossScene2_Sound->Stop(true);
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();
	}
}
