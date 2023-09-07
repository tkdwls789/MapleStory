#pragma once
#include "exMonsters.h"

namespace ex
{
	class Sound;
	class VonLeon;

	class VonLeonHuman : public Monsters
	{
	public:
		VonLeonHuman();
		virtual ~VonLeonHuman();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* _other) override;
		virtual void OnCollisionStay(Collider* _other) override;
		virtual void OnCollisionExit(Collider* _other) override;

	private:
		
		Sound* mVonLeonDial2_Sound;
		VonLeon* mVonLeon;
		bool mbSoundCheck;
	};

}
