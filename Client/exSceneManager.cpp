#include "exSceneManager.h"
#include "exTitleScene.h"
#include "exStageScene.h"
#include "exInput.h"
#include "exBossScene.h"
#include "exBossScene2.h"
#include "exStageScene2.h"
#include "exStageScene3.h"
#include "exMushMomScene.h"
#include "exEndScene.h"
#include "exPlayer.h"
#include "exObject.h"
#include "exPlayerAttack.h"
#include "exStatusBar.h"
#include "exExpBar.h"
#include "exHpBar.h"
#include "exMpBar.h"
#include "exDamageManager.h"
#include "exMushMomHpBar.h"
#include "exSkillSlot.h"
#include "exLevel.h"
#include "exResourceManager.h"
#include "exVonLeonHuman.h"

namespace ex
{
	std::map<std::wstring, Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;
	Player* SceneManager::mPlayer = new Player;
	StatusBar* SceneManager::mStatusBar = new StatusBar;
	ExpBar* SceneManager::mExpBar = new ExpBar;
	HpBar* SceneManager::mHpBar = new HpBar;
	MpBar* SceneManager::mMpBar = new MpBar;
	SkillSlot* SceneManager::mSkillSlot = new SkillSlot;
	Level* SceneManager::mLevel1 = new Level;
	Level* SceneManager::mLevel2 = new Level;
	Level* SceneManager::mLevel3 = new Level;
	bool SceneManager::mbPortalCheck = false;

