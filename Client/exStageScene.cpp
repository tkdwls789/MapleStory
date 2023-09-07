#include "exStageScene.h"
#include "exPlayer.h"
#include "exSpriteRenderer.h"
#include "exGameObject.h"
#include "exObject.h"
#include "exResourceManager.h"
#include "exInput.h"
#include "exTexture.h"
#include "exTransform.h"
#include "exResourceManager.h"
#include "exBackGround.h"
#include "exCamera.h"
#include "exAnimator.h"
#include "exCollider.h"
#include "exCollisionManager.h"
#include "exSceneManager.h"
#include "exGreenMush.h"
#include "exOrangeMush.h"
#include "exFloor.h"
#include "exPapulatus.h"
#include "exPortal.h"
#include "exWall.h"
#include "exRope.h"
#include "exStatusBar.h"
#include "exSound.h"
#include "exBuff.h"

namespace ex
{

	StageScene::StageScene()
		: mStage1_Sound(nullptr)
	{
	}

	StageScene::~StageScene()
	{
	}

	void StageScene::Initialize()
	{
		// 몬스터 초록버섯 
		// 2층
		GreenMush* greenMush1 = object::Instantiate<GreenMush>(enums::eLayerType::Monster);
		Transform* grMushtr1 = greenMush1->GetComponent<Transform>();
		grMushtr1->SetMoveDir(enums::eMoveDir::Left);
		grMushtr1->SetPosition(math::Vector2(440.0f, 530.0f));
		greenMush1->SetMoveDelay(4.5f);
		greenMush1->Initialize();


		GreenMush* greenMush2 = object::Instantiate<GreenMush>(enums::eLayerType::Monster);
		Transform* grMushtr2 = greenMush2->GetComponent<Transform>();
		grMushtr2->SetMoveDir(enums::eMoveDir::Right);
		grMushtr2->SetPosition(math::Vector2(400.0f, 530.0f));
		greenMush2->SetMoveDelay(3.5f);
		greenMush2->Initialize();


		GreenMush* greenMush3 = object::Instantiate<GreenMush>(enums::eLayerType::Monster);
		Transform* grMushtr3 = greenMush3->GetComponent<Transform>();
		grMushtr3->SetMoveDir(enums::eMoveDir::Right);
		grMushtr3->SetPosition(math::Vector2(640.0f, 530.0f));
		greenMush3->SetMoveDelay(3.8f);
		greenMush3->Initialize();

		GreenMush* greenMush4 = object::Instantiate<GreenMush>(enums::eLayerType::Monster);
		Transform* grMushtr4 = greenMush4->GetComponent<Transform>();
		grMushtr4->SetMoveDir(enums::eMoveDir::Left);
		grMushtr4->SetPosition(math::Vector2(740.0f, 530.0f));
		greenMush4->SetMoveDelay(4.0f);
		greenMush4->Initialize();

		GreenMush* greenMush5 = object::Instantiate<GreenMush>(enums::eLayerType::Monster);
		Transform* grMushtr5 = greenMush5->GetComponent<Transform>();
		grMushtr5->SetMoveDir(enums::eMoveDir::Right);
		grMushtr5->SetPosition(math::Vector2(900.0f, 530.0f));
		greenMush5->SetMoveDelay(2.8f);
		greenMush5->Initialize();

		GreenMush* greenMush6 = object::Instantiate<GreenMush>(enums::eLayerType::Monster);
		Transform* grMushtr6 = greenMush6->GetComponent<Transform>();
		grMushtr6->SetMoveDir(enums::eMoveDir::Left);
		grMushtr6->SetPosition(math::Vector2(850.0f, 530.0f));
		greenMush6->SetMoveDelay(3.7f);
		greenMush6->Initialize();

		GreenMush* greenMush7 = object::Instantiate<GreenMush>(enums::eLayerType::Monster);
		Transform* grMushtr7 = greenMush7->GetComponent<Transform>();
		grMushtr7->SetMoveDir(enums::eMoveDir::Right);
		grMushtr7->SetPosition(math::Vector2(1000.0f, 530.0f));
		greenMush7->SetMoveDelay(3.1f);
		greenMush7->Initialize();

		GreenMush* greenMush8 = object::Instantiate<GreenMush>(enums::eLayerType::Monster);
		Transform* grMushtr8 = greenMush8->GetComponent<Transform>();
		grMushtr8->SetMoveDir(enums::eMoveDir::Left);
		grMushtr8->SetPosition(math::Vector2(300.0f, 530.0f));
		greenMush8->SetMoveDelay(4.2f);
		greenMush8->Initialize();


		// 몬스터 주황버섯
		// 3층
		OrangeMush* orangeMush1 = object::Instantiate<OrangeMush>(enums::eLayerType::Monster);
		Transform* orangeMushTr1 = orangeMush1->GetComponent<Transform>();
		orangeMushTr1->SetMoveDir(enums::eMoveDir::Left);
		orangeMushTr1->SetPosition(math::Vector2(800.0f, 330.0f));
		orangeMush1->SetMoveDelay(1.5f);
		orangeMush1->Initialize();

		OrangeMush* orangeMush2 = object::Instantiate<OrangeMush>(enums::eLayerType::Monster);
		Transform* orangeMushTr2 = orangeMush2->GetComponent<Transform>();
		orangeMushTr2->SetMoveDir(enums::eMoveDir::Right);
		orangeMushTr2->SetPosition(math::Vector2(700.0f, 330.0f));
		orangeMush2->SetMoveDelay(3.5f);
		orangeMush2->Initialize();

		OrangeMush* orangeMush3 = object::Instantiate<OrangeMush>(enums::eLayerType::Monster);
		Transform* orangeMushTr3 = orangeMush3->GetComponent<Transform>();
		orangeMushTr3->SetMoveDir(enums::eMoveDir::Right);
		orangeMushTr3->SetPosition(math::Vector2(600.0f, 330.0f));
		orangeMush3->SetMoveDelay(5.5f);
		orangeMush3->Initialize();

		OrangeMush* orangeMush4 = object::Instantiate<OrangeMush>(enums::eLayerType::Monster);
		Transform* orangeMushTr4 = orangeMush4->GetComponent<Transform>();
		orangeMushTr4->SetMoveDir(enums::eMoveDir::Right);
		orangeMushTr4->SetPosition(math::Vector2(430.0f, 330.0f));
		orangeMush4->SetMoveDelay(3.2f);
		orangeMush4->Initialize();

		OrangeMush* orangeMush5 = object::Instantiate<OrangeMush>(enums::eLayerType::Monster);
		Transform* orangeMushTr5 = orangeMush5->GetComponent<Transform>();
		orangeMushTr5->SetMoveDir(enums::eMoveDir::Left);
		orangeMushTr5->SetPosition(math::Vector2(900.0f, 330.0f));
		orangeMush5->SetMoveDelay(2.5f);
		orangeMush5->Initialize();

		OrangeMush* orangeMush6 = object::Instantiate<OrangeMush>(enums::eLayerType::Monster);
		Transform* orangeMushTr6 = orangeMush6->GetComponent<Transform>();
		orangeMushTr6->SetMoveDir(enums::eMoveDir::Right);
		orangeMushTr6->SetPosition(math::Vector2(880.0f, 330.0f));
		orangeMush6->SetMoveDelay(3.0f);
		orangeMush6->Initialize();

		OrangeMush* orangeMush7 = object::Instantiate<OrangeMush>(enums::eLayerType::Monster);
		Transform* orangeMushTr7 = orangeMush7->GetComponent<Transform>();
		orangeMushTr7->SetMoveDir(enums::eMoveDir::Left);
		orangeMushTr7->SetPosition(math::Vector2(330.0f, 330.0f));
		orangeMush7->SetMoveDelay(3.0f);
		orangeMush7->Initialize();

		OrangeMush* orangeMush8 = object::Instantiate<OrangeMush>(enums::eLayerType::Monster);
		Transform* orangeMushTr8 = orangeMush8->GetComponent<Transform>();
		orangeMushTr8->SetMoveDir(enums::eMoveDir::Right);
		orangeMushTr8->SetPosition(math::Vector2(490.0f, 330.0f));
		orangeMush8->SetMoveDelay(3.0f);
		orangeMush8->Initialize();

		// 3층

		GreenMush* greenMush9 = object::Instantiate<GreenMush>(enums::eLayerType::Monster);
		Transform* grMushtr9 = greenMush9->GetComponent<Transform>();
		grMushtr9->SetMoveDir(enums::eMoveDir::Left);
		grMushtr9->SetPosition(math::Vector2(640.0f, 140.0f));
		greenMush9->SetMoveDelay(4.21f);
		greenMush9->Initialize();


		GreenMush* greenMush10 = object::Instantiate<GreenMush>(enums::eLayerType::Monster);
		Transform* grMushtr10 = greenMush10->GetComponent<Transform>();
		grMushtr10->SetMoveDir(enums::eMoveDir::Right);
		grMushtr10->SetPosition(math::Vector2(440.0f, 140.0f));
		greenMush10->SetMoveDelay(3.563f);
		greenMush10->Initialize();


		GreenMush* greenMush11 = object::Instantiate<GreenMush>(enums::eLayerType::Monster);
		Transform* grMushtr11 = greenMush11->GetComponent<Transform>();
		grMushtr11->SetMoveDir(enums::eMoveDir::Left);
		grMushtr11->SetPosition(math::Vector2(840.0f, 140.0f));
		greenMush11->SetMoveDelay(3.98f);
		greenMush11->Initialize();


		OrangeMush* orangeMush9 = object::Instantiate<OrangeMush>(enums::eLayerType::Monster);
		Transform* orangeMushTr9 = orangeMush9->GetComponent<Transform>();
		orangeMushTr9->SetMoveDir(enums::eMoveDir::Right);
		orangeMushTr9->SetPosition(math::Vector2(760.0f, 140.0f));
		orangeMush9->SetMoveDelay(4.11f);
		orangeMush9->Initialize();

		OrangeMush* orangeMush10 = object::Instantiate<OrangeMush>(enums::eLayerType::Monster);
		Transform* orangeMushTr10 = orangeMush10->GetComponent<Transform>();
		orangeMushTr10->SetMoveDir(enums::eMoveDir::Left);
		orangeMushTr10->SetPosition(math::Vector2(1000.0f, 140.0f));
		orangeMush10->SetMoveDelay(3.76f);
		orangeMush10->Initialize();

		OrangeMush* orangeMush11 = object::Instantiate<OrangeMush>(enums::eLayerType::Monster);
		Transform* orangeMushTr11 = orangeMush11->GetComponent<Transform>();
		orangeMushTr11->SetMoveDir(enums::eMoveDir::Left);
		orangeMushTr11->SetPosition(math::Vector2(630, 140.0f));
		orangeMush11->SetMoveDelay(3.33f);
		orangeMush11->Initialize();

		// 1층 바닥
		Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Transform* floorTr = floor1->GetComponent<Transform>();
		Collider* floorCol = floor1->AddComponent<Collider>();
		floorCol->SetSize(math::Vector2(2000.0f, 1000.0f));
		floorTr->SetPosition(math::Vector2(680.0f, 1380.0f));

		// 2층
		Floor* floor2 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* floorCol2 = floor2->AddComponent<Collider>();
		Transform* floorTr2 = floor2->GetComponent<Transform>();
		floorCol2->SetSize(math::Vector2(1300.0f, 1.0f));
		floorTr2->SetPosition(math::Vector2(680.0f, 645.0f));

		// 3층
		Floor* floor3 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* floorCol3 = floor3->AddComponent<Collider>();
		Transform* floorTr3 = floor3->GetComponent<Transform>();
		floorCol3->SetSize(math::Vector2(1100.0f, 1.0f));
		floorTr3->SetPosition(math::Vector2(680.0f, 405.0f));

		// 4층
		Floor* floor4 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* floorCol4 = floor4->AddComponent<Collider>();
		Transform* floorTr4 = floor4->GetComponent<Transform>();
		floorCol4->SetSize(math::Vector2(950.0f, 1.0f));
		floorTr4->SetPosition(math::Vector2(680.0f, 165.0f));

		// 5층
		Floor* floor5 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* floorCol5 = floor5->AddComponent<Collider>();
		Transform* floorTr5 = floor5->GetComponent<Transform>();
		floorCol5->SetSize(math::Vector2(760.0f, 1.0f));
		floorTr5->SetPosition(math::Vector2(680.0f, -75.0f));

		// 왼쪽 벽
		Wall* leftWall = object::Instantiate<Wall>(enums::eLayerType::Wall);
		Collider* leftwallCol = leftWall->AddComponent<Collider>();
		leftwallCol->SetSize(math::Vector2(1000.0f, 1500.0f));
		Transform* leftwalltr = leftWall->GetComponent<Transform>();
		leftwalltr->SetPosition(math::Vector2(-745.0f, 360.0f));

		// 오른쪽 벽
		Wall* RightWall = object::Instantiate<Wall>(enums::eLayerType::Wall);
		Collider* RightwallCol = RightWall->AddComponent<Collider>();
		RightwallCol->SetSize(math::Vector2(1000.0f, 1500.0f));
		Transform* Rightwalltr = RightWall->GetComponent<Transform>();
		Rightwalltr->SetPosition(math::Vector2(2025.0f, 360.0f));

		// 로프 1층 -> 2층
		Rope* rope1 = object::Instantiate<Rope>(enums::eLayerType::Rope);
		rope1->Initialize();
		Collider* RopeCol1 = rope1->GetComponent<Collider>();
		RopeCol1->SetSize(math::Vector2(2.0f, 165.0f));
		Transform* RopeTr1 = rope1->GetComponent<Transform>();
		RopeTr1->SetPosition(math::Vector2(393.0f, 720.0f));

		// 로프 2층 -> 3층
		Rope* rope2 = object::Instantiate<Rope>(enums::eLayerType::Rope);
		rope2->Initialize();
		Collider* RopeCol2 = rope2->GetComponent<Collider>();
		RopeCol2->SetSize(math::Vector2(2.0f, 165.0f));
		Transform* RopeTr2 = rope2->GetComponent<Transform>();
		RopeTr2->SetPosition(math::Vector2(759.0f, 480.0f));

		// 로프 3층 -> 4층
		Rope* rope3 = object::Instantiate<Rope>(enums::eLayerType::Rope);
		rope3->Initialize();
		Collider* RopeCol3 = rope3->GetComponent<Collider>();
		RopeCol3->SetSize(math::Vector2(2.0f, 163.0f));
		Transform* RopeTr3 = rope3->GetComponent<Transform>();
		RopeTr3->SetPosition(math::Vector2(545.0f, 243.0f));

		// 포탈
		Portal* portal = object::Instantiate<Portal>(enums::eLayerType::Potal);
		portal->Initialize();

		Transform* portalTr = portal->GetComponent<Transform>();
		//portalTr->SetPosition(math::Vector2(900.0f, 600.0f));
		portalTr->SetPosition(math::Vector2(1370.0f, 830.0f));
	}

