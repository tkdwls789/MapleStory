#pragma once
#include "exScene.h"


namespace ex
{
	class Player;
	class StatusBar;
	class ExpBar;
	class HpBar;
	class MpBar;
	class DamageManager;
	class MushMomHpBar;
	class SkillSlot;
	class Level;

	class SceneManager
	{
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC _hdc);
		static void Release();

		template <typename T>
		static T* CreateScene(const std::wstring& _name)
		{
			T* scene = new T();
			scene->SetName(_name);
			mScenes.insert(std::make_pair(_name, scene));
			mActiveScene = scene;
			scene->Initialize();

			return scene;
		}
		static Scene* LoadScene(const std::wstring& _name);
		static Scene* GetActiveScene() { return mActiveScene; }

		static Player* GetPlayer() { return mPlayer; }
		static StatusBar* GetStatusBar() { return mStatusBar; }

		static Level* GetLevel_1() { return mLevel1; }
		static Level* GetLevel_2() { return mLevel2; }
		static Level* GetLevel_3() { return mLevel3; }

		static bool GetPortalCheck() { return mbPortalCheck; }
		static void SetPortalCheck(bool _data) { mbPortalCheck = _data; }

	private:
		static std::map<std::wstring, Scene*> mScenes;
		static Scene* mActiveScene;
		static Player* mPlayer;
		static StatusBar* mStatusBar;
		static ExpBar* mExpBar;
		static HpBar* mHpBar;
		static MpBar* mMpBar;
		static SkillSlot* mSkillSlot;
		static Level*     mLevel1;
		static Level*     mLevel2;
		static Level*     mLevel3;
		static bool mbPortalCheck;
	};

}
