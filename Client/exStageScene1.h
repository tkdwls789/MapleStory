#pragma once
#include "exScene.h"


namespace ex
{
	class StageScene : public Scene
	{
	public:
		StageScene();
		virtual ~StageScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void SceneIN() override;
		virtual void SceneOut() override;
	private:
	};
}
