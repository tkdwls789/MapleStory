#pragma once
#include "exUI.h"
#include "exTexture.h"

namespace ex
{
	class Transform;

	class DamageSkin : public UI
	{
	public:
		DamageSkin(int _index);
		virtual ~DamageSkin();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* _other) override;
		virtual void OnCollisionStay(Collider* _other) override;
		virtual void OnCollisionExit(Collider* _other) override;

		Texture* GetDamageArr() { return *mPlayerDamageArr; }

		int GetDamageSize() { return mDamageSize; }

		float GetDamageDelay() { return mDamageDelay; }
		void SetDamageDelay(float _delay) { mDamageDelay = _delay; }


	private:
		Texture* mPlayerDamageArr[10];
		int		 mDamageIndex;
		int		 mDamageSize;

		float	 mDamageDelay;
		float	 mDelay;
	};

}
