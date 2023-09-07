#pragma once
#include "exScene.h"

namespace ex
{
	class Login;
	class Sound;
	class EndScene : public Scene
	{
	public:
		EndScene();
		virtual ~EndScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void SceneIN() override;
		virtual void SceneOut() override;

	private:
		Sound* mEndSound;
	};
}
