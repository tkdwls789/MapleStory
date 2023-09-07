#pragma once
#include "exUI.h"

namespace ex
{
	class Transform;
	class Collider;
	class Texture;
	class VonLeon;

	class VonLeonHpBar : public UI
	{
	public:
		VonLeonHpBar(VonLeon* _owner);
		virtual ~VonLeonHpBar();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* _other) override;
		virtual void OnCollisionStay(Collider* _other) override;
		virtual void OnCollisionExit(Collider* _other) override;

		bool IsHpBarOn() { return mbHpBarOn; }
		void SetHpBarOn(bool _data) { mbHpBarOn = _data; }

	private:
		Texture* mVonLeonHpBar;
		VonLeon* mVonLeon;
		__int64	 mVonLeonHp;
		__int64	 mVonLeonMaxHp;
		float	 mReductionHp;

		bool     mbHpBarOn;

	};

}