	void StageScene::Update()
	{

		Scene::Update();
	}

	void StageScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);
	}
	void StageScene::SceneIN()
	{
		// 백그라운드
		Texture* image = ResourceManager::Load<Texture>(L"Stage1BackGroundImgae"
			, L"..\\Resources\\Maple\\Image\\Map\\Stage1.bmp");

		BackGround* bg = object::Instantiate<BackGround>(enums::eLayerType::Background);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(math::Vector2(1.0f, 1.0f));
		bgsr->SetAffectCamera(true);
		//bgsr->SetAlpha(0.2f);
		bg->GetComponent<Transform>()->SetPosition(math::Vector2(640.0f, 360.0f));

		//카메라가 백그라운드 밖으로 나가지못하게 설정
		bg->SetAutoCameraLimit();
		math::Vector2 widthLimit = math::Vector2(bg->GetLimitLeft(), bg->GetLimitRight());
		math::Vector2 heightLimit = math::Vector2(bg->GetLimitUp(), bg->GetLimitDown());
		Camera::SetLimitDistance(widthLimit, heightLimit);

		// 
		Camera::FadeIn(1.0f, RGB(0, 0, 0));
		// 플레이어 static으로 SceneManager에서 한개만 생성
		Player* player = SceneManager::GetPlayer();

		// 게임오브젝트는 생성자에서 AddComponent<Transform>()을 선언함
		Transform* playerTF = player->GetComponent<Transform>();
		playerTF->SetPosition(math::Vector2(50.0f, 810.0f));
		//playerTF->SetPosition(math::Vector2(640.0f, 500.0f));
		Animator* playerAt = player->GetComponent<Animator>();

		// 카메라의 영향을 true || false
		playerAt->SetAffectedCamera(true);

		// 씬에 들어갈때 카메라 타겟 플레이어한테 세팅
		Camera::SetTarget(player);

		mStage1_Sound = ResourceManager::Load<Sound>(L"Stage1Sound", L"..\\Resources\\Maple\\Sound\\Stage\\Stage1.wav");
		mStage1_Sound->Play(true);

		// 씬에 들어갈때 충돌체크 세팅
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Effect, enums::eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Potal, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Rope, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Monster, enums::eLayerType::Floor, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Floor, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Wall, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Monster, enums::eLayerType::Wall, true);
	}

	void StageScene::SceneOut()
	{

		mStage1_Sound->Stop(true);
		// 씬에서 나올때 카메라 타겟 초기화
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();
	}
}
