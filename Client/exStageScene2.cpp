#include "exStageScene2.h"
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
#include "exRobo.h"
#include "exMasterRobo.h"
#include "exRope.h"
#include "exWall.h"
#include "exSound.h"

namespace ex
{
	StageScene2::StageScene2()
		: mStage2_Sound(nullptr)
	{
	}

	StageScene2::~StageScene2()
	{
	}

	void StageScene2::Initialize()
	{

		// 몬스터 로보
		// 1층
		Robo* robo1 = object::Instantiate<Robo>(enums::eLayerType::Monster);
		Transform* roboTr1 = robo1->GetComponent<Transform>();
		roboTr1->SetMoveDir(enums::eMoveDir::Left);
		roboTr1->SetPosition(math::Vector2(480.0f, 500.0f));
		robo1->SetMoveDelay(3.6f);
		robo1->Initialize();

		Robo* robo2 = object::Instantiate<Robo>(enums::eLayerType::Monster);
		Transform* roboTr2 = robo2->GetComponent<Transform>();
		roboTr2->SetMoveDir(enums::eMoveDir::Right);
		roboTr2->SetPosition(math::Vector2(100.0f, 500.0f));
		robo2->SetMoveDelay(2.5f);
		robo2->Initialize();

		Robo* robo3 = object::Instantiate<Robo>(enums::eLayerType::Monster);
		Transform* roboTr3 = robo3->GetComponent<Transform>();
		roboTr3->SetMoveDir(enums::eMoveDir::Left);
		roboTr3->SetPosition(math::Vector2(200.0f, 500.0f));
		robo3->SetMoveDelay(6.5f);
		robo3->Initialize();

		Robo* robo4 = object::Instantiate<Robo>(enums::eLayerType::Monster);
		Transform* roboTr4 = robo4->GetComponent<Transform>();
		roboTr4->SetMoveDir(enums::eMoveDir::Right);
		roboTr4->SetPosition(math::Vector2(800.0f, 500.0f));
		robo4->SetMoveDelay(4.0f);
		robo4->Initialize();

		Robo* robo5 = object::Instantiate<Robo>(enums::eLayerType::Monster);
		Transform* roboTr5 = robo5->GetComponent<Transform>();
		roboTr5->SetMoveDir(enums::eMoveDir::Left);
		roboTr5->SetPosition(math::Vector2(1100.0f, 500.0f));
		robo5->SetMoveDelay(3.7f);
		robo5->Initialize();

		Robo* robo6 = object::Instantiate<Robo>(enums::eLayerType::Monster);
		Transform* roboTr6 = robo6->GetComponent<Transform>();
		roboTr6->SetMoveDir(enums::eMoveDir::Left);
		roboTr6->SetPosition(math::Vector2(0.0f, 500.0f));
		robo6->SetMoveDelay(5.5f);
		robo6->Initialize();

		Robo* robo7 = object::Instantiate<Robo>(enums::eLayerType::Monster);
		Transform* roboTr7 = robo7->GetComponent<Transform>();
		roboTr7->SetMoveDir(enums::eMoveDir::Right);
		roboTr7->SetPosition(math::Vector2(900.0f, 500.0f));
		robo7->SetMoveDelay(4.5f);
		robo7->Initialize();

		Robo* robo8 = object::Instantiate<Robo>(enums::eLayerType::Monster);
		Transform* roboTr8 = robo8->GetComponent<Transform>();
		roboTr8->SetMoveDir(enums::eMoveDir::Right);
		roboTr8->SetPosition(math::Vector2(1200.0f, 500.0f));
		robo8->SetMoveDelay(3.0f);
		robo8->Initialize();

		Robo* robo9 = object::Instantiate<Robo>(enums::eLayerType::Monster);
		Transform* roboTr9 = robo9->GetComponent<Transform>();
		roboTr9->SetMoveDir(enums::eMoveDir::Right);
		roboTr9->SetPosition(math::Vector2(1000.0f, 500.0f));
		robo9->SetMoveDelay(4.3f);
		robo9->Initialize();

		Robo* robo10 = object::Instantiate<Robo>(enums::eLayerType::Monster);
		Transform* roboTr10 = robo10->GetComponent<Transform>();
		roboTr10->SetMoveDir(enums::eMoveDir::Left);
		roboTr10->SetPosition(math::Vector2(1400.0f, 500.0f));
		robo10->SetMoveDelay(2.3f);
		robo10->Initialize();

		Robo* robo11 = object::Instantiate<Robo>(enums::eLayerType::Monster);
		Transform* roboTr11 = robo11->GetComponent<Transform>();
		roboTr11->SetMoveDir(enums::eMoveDir::Left);
		roboTr11->SetPosition(math::Vector2(500.0f, 340.0f));
		robo11->SetMoveDelay(2.5f);
		robo11->Initialize();

		Robo* robo12 = object::Instantiate<Robo>(enums::eLayerType::Monster);
		Transform* roboTr12 = robo12->GetComponent<Transform>();
		roboTr12->SetMoveDir(enums::eMoveDir::Right);
		roboTr12->SetPosition(math::Vector2(500.0f, 160.0f));
		robo12->SetMoveDelay(2.32f);
		robo12->Initialize();

		Robo* robo13 = object::Instantiate<Robo>(enums::eLayerType::Monster);
		Transform* roboTr13 = robo13->GetComponent<Transform>();
		roboTr13->SetMoveDir(enums::eMoveDir::Left);
		roboTr13->SetPosition(math::Vector2(1300.0f, 200.0f));
		robo13->SetMoveDelay(3.05f);
		robo13->Initialize();

		Robo* robo14 = object::Instantiate<Robo>(enums::eLayerType::Monster);
		Transform* roboTr14 = robo14->GetComponent<Transform>();
		roboTr14->SetMoveDir(enums::eMoveDir::Right);
		roboTr14->SetPosition(math::Vector2(1400.0f, 200.0f));
		robo14->SetMoveDelay(2.7f);
		robo14->Initialize();

		// 몬스터 마스터로보
		MasterRobo* masterRobo1 = object::Instantiate<MasterRobo>(enums::eLayerType::Monster);
		Transform* masterRoboTr1 = masterRobo1->GetComponent<Transform>();
		masterRoboTr1->SetMoveDir(enums::eMoveDir::Right);
		masterRoboTr1->SetPosition(math::Vector2(489.0f, 500.0f));
		masterRobo1->SetMoveDelay(3.07f);
		masterRobo1->Initialize();

		MasterRobo* masterRobo2 = object::Instantiate<MasterRobo>(enums::eLayerType::Monster);
		Transform* masterRoboTr2 = masterRobo2->GetComponent<Transform>();
		masterRoboTr2->SetMoveDir(enums::eMoveDir::Right);
		masterRoboTr2->SetPosition(math::Vector2(489.0f, 340.0f));
		masterRobo2->SetMoveDelay(3.23f);
		masterRobo2->Initialize();

		MasterRobo* masterRobo3 = object::Instantiate<MasterRobo>(enums::eLayerType::Monster);
		Transform* masterRoboTr3 = masterRobo3->GetComponent<Transform>();
		masterRoboTr3->SetMoveDir(enums::eMoveDir::Right);
		masterRoboTr3->SetPosition(math::Vector2(395.0f, 340.0f));
		masterRobo3->SetMoveDelay(3.11f);
		masterRobo3->Initialize();

		MasterRobo* masterRobo4 = object::Instantiate<MasterRobo>(enums::eLayerType::Monster);
		Transform* masterRoboTr4 = masterRobo4->GetComponent<Transform>();
		masterRoboTr4->SetMoveDir(enums::eMoveDir::Right);
		masterRoboTr4->SetPosition(math::Vector2(777.0f, 500.0f));
		masterRobo4->SetMoveDelay(3.66f);
		masterRobo4->Initialize();

		MasterRobo* masterRobo5 = object::Instantiate<MasterRobo>(enums::eLayerType::Monster);
		Transform* masterRoboTr5 = masterRobo5->GetComponent<Transform>();
		masterRoboTr5->SetMoveDir(enums::eMoveDir::Right);
		masterRoboTr5->SetPosition(math::Vector2(1200.0f, 500.0f));
		masterRobo5->SetMoveDelay(3.59f);
		masterRobo5->Initialize();

		MasterRobo* masterRobo6 = object::Instantiate<MasterRobo>(enums::eLayerType::Monster);
		Transform* masterRoboTr6 = masterRobo6->GetComponent<Transform>();
		masterRoboTr6->SetMoveDir(enums::eMoveDir::Left);
		masterRoboTr6->SetPosition(math::Vector2(1250.0f, 200.0f));
		masterRobo6->SetMoveDelay(3.17f);
		masterRobo6->Initialize();

		MasterRobo* masterRobo7 = object::Instantiate<MasterRobo>(enums::eLayerType::Monster);
		Transform* masterRoboTr7 = masterRobo7->GetComponent<Transform>();
		masterRoboTr7->SetMoveDir(enums::eMoveDir::Left);
		masterRoboTr7->SetPosition(math::Vector2(530.0f, 160.0f));
		masterRobo7->SetMoveDelay(3.32f);
		masterRobo7->Initialize();

		// 바닥 1층
		Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* col1 = floor1->GetComponent<Collider>();
		Transform* tr1 = floor1->GetComponent<Transform>();
		col1 = floor1->AddComponent<Collider>();
		col1->SetSize(math::Vector2(3000.0f, 1000.0f));
		tr1 = floor1->GetComponent<Transform>();
		tr1->SetPosition(math::Vector2(680.0f, 1038.0f));

		// 왼쪽 바닥 2층
		Floor* floor2 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* col2 = floor2->GetComponent<Collider>();
		Transform* tr2 = floor2->GetComponent<Transform>();
		col2 = floor2->AddComponent<Collider>();
		col2->SetSize(math::Vector2(145.0f, 1.0f));
		col2->SetOffset(math::Vector2(10.0f, 0.0f));
		tr2 = floor2->GetComponent<Transform>();
		tr2->SetPosition(math::Vector2(-200.0f, 280.0f));

		// 가운데 바닥 2층
		Floor* floor3 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* col3 = floor3->GetComponent<Collider>();
		Transform* tr3 = floor3->GetComponent<Transform>();
		col3 = floor3->AddComponent<Collider>();
		col3->SetSize(math::Vector2(490.0f, 1.0f));
		//col3->SetOffset(math::Vector2(10.0f, 0.0f));
		tr3 = floor3->GetComponent<Transform>();
		tr3->SetPosition(math::Vector2(500.0f, 352.0f));

		// 오른쪽 바닥 2층
		Floor* floor4 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* col4 = floor4->GetComponent<Collider>();
		Transform* tr4 = floor4->GetComponent<Transform>();
		col4 = floor4->AddComponent<Collider>();
		col4->SetSize(math::Vector2(530.0f, 1.0f));
		tr4 = floor4->GetComponent<Transform>();
		tr4->SetPosition(math::Vector2(1350.0f, 275.0f));

		// 오른쪽 바닥 3층
		Floor* floor5 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* col5 = floor5->GetComponent<Collider>();
		Transform* tr5 = floor5->GetComponent<Transform>();
		col5 = floor5->AddComponent<Collider>();
		col5->SetSize(math::Vector2(188.0f, 1.0f));
		tr5 = floor5->GetComponent<Transform>();
		tr5->SetPosition(math::Vector2(920.0f, 207.0f));

		// 가운데 바닥 3층
		Floor* floor6 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* col6 = floor6->GetComponent<Collider>();
		Transform* tr6 = floor6->GetComponent<Transform>();
		col6 = floor6->AddComponent<Collider>();
		col6->SetSize(math::Vector2(355.0f, 1.0f));
		tr6 = floor6->GetComponent<Transform>();
		tr6->SetPosition(math::Vector2(500.0f, 168.0f));

		// 왼쪽 로프
		Rope* rope1 = object::Instantiate<Rope>(enums::eLayerType::Rope);
		rope1->Initialize();
		Collider* RopeCol1 = rope1->GetComponent<Collider>();
		RopeCol1->SetSize(math::Vector2(2.0f, 460.0f));
		RopeCol1->SetOffset(math::Vector2(0.0f, -23.0f));
		Transform* RopeTr1 = rope1->GetComponent<Transform>();
		RopeTr1->SetPosition(math::Vector2(-73.0f, 250.0f));

		// 오른쪽 로프
		Rope* rope2 = object::Instantiate<Rope>(enums::eLayerType::Rope);
		rope2->Initialize();
		Collider* RopeCol2 = rope2->GetComponent<Collider>();
		RopeCol2->SetSize(math::Vector2(2.0f, 180.0f));
		Transform* RopeTr2 = rope2->GetComponent<Transform>();
		RopeTr2->SetPosition(math::Vector2(1092.0f, 363.0f));


		// 왼쪽 벽
		Wall* leftWall = object::Instantiate<Wall>(enums::eLayerType::Wall);
		Collider* leftwallCol = leftWall->AddComponent<Collider>();
		leftwallCol->SetSize(math::Vector2(1000.0f, 1500.0f));
		Transform* leftwalltr = leftWall->GetComponent<Transform>();
		leftwalltr->SetPosition(math::Vector2(-840.0f, 360.0f));

		// 오른쪽 벽
		Wall* RightWall = object::Instantiate<Wall>(enums::eLayerType::Wall);
		Collider* RightwallCol = RightWall->AddComponent<Collider>();
		RightwallCol->SetSize(math::Vector2(1000.0f, 1500.0f));
		Transform* Rightwalltr = RightWall->GetComponent<Transform>();
		Rightwalltr->SetPosition(math::Vector2(2125.0f, 360.0f));


		// 포탈
		Portal* portal = object::Instantiate<Portal>(enums::eLayerType::Potal);
		portal->Initialize();

		Transform* portalTr = portal->GetComponent<Transform>();
		portalTr->SetPosition(math::Vector2(1450.0f, 500.0f));
		//portalTr->SetPosition(math::Vector2(-200.0f, 250.0f));

	}

