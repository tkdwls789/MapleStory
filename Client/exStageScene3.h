#pragma once
#include "exScene.h"

namespace ex
{
	class Sound;

	class StageScene3 : public Scene
	{
	public:
		StageScene3();
		virtual ~StageScene3();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void SceneIN() override;
		virtual void SceneOut() override;

	private:
		Sound* mStage3_Sound;
	};
}
