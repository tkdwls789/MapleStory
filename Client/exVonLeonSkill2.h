#pragma once
#include "exEffectManger.h"

namespace ex
{
	class Animator;
	class Collider;
	class Transform;
	class VonLeon;
	class Sound;

	class VonLeonSkill2 : public EffectManger
	{
	public:
		VonLeonSkill2(VonLeon* _owner);
		virtual ~VonLeonSkill2();

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

		EffectInfo mVonLeonSkill2_Info;
		int	   mVonLeonSkill2_Damege;
		Sound* mVonLeonSkill2_Sound;

		float mSkillDelay;
	};

}
