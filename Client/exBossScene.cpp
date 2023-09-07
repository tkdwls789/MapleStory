#include "exBossScene.h"
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
#include "exPapulatus.h"
#include "exCollisionManager.h"
#include "exFloor.h"
#include "exWall.h"
#include "exPapulatusHpBar.h"
#include "exSound.h"
#include "exPortal.h"

namespace ex
{
	BossScene::BossScene()
		: mBossSceneSound(nullptr)
		, mPortal(nullptr)
	{
	}

	BossScene::~BossScene()
	{
	}

	void BossScene::Initialize()
	{
		Papulatus* papulatus = object::Instantiate<Papulatus>(enums::eLayerType::Monster);
		papulatus->Initialize();
		Transform* papulatusTr = papulatus->GetComponent<Transform>();
		papulatusTr->SetPosition(math::Vector2(900.0f, 410.0f));

		PapulatusHpBar* papulatusHpBar = new PapulatusHpBar(papulatus);
		object::ActiveSceneAddGameObject(enums::eLayerType::UI, papulatusHpBar);

		// 바닥 1층
		Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* col = floor1->GetComponent<Collider>();
		Transform* tr1 = floor1->GetComponent<Transform>();
		col = floor1->AddComponent<Collider>();
		col->SetSize(math::Vector2(3000.0f, 1000.0f));
		tr1 = floor1->GetComponent<Transform>();
		tr1->SetPosition(math::Vector2(680.0f, 1005.0f));

		Floor* floor2 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* col2 = floor2->GetComponent<Collider>();
		Transform* tr2 = floor2->GetComponent<Transform>();
		col2 = floor2->AddComponent<Collider>();
		col2->SetSize(math::Vector2(200.0f, 2.0f));
		tr2 = floor2->GetComponent<Transform>();
		tr2->SetPosition(math::Vector2(-70.0f, 305.0f));

		Floor* floor3 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* col3 = floor3->GetComponent<Collider>();
		Transform* tr3 = floor3->GetComponent<Transform>();
		col3 = floor3->AddComponent<Collider>();
		col3->SetSize(math::Vector2(202.0f, 2.0f));
		tr3 = floor3->GetComponent<Transform>();
		tr3->SetPosition(math::Vector2(186.0f, 275.0f));

		Floor* floor4 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* col4 = floor4->GetComponent<Collider>();
		Transform* tr4 = floor4->GetComponent<Transform>();
		col4 = floor4->AddComponent<Collider>();
		col4->SetSize(math::Vector2(202.0f, 2.0f));
		tr4 = floor4->GetComponent<Transform>();
		tr4->SetPosition(math::Vector2(410.0f, 345.0f));


		Floor* floor5 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* col5 = floor5->GetComponent<Collider>();
		Transform* tr5 = floor5->GetComponent<Transform>();
		col5 = floor5->AddComponent<Collider>();
		col5->SetSize(math::Vector2(202.0f, 2.0f));
		tr5 = floor5->GetComponent<Transform>();
		tr5->SetPosition(math::Vector2(898.0f, 276.0f));

		Floor* floor6 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* col6 = floor6->GetComponent<Collider>();
		Transform* tr6 = floor6->GetComponent<Transform>();
		col6 = floor6->AddComponent<Collider>();
		col6->SetSize(math::Vector2(190.0f, 2.0f));
		tr6 = floor6->GetComponent<Transform>();
		tr6->SetPosition(math::Vector2(1125.0f, 315.0f));

		Floor* floor7 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* col7 = floor7->GetComponent<Collider>();
		Transform* tr7 = floor7->GetComponent<Transform>();
		col7 = floor7->AddComponent<Collider>();
		col7->SetSize(math::Vector2(190.0f, 2.0f));
		tr7 = floor7->GetComponent<Transform>();
		tr7->SetPosition(math::Vector2(1375.0f, 368.0f));

		Floor* floor8 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* col8 = floor8->GetComponent<Collider>();
		Transform* tr8 = floor8->GetComponent<Transform>();
		col8 = floor8->AddComponent<Collider>();
		col8->SetSize(math::Vector2(150.0f, 2.0f));
		tr8 = floor8->GetComponent<Transform>();
		tr8->SetPosition(math::Vector2(1585.0f, 315.0f));

		// 왼쪽 벽
		Wall* leftWall = object::Instantiate<Wall>(enums::eLayerType::Wall);
		Collider* leftwallCol = leftWall->AddComponent<Collider>();
		leftwallCol->SetSize(math::Vector2(1000.0f, 1500.0f));
		Transform* leftwalltr = leftWall->GetComponent<Transform>();
		leftwalltr->SetPosition(math::Vector2(-913.0f, 360.0f));

		// 오른쪽 벽
		Wall* RightWall = object::Instantiate<Wall>(enums::eLayerType::Wall);
		Collider* RightwallCol = RightWall->AddComponent<Collider>();
		RightwallCol->SetSize(math::Vector2(1000.0f, 1500.0f));
		Transform* Rightwalltr = RightWall->GetComponent<Transform>();
		Rightwalltr->SetPosition(math::Vector2(2190.0f, 360.0f));

		// 포탈
		mPortal = object::Instantiate<Portal>(enums::eLayerType::Potal);
		mPortal->Initialize();
		Transform* portalTr = mPortal->GetComponent<Transform>();
		portalTr->SetPosition(math::Vector2(-1000.0f, -1000.0f));
	}

