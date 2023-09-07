#pragma once
#include "exUI.h"

namespace ex
{
	class Transform;
	class Collider;
	class Texture;
	class MushMom;

	class MushMomHpBar : public UI
	{
	public:
		MushMomHpBar(MushMom* _owner);
		virtual ~MushMomHpBar();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* _other) override;
		virtual void OnCollisionStay(Collider* _other) override;
		virtual void OnCollisionExit(Collider* _other) override;


		bool IsMushMomHpBarOn() { return mbMushMomHpBarOn; }
		void SetMushMomHpBarOn(bool _data) {  mbMushMomHpBarOn = _data; }

	private:
		Texture* mMushMomHpBar;
		MushMom* mMushMom;
		__int64	 mMushMomHp;
		__int64	 mMushMomMaxHp;
		float	 mReductionHp;

		bool    mbMushMomHpBarOn;

	};

}
