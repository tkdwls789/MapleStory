#include "exTitleScene.h"
#include "exPlayer.h"
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
#include "exFloor.h"
#include "exLogin.h"

namespace ex
{
	TitleScene::TitleScene()
		: mTitleSound(nullptr)
	{
	}

	TitleScene::~TitleScene()
	{
	}

	void TitleScene::Initialize()
	{	
		SoundLoad();

	}

	void TitleScene::Update()
	{
		Scene::Update();
		
		bool bLogin = Login::IsLoginCheck();
		if (bLogin)
		{
			SceneManager::LoadScene(L"StageScene");
		}
	}

	void TitleScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);		
	}
	void TitleScene::SceneIN()
	{
		Texture* image = ResourceManager::Load<Texture>(L"TitleBackGroundImgae"
			, L"..\\Resources\\Maple\\Image\\Logo\\Title.bmp");

		BackGround* bg = object::Instantiate<BackGround>(enums::eLayerType::Background);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(math::Vector2(1.7f, 1.8f));
		bgsr->SetAffectCamera(true);
		//bgsr->SetAlpha(0.2f);
		bg->GetComponent<Transform>()->SetPosition(math::Vector2(640.0f, 360.0f));

		mTitleSound = ResourceManager::Load<Sound>(L"TitleSound", L"..\\Resources\\Maple\\Sound\\Stage\\Title.wav");
		mTitleSound->Play(true);

		Login* login = object::Instantiate<Login>(enums::eLayerType::Floor);
		login->Initialize();
		
		Camera::SetTarget(nullptr);
	}
	void TitleScene::SceneOut()
	{
		mTitleSound->Stop(true);
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();
	}
	void TitleScene::SoundLoad()
	{
		ResourceManager::Load<Sound>(L"TitleSound", L"..\\Resources\\Maple\\Sound\\Stage\\Title.wav");
		ResourceManager::Load<Sound>(L"Stage1Sound", L"..\\Resources\\Maple\\Sound\\Stage\\Stage1.wav");
		ResourceManager::Load<Sound>(L"MushMomSceneSound", L"..\\Resources\\Maple\\Sound\\Stage\\MushMomRoom.wav");
		ResourceManager::Load<Sound>(L"Stage2Sound", L"..\\Resources\\Maple\\Sound\\Stage\\Stage2.wav");
		ResourceManager::Load<Sound>(L"Stage3Sound", L"..\\Resources\\Maple\\Sound\\Stage\\Stage3.wav");
		ResourceManager::Load<Sound>(L"BossSceneSound", L"..\\Resources\\Maple\\Sound\\Stage\\PapulatusRoom.wav");
		ResourceManager::Load<Sound>(L"VonLeonRoomSound", L"..\\Resources\\Maple\\Sound\\Stage\\VonLeonRoom.wav");
		ResourceManager::Load<Sound>(L"VonLeonDial", L"..\\Resources\\Maple\\Sound\\Monster\\VonLeon\\VonLeon_Dial1.wav");
		ResourceManager::Load<Sound>(L"VonLeonDial2_Sound", L"..\\Resources\\Maple\\Sound\\Monster\\VonLeon\\VonLeon_Dial2.wav");

		ResourceManager::Load<Sound>(L"PlayerJump", L"..\\Resources\\Maple\\Sound\\Player\\Player_Jump.wav");
		ResourceManager::Load<Sound>(L"PlayerPortion", L"..\\Resources\\Maple\\Sound\\Player\\Player_Portion.wav");
		ResourceManager::Load<Sound>(L"PlayerDieSound", L"..\\Resources\\Maple\\Sound\\Player\\Player_Die.wav");

		ResourceManager::Load<Sound>(L"GreenMushDeadSound", L"..\\Resources\\Maple\\Sound\\Monster\\Mush\\Mush_Die.wav");
		ResourceManager::Load<Sound>(L"OrangeMushDeadSound", L"..\\Resources\\Maple\\Sound\\Monster\\Mush\\Mush_Die.wav");
		ResourceManager::Load<Sound>(L"RoboDeadSound", L"..\\Resources\\Maple\\Sound\\Monster\\Robo\\Robo_Die.wav");
		ResourceManager::Load<Sound>(L"RoboHitSound", L"..\\Resources\\Maple\\Sound\\Monster\\Robo\\Robo_Hit.wav");
		ResourceManager::Load<Sound>(L"MasterRoboDeadSound", L"..\\Resources\\Maple\\Sound\\Monster\\Robo\\Robo_Die.wav");

		ResourceManager::Load<Sound>(L"GateKeeperHitSound", L"..\\Resources\\Maple\\Sound\\Monster\\GateKeeper\\GateKeeper_Die.wav");
		ResourceManager::Load<Sound>(L"GateKeeperDeadSound", L"..\\Resources\\Maple\\Sound\\Monster\\GateKeeper\\GateKeeper_Hit.wav");
		ResourceManager::Load<Sound>(L"ThanatosHitSound", L"..\\Resources\\Maple\\Sound\\Monster\\Thanatos\\Thanatos_Hit.wav");
		ResourceManager::Load<Sound>(L"ThanatosDeadSound", L"..\\Resources\\Maple\\Sound\\Monster\\Thanatos\\Thanatos_Die.wav");
		ResourceManager::Load<Sound>(L"MasterCronusHitSound", L"..\\Resources\\Maple\\Sound\\Monster\\MasterCronus\\MasterCronus_Die.wav");
		ResourceManager::Load<Sound>(L"MasterCronusDeadSound", L"..\\Resources\\Maple\\Sound\\Monster\\MasterCronus\\MasterCronus_Hit.wav");

		ResourceManager::Load<Sound>(L"MushMomHitSound", L"..\\Resources\\Maple\\Sound\\Monster\\MushMom\\MushMom_Hit.wav");
		ResourceManager::Load<Sound>(L"MushMomDeadSound", L"..\\Resources\\Maple\\Sound\\Monster\\MushMom\\MushMom_Die.wav");
		ResourceManager::Load<Sound>(L"PapulatusHitSound", L"..\\Resources\\Maple\\Sound\\Monster\\Papulatus\\Papulatus_Die.wav");
		ResourceManager::Load<Sound>(L"PapulatusDeadSound", L"..\\Resources\\Maple\\Sound\\Monster\\Papulatus\\Papulatus_Hit.wav");
		ResourceManager::Load<Sound>(L"VonLeonHitSound", L"..\\Resources\\Maple\\Sound\\Monster\\VonLeon\\VonLeon_Hit.wav");
		ResourceManager::Load<Sound>(L"VonLeonDeadSound", L"..\\Resources\\Maple\\Sound\\Monster\\VonLeon\\VonLeon_Die.wav");

		ResourceManager::Load<Sound>(L"playerAttackSound", L"..\\Resources\\Maple\\Sound\\Player\\player_Attack.wav");
		ResourceManager::Load<Sound>(L"WarriorLeapSound", L"..\\Resources\\Maple\\Sound\\Skill\\WarriorLeap.wav");
		ResourceManager::Load<Sound>(L"RagingblowScound", L"..\\Resources\\Maple\\Sound\\Skill\\Ragingblow.wav");
		ResourceManager::Load<Sound>(L"RaisingBlowHit", L"..\\Resources\\Maple\\Sound\\Skill\\Ragingblow_Hit.wav");
		ResourceManager::Load<Sound>(L"UpperChargeSound", L"..\\Resources\\Maple\\Sound\\Skill\\UpperCharge.wav");
		ResourceManager::Load<Sound>(L"RushSound", L"..\\Resources\\Maple\\Sound\\Skill\\Rush.wav");
		ResourceManager::Load<Sound>(L"ComboDeathFaultSound", L"..\\Resources\\Maple\\Sound\\Skill\\ComboDeathFault.wav");
		ResourceManager::Load<Sound>(L"ComboDeathFaultHitSound", L"..\\Resources\\Maple\\Sound\\Skill\\ComboDeathFault_Hit.wav");

		ResourceManager::Load<Sound>(L"GateKeeperAttackSound", L"..\\Resources\\Maple\\Sound\\Monster\\GateKeeper\\GateKeeper_Attack.wav");
		ResourceManager::Load<Sound>(L"ThanatosAttackSound", L"..\\Resources\\Maple\\Sound\\Monster\\Thanatos\\Thanatos_Attack.wav");
		ResourceManager::Load<Sound>(L"MasterCronusAttackSound", L"..\\Resources\\Maple\\Sound\\Monster\\MasterCronus\\MasterCronus_Attack.wav");

		ResourceManager::Load<Sound>(L"MushMomSkillSound", L"..\\Resources\\Maple\\Sound\\Monster\\MushMom\\MushMom_Attack.wav");
		ResourceManager::Load<Sound>(L"PapulatusSkill1_Sound", L"..\\Resources\\Maple\\Sound\\Monster\\Papulatus\\Papulatus_Skill1.wav");
		ResourceManager::Load<Sound>(L"PapulatusSkill2_Sound", L"..\\Resources\\Maple\\Sound\\Monster\\Papulatus\\Papulatus_Skill2.wav");
		ResourceManager::Load<Sound>(L"PapulatusSkill3_Sound", L"..\\Resources\\Maple\\Sound\\Monster\\Papulatus\\Papulatus_alarmStart.wav");
		ResourceManager::Load<Sound>(L"PapulatusSkill4_Sound", L"..\\Resources\\Maple\\Sound\\Monster\\Papulatus\\Papulatus_Skill4.wav");
		ResourceManager::Load<Sound>(L"PapulatusSkill5_Sound", L"..\\Resources\\Maple\\Sound\\Monster\\Papulatus\\Papulatus_Skill5.wav");
		ResourceManager::Load<Sound>(L"PapulatusSleep_Sound", L"..\\Resources\\Maple\\Sound\\Monster\\Papulatus\\Papulatus_Sleep.wav");
		ResourceManager::Load<Sound>(L"VonLeonSkill1_Sound", L"..\\Resources\\Maple\\Sound\\Monster\\VonLeon\\VonLeon_Skill1.wav");
		ResourceManager::Load<Sound>(L"VonLeonSkill2_Sound", L"..\\Resources\\Maple\\Sound\\Monster\\VonLeon\\VonLeon_Skill2.wav");
		ResourceManager::Load<Sound>(L"VonLeonSkill3_Sound", L"..\\Resources\\Maple\\Sound\\Monster\\VonLeon\\VonLeon_Skill3.wav");
		ResourceManager::Load<Sound>(L"VonLeonSkill4_Sound", L"..\\Resources\\Maple\\Sound\\Monster\\VonLeon\\VonLeon_Skill4.wav");
		ResourceManager::Load<Sound>(L"VonLeonSkill5_Sound", L"..\\Resources\\Maple\\Sound\\Monster\\VonLeon\\VonLeon_Skill5.wav");
		ResourceManager::Load<Sound>(L"VonLeonTeleport_Sound", L"..\\Resources\\Maple\\Sound\\Monster\\VonLeon\\VonLeon_Teleport.wav");

		ResourceManager::Load<Sound>(L"BuffSound", L"..\\Resources\\Maple\\Sound\\Player\\player_Buff.wav");

		ResourceManager::Load<Sound>(L"PlayerLevelUpSound",L"..\\Resources\\Maple\\Sound\\Player\\Player_LevelUp.wav");

	}
}
