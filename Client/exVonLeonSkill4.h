#pragma once
#include "exEffectManger.h"

namespace ex
{
	class Animator;
	class Collider;
	class Transform;
	class VonLeon;
	class Sound;

	class VonLeonSkill4 : public EffectManger
	{
	public:
		VonLeonSkill4(VonLeon* _owner);
		virtual ~VonLeonSkill4();

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

		EffectInfo mVonLeonSkill4_Info;
		int	   mVonLeonSkill4_Damege;
		Sound* mVonLeonSkill4_Sound;

		float mSkillDelay;
	};

}
