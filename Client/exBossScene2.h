#pragma once
#include "exScene.h"

namespace ex
{
	class Sound;
	class Portal;
	class VonLeonHuman;
	class BossScene2 : public Scene
	{
	public:
		BossScene2();
		virtual ~BossScene2();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void SceneIN() override;
		virtual void SceneOut() override;

	private:
		Portal* mPortal;

		Sound* mBossScene2_Sound;
		Sound* mVonLeonDial_Sound;

		VonLeonHuman* mVonLeonHuman;
	};
}