	void SceneManager::Initialize()
	{
		CreateScene<TitleScene>(L"TitleScene");
		CreateScene<StageScene>(L"StageScene");
		CreateScene<MushMomScene>(L"MushMomScene");
		CreateScene<StageScene2>(L"Stage2Scene");
		CreateScene<StageScene3>(L"Stage3Scene");
		CreateScene<BossScene>(L"BossScene");
		CreateScene<BossScene2>(L"BossScene2");
		CreateScene<EndScene>(L"EndScene");

		mPlayer->Initialize();
		mLevel1->SetPosition(587.0f, 648.5f);
		mLevel2->SetPosition(mLevel1->GetPositionX() + 10.0f, mLevel1->GetPositionY());
		mLevel3->SetPosition(mLevel2->GetPositionX() + 10.0f, mLevel1->GetPositionY());

		ResourceManager::Load<Texture>(L"TitleBackGroundImgae", L"..\\Resources\\Maple\\Image\\Logo\\Title.bmp");
		ResourceManager::Load<Texture>(L"Stage1BackGroundImgae", L"..\\Resources\\Maple\\Image\\Map\\Stage1.bmp");
		ResourceManager::Load<Texture>(L"BossStage1BackGroundImgae", L"..\\Resources\\Maple\\Image\\Map\\BossStage1.bmp");
		ResourceManager::Load<Texture>(L"Stage2BackGroundImgae", L"..\\Resources\\Maple\\Image\\Map\\Stage2.bmp");
		ResourceManager::Load<Texture>(L"Stage3BackGroundImgae", L"..\\Resources\\Maple\\Image\\Map\\Stage3.bmp");
		ResourceManager::Load<Texture>(L"BossBackGroundImgae", L"..\\Resources\\Maple\\Image\\Map\\BossStage2.bmp");
		ResourceManager::Load<Texture>(L"VonLeonBackGroundImgae", L"..\\Resources\\Maple\\Image\\Map\\BossStage3.bmp");
		ResourceManager::Load<Texture>(L"EndBackGroundImgae", L"..\\Resources\\Maple\\Image\\Logo\\EndScene.bmp");

		LoadScene(L"TitleScene");
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::Render(HDC _hdc)
	{
		mActiveScene->Render(_hdc);
	}

	void SceneManager::Release()
	{

		if (mActiveScene->GetName() == L"TitleScene" || mActiveScene->GetName() == L"EndScene")
		{
			delete mPlayer;
			mPlayer = nullptr;

			delete mStatusBar;
			mStatusBar = nullptr;

			delete mExpBar;
			mExpBar = nullptr;

			delete mHpBar;
			mHpBar = nullptr;

			delete mMpBar;
			mMpBar = nullptr;

			delete mSkillSlot;
			mSkillSlot = nullptr;

			delete mLevel1;
			mLevel1 = nullptr;

			delete mLevel2;
			mLevel2 = nullptr;

			delete mLevel3;
			mLevel3 = nullptr;


			
		}

		for (auto iter : mScenes)
		{
			if (nullptr != iter.second)
			{
				delete iter.second;
				iter.second = nullptr;
			}
		}

		mScenes.clear();
	}

	Scene* SceneManager::LoadScene(const std::wstring& _name)
	{
		mActiveScene->SceneOut();

		std::map<std::wstring, Scene*>::iterator iter = mScenes.find(_name);

		mActiveScene->RemoveGameObject(enums::eLayerType::Player, mPlayer);

		// 현재 씬의 레이어안에 있는 GameObject를 변수에 복사
		std::vector<GameObject*> buffObject = mActiveScene->GetLayer(enums::eLayerType::Buff).GetGameObjects();
		// 현재 씬의 레이어 초기화
		mActiveScene->RemoveLayer(enums::eLayerType::Buff);
		std::vector<GameObject*> buffEffectObject = mActiveScene->GetLayer(enums::eLayerType::BuffEffect).GetGameObjects();
		mActiveScene->RemoveLayer(enums::eLayerType::BuffEffect);
		std::vector<GameObject*> buffUIObject = mActiveScene->GetLayer(enums::eLayerType::BuffUI).GetGameObjects();
		mActiveScene->RemoveLayer(enums::eLayerType::BuffUI);

		mActiveScene->RemoveGameObject(enums::eLayerType::UI, mStatusBar);
		mActiveScene->RemoveGameObject(enums::eLayerType::UI, mHpBar);
		mActiveScene->RemoveGameObject(enums::eLayerType::UI, mMpBar);
		mActiveScene->RemoveGameObject(enums::eLayerType::UI, mExpBar);
		mActiveScene->RemoveGameObject(enums::eLayerType::UI, mSkillSlot);
		mActiveScene->RemoveGameObject(enums::eLayerType::UI, mLevel1);
		mActiveScene->RemoveGameObject(enums::eLayerType::UI, mLevel2);
		mActiveScene->RemoveGameObject(enums::eLayerType::UI, mLevel3);

		if (iter == mScenes.end())
		{
			return nullptr;
		}

		mActiveScene = iter->second;

		// 타이틀 씬 End씬이 아니면 플레이어를 씬에 넣어줌
		if (_name != L"TitleScene" && _name != L"EndScene")
		{
			mActiveScene->AddGameObject(enums::eLayerType::Player, mPlayer);
			mActiveScene->AddGameObject(enums::eLayerType::UI, mStatusBar);
			mActiveScene->AddGameObject(enums::eLayerType::UI, mExpBar);
			mActiveScene->AddGameObject(enums::eLayerType::UI, mHpBar);
			mActiveScene->AddGameObject(enums::eLayerType::UI, mMpBar);
			mActiveScene->AddGameObject(enums::eLayerType::UI, mSkillSlot);
			mActiveScene->AddGameObject(enums::eLayerType::UI, mLevel1);
			mActiveScene->AddGameObject(enums::eLayerType::UI, mLevel2);
			mActiveScene->AddGameObject(enums::eLayerType::UI, mLevel3);
		}

		// 현재 Scene에 그 전 Scene 레이어에 들어있던 GameObject의 사이즈만큼 순회하면서
		// 넣어줌
		for (size_t i = 0; i < buffObject.size(); i++)
		{
			mActiveScene->AddGameObject(enums::eLayerType::Buff, buffObject[i]);
		}

		for (size_t i = 0; i < buffEffectObject.size(); i++)
		{
			mActiveScene->AddGameObject(enums::eLayerType::BuffEffect, buffEffectObject[i]);
		}

		for (size_t i = 0; i < buffUIObject.size(); i++)
		{
			mActiveScene->AddGameObject(enums::eLayerType::BuffUI, buffUIObject[i]);
		}

		mActiveScene->SceneIN();

		return iter->second;
	}

}