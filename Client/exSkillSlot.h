#pragma once
#include "exUI.h"

namespace ex
{
	class Transform;
	class Texture;
	class SkillSlot : public UI
	{
	public:
		SkillSlot();
		virtual ~SkillSlot();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* _other) override;
		virtual void OnCollisionStay(Collider* _other) override;
		virtual void OnCollisionExit(Collider* _other) override;

	private:
		Texture* mSkillSlot;
	};

}
