#include "exStageScene3.h"
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

namespace ex
{
	StageScene3::StageScene3()
		: mStage3_Sound(nullptr)
	{
	}

	StageScene3::~StageScene3()
	{
	}

	void StageScene3::Initialize()
	{
		// 게이트키퍼
		GateKeeper* gateKeeper1 = object::Instantiate<GateKeeper>(enums::eLayerType::Monster);
		Transform* gateKeeperTr1 = gateKeeper1->GetComponent<Transform>();
		gateKeeperTr1->SetMoveDir(enums::eMoveDir::Left);
		gateKeeperTr1->SetPosition(math::Vector2(500.0f, 750.0f));
		gateKeeper1->SetMoveDelay(5.1f);
		gateKeeper1->Initialize();

		GateKeeper* gateKeeper2 = object::Instantiate<GateKeeper>(enums::eLayerType::Monster);
		Transform* gateKeeperTr2 = gateKeeper2->GetComponent<Transform>();
		gateKeeperTr2->SetMoveDir(enums::eMoveDir::Right);
		gateKeeperTr2->SetPosition(math::Vector2(770.0f, 750.0f));
		gateKeeper2->SetMoveDelay(6.4f);
		gateKeeper2->Initialize();

		GateKeeper* gateKeeper3 = object::Instantiate<GateKeeper>(enums::eLayerType::Monster);
		Transform* gateKeeperTr3 = gateKeeper3->GetComponent<Transform>();
		gateKeeperTr3->SetMoveDir(enums::eMoveDir::Left);
		gateKeeperTr3->SetPosition(math::Vector2(1100.0f, 750.0f));
		gateKeeper3->SetMoveDelay(3.6f);
		gateKeeper3->Initialize();

		GateKeeper* gateKeeper4 = object::Instantiate<GateKeeper>(enums::eLayerType::Monster);
		Transform* gateKeeperTr4 = gateKeeper4->GetComponent<Transform>();
		gateKeeperTr4->SetMoveDir(enums::eMoveDir::Right);
		gateKeeperTr4->SetPosition(math::Vector2(1400.0f, 750.0f));
		gateKeeper4->SetMoveDelay(4.1f);
		gateKeeper4->Initialize();

		GateKeeper* gateKeeper5 = object::Instantiate<GateKeeper>(enums::eLayerType::Monster);
		Transform* gateKeeperTr5 = gateKeeper5->GetComponent<Transform>();
		gateKeeperTr5->SetMoveDir(enums::eMoveDir::Left);
		gateKeeperTr5->SetPosition(math::Vector2(1700.0f, 750.0f));
		gateKeeper5->SetMoveDelay(3.7f);
		gateKeeper5->Initialize();

		GateKeeper* gateKeeper6 = object::Instantiate<GateKeeper>(enums::eLayerType::Monster);
		Transform* gateKeeperTr6 = gateKeeper6->GetComponent<Transform>();
		gateKeeperTr6->SetMoveDir(enums::eMoveDir::Left);
		gateKeeperTr6->SetPosition(math::Vector2(1300.0f, 750.0f));
		gateKeeper6->SetMoveDelay(4.32f);
		gateKeeper6->Initialize();


		// 타나토스
		Thanatos* thanatos1 = object::Instantiate<Thanatos>(enums::eLayerType::Monster);
		Transform* thanatosTr1 = thanatos1->GetComponent<Transform>();
		thanatosTr1->SetMoveDir(enums::eMoveDir::Left);
		thanatosTr1->SetPosition(math::Vector2(180.0f, 750.0f));
		thanatos1->SetMoveDelay(5.71f);
		thanatos1->Initialize();

		Thanatos* thanatos2 = object::Instantiate<Thanatos>(enums::eLayerType::Monster);
		Transform* thanatosTr2 = thanatos2->GetComponent<Transform>();
		thanatosTr2->SetMoveDir(enums::eMoveDir::Right);
		thanatosTr2->SetPosition(math::Vector2(-30.0f, 750.0f));
		thanatos2->SetMoveDelay(4.22f);
		thanatos2->Initialize();

		Thanatos* thanatos3 = object::Instantiate<Thanatos>(enums::eLayerType::Monster);
		Transform* thanatosTr3 = thanatos3->GetComponent<Transform>();
		thanatosTr3->SetMoveDir(enums::eMoveDir::Left);
		thanatosTr3->SetPosition(math::Vector2(-200.0f, 750.0f));
		thanatos3->SetMoveDelay(4.774f);
		thanatos3->Initialize();

		Thanatos* thanatos4 = object::Instantiate<Thanatos>(enums::eLayerType::Monster);
		Transform* thanatosTr4 = thanatos4->GetComponent<Transform>();
		thanatosTr4->SetMoveDir(enums::eMoveDir::Right);
		thanatosTr4->SetPosition(math::Vector2(-310.0f, 750.0f));
		thanatos4->SetMoveDelay(3.447f);
		thanatos4->Initialize();

		Thanatos* thanatos5 = object::Instantiate<Thanatos>(enums::eLayerType::Monster);
		Transform* thanatosTr5 = thanatos5->GetComponent<Transform>();
		thanatosTr5->SetMoveDir(enums::eMoveDir::Left);
		thanatosTr5->SetPosition(math::Vector2(-480.0f, 750.0f));
		thanatos5->SetMoveDelay(2.7f);
		thanatos5->Initialize();



		// 왼쪽 벽
		Wall* leftWall = object::Instantiate<Wall>(enums::eLayerType::Wall);
		Collider* leftwallCol = leftWall->AddComponent<Collider>();
		leftwallCol->SetSize(math::Vector2(1000.0f, 1500.0f));
		Transform* leftwalltr = leftWall->GetComponent<Transform>();
		leftwalltr->SetPosition(math::Vector2(-1353.0f, 360.0f));

		// 오른쪽 벽
		Wall* RightWall = object::Instantiate<Wall>(enums::eLayerType::Wall);
		Collider* RightwallCol = RightWall->AddComponent<Collider>();
		RightwallCol->SetSize(math::Vector2(1000.0f, 1500.0f));
		Transform* Rightwalltr = RightWall->GetComponent<Transform>();
		Rightwalltr->SetPosition(math::Vector2(2630.0f, 360.0f));

		// 로프
		Rope* rope1 = object::Instantiate<Rope>(enums::eLayerType::Rope);
		rope1->Initialize();
		Collider* RopeCol1 = rope1->GetComponent<Collider>();
		RopeCol1->SetSize(math::Vector2(2.0f, 780.0f));
		RopeCol1->SetOffset(math::Vector2(0.0f, -23.0f));
		Transform* RopeTr1 = rope1->GetComponent<Transform>();
		RopeTr1->SetPosition(math::Vector2(1673.0f, 482.0f));



		// 바닥 1층
		Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* col1 = floor1->AddComponent<Collider>();
		Transform* tr1 = floor1->GetComponent<Transform>();
		col1->SetSize(math::Vector2(3300.0f, 1000.0f));
		tr1->SetPosition(math::Vector2(680.0f, 1410.0f));

		// 바닥 2층
		Floor* floor2 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* col2 = floor2->AddComponent<Collider>();
		Transform* tr2 = floor2->GetComponent<Transform>();
		col2->SetSize(math::Vector2(2150.0f, 130.0f));
		tr2->SetPosition(math::Vector2(635.0f, 138.0f));



		// 포탈
		Portal* portal = object::Instantiate<Portal>(enums::eLayerType::Potal);
		portal->Initialize();
		Transform* portalTr = portal->GetComponent<Transform>();
		Animator* portalAt = portal->GetComponent<Animator>();
		Collider* portalCol = portal->GetComponent<Collider>();
		portalAt->SetScale(math::Vector2(0.8f, 0.8f));
		portalTr->SetPosition(math::Vector2(1950.0f, 862.0f));
		portalCol->SetSize(math::Vector2(45.0f, 80.0f));
		
		//Test
		//portalTr->SetPosition(math::Vector2(640.0f, 862.0f));

	}

	void StageScene3::Update()
	{
		Scene::Update();
	}

	void StageScene3::Render(HDC _hdc)
	{
		Scene::Render(_hdc);
	}
	void StageScene3::SceneIN()
	{
		Texture* image = ResourceManager::Load<Texture>(L"Stage3BackGroundImgae"
			, L"..\\Resources\\Maple\\Image\\Map\\Stage3.bmp");

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
		playerTF->SetPosition(math::Vector2(-600.0f, 810.0f));
		//playerTF->SetPosition(math::Vector2(400.0f, 800.0f));
		// 플레이어가 중력을 받기위해 
		player->GetComponent<Rigidbody>()->SetGround(false);

		Animator* playerAt = player->GetComponent<Animator>();
		// 카메라의 영향을 true || false
		playerAt->SetAffectedCamera(true);

		// 씬에 들어갈때 카메라 타겟 플레이어한테 세팅
		Camera::SetTarget(player);

		mStage3_Sound = ResourceManager::Load<Sound>(L"Stage3Sound", L"..\\Resources\\Maple\\Sound\\Stage\\Stage3.wav");
		mStage3_Sound->Play(true);

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
	void StageScene3::SceneOut()
	{
		mStage3_Sound->Stop(true);
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();
	}
}