	void StageScene2::Update()
	{
		math::Vector2 pos = SceneManager::GetPlayer()->GetComponent<Transform>()->GetPosition();

		Scene::Update();
	}

	void StageScene2::Render(HDC _hdc)
	{
		Scene::Render(_hdc);
	}
	void StageScene2::SceneIN()
	{
		Texture* image = ResourceManager::Load<Texture>(L"Stage2BackGroundImgae"
			, L"..\\Resources\\Maple\\Image\\Map\\Stage2.bmp");

		BackGround* bg = object::Instantiate<BackGround>(enums::eLayerType::Background);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(math::Vector2(1.0f, 1.1f));
		bgsr->SetAffectCamera(true);
		//bgsr->SetAlpha(0.2f);
		bg->GetComponent<Transform>()->SetPosition(math::Vector2(640.0f, 360.f));

		bg->SetAutoCameraLimit();
		math::Vector2 widthLimit = math::Vector2(bg->GetLimitLeft(), bg->GetLimitRight());
		math::Vector2 heightLimit = math::Vector2(bg->GetLimitUp(), bg->GetLimitDown());
		Camera::SetLimitDistance(widthLimit, heightLimit);
		Camera::FadeIn(1.f, RGB(0, 0, 0));

		Player* player = SceneManager::GetPlayer();

		// 게임오브젝트는 생성자에서 AddComponent<Transform>()을 선언함
		Transform* playerTF = player->GetComponent<Transform>();
		//playerTF->SetPosition(math::Vector2(50.0f, 810.0f));
		playerTF->SetPosition(math::Vector2(-200.0f, 250.0f));
		// 플레이어가 중력을 받기위해 
		player->GetComponent<Rigidbody>()->SetGround(false);

		Animator* playerAt = player->GetComponent<Animator>();
		// 카메라의 영향을 true || false
		playerAt->SetAffectedCamera(true);

		// 씬에 들어갈때 카메라 타겟 플레이어한테 세팅
		Camera::SetTarget(player);

		
		mStage2_Sound = ResourceManager::Load<Sound>(L"Stage2Sound", L"..\\Resources\\Maple\\Sound\\Stage\\Stage2.wav");
		mStage2_Sound->Play(true);

		// 씬에 들어갈때 충돌체크 세팅
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Floor, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Rope, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Effect, enums::eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Potal, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Monster, enums::eLayerType::Floor, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Wall, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Monster, enums::eLayerType::Wall, true);
	}
	void StageScene2::SceneOut()
	{
		mStage2_Sound->Stop(true);
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();
	}
}
