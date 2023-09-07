#pragma once
#include "exGameObject.h"

namespace ex
{

	class Rope : public GameObject
	{
	public:
		Rope();
		virtual ~Rope();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(class Collider* _other) override;
		virtual void OnCollisionStay(class Collider* _other) override;
		virtual void OnCollisionExit(class Collider* _other) override;

	private:


	};

}
