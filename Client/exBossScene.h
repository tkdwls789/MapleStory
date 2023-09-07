#pragma once
#include "exScene.h"

namespace ex
{
	class Sound;
	class Portal;

	class BossScene : public Scene
	{
	public:
		BossScene();
		virtual ~BossScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void SceneIN() override;
		virtual void SceneOut() override;

	private:
		Sound* mBossSceneSound;
		Portal* mPortal;
	};
}
