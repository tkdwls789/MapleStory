#pragma once
#include "exScene.h"

namespace ex
{
	class Login;
	class Sound;
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		virtual ~TitleScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void SceneIN() override;
		virtual void SceneOut() override;

		void SoundLoad();
	private:
		Sound* mTitleSound;
	};
}
