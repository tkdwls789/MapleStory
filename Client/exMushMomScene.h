#pragma once
#include "exScene.h"


namespace ex
{
	class Portal;
	class MushMom;
	class Sound;

	class MushMomScene : public Scene
	{
	public:
		MushMomScene();
		virtual ~MushMomScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void SceneIN() override;
		virtual void SceneOut() override;

		void SetMushMomHit(bool _data) { mbMushMomHit = _data; }

	private:
		Portal* mPortal;
		MushMom* mMushMom;
		bool	mbMushMomHit;

		Sound* mMushMomSceneSound;
	};
}