	void BossScene::Update()
	{
		math::Vector2 pos = SceneManager::GetPlayer()->GetPosition();
		bool bCheck = SceneManager::GetPortalCheck();
		if (bCheck)
		{
			Transform* portalTr = mPortal->GetComponent<Transform>();
			portalTr->SetPosition(math::Vector2(1070.0f, 460.0f));
		}
		Scene::Update();
	}

	void BossScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);
	}
	void BossScene::SceneIN()
	{
		Texture* image = ResourceManager::Load<Texture>(L"BossBackGroundImgae"
			, L"..\\Resources\\Maple\\Image\\Map\\BossStage2.bmp");

		BackGround* bg = object::Instantiate<BackGround>(enums::eLayerType::Background);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(math::Vector2(1.0f, 1.25f));
		bgsr->SetAffectCamera(true);
		bg->GetComponent<Transform>()->SetPosition(math::Vector2(640.0f, 360.f));

		bg->SetAutoCameraLimit();
		math::Vector2 widthLimit = math::Vector2(bg->GetLimitLeft(), bg->GetLimitRight());
		math::Vector2 heightLimit = math::Vector2(bg->GetLimitUp(), bg->GetLimitDown());
		Camera::SetLimitDistance(widthLimit, heightLimit);

		Player* player = SceneManager::GetPlayer();
		// 게임오브젝트는 생성자에서 AddComponent<Transform>()을 선언함
		Transform* playerTF = player->GetComponent<Transform>();
		playerTF->SetPosition(math::Vector2(-190.0f, 380.0f));
		// 플레이어가 중력을 받기위해 
		player->GetComponent<Rigidbody>()->SetGround(false);

		Animator* playerAt = player->GetComponent<Animator>();
		// 카메라의 영향을 true || false
		playerAt->SetAffectedCamera(true);

		// 씬에 들어갈때 카메라 타겟 플레이어한테 세팅
		Camera::SetTarget(player);
		Camera::FadeIn(1.0f, RGB(0, 0, 0));

		mBossSceneSound = ResourceManager::Load<Sound>(L"BossSceneSound", L"..\\Resources\\Maple\\Sound\\Stage\\PapulatusRoom.wav");
		mBossSceneSound->Play(true);

		// 씬에 들어갈때 충돌체크 세팅
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Floor, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Effect, enums::eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Effect, enums::eLayerType::Player, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Effect, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Potal, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Monster, enums::eLayerType::Floor, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Wall, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Monster, enums::eLayerType::Wall, true);
	}
	void BossScene::SceneOut()
	{
		mBossSceneSound->Stop(true);
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();
		SceneManager::SetPortalCheck(false);
	}
}
