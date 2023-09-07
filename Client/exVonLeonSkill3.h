#pragma once
#include "exEffectManger.h"

namespace ex
{
	class Animator;
	class Collider;
	class Transform;
	class VonLeon;
	class Sound;

	class VonLeonSkill3 : public EffectManger
	{
	public:
		VonLeonSkill3(VonLeon* _owner);
		virtual ~VonLeonSkill3();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* _other) override;
		virtual void OnCollisionStay(Collider* _other) override;
		virtual void OnCollisionExit(Collider* _other) override;

		std::set<GameObject*>* GetAttackList() { return &mAttackList; }
	private:
		GameObject* mOwner;
		std::set<GameObject*> mAttackList;

		Animator* mAnimator;
		Collider* mCollider;
		Transform* mTransform;

		EffectInfo mVonLeonSkill3_Info;
		int	   mVonLeonSkill3_Damege;
		Sound* mVonLeonSkill3_Sound;

		float mSkillDelay;
	};

}
