#pragma once
#include "exEffectManger.h"

namespace ex
{
	class Animator;
	class Collider;
	class Transform;
	class VonLeon;
	class Sound;

	class VonLeonSkill1 : public EffectManger
	{
	public:
		VonLeonSkill1(VonLeon* _owner);
		virtual ~VonLeonSkill1();

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

		EffectInfo mVonLeonSkill1_Info;
		int	   mVonLeonSkill1_Damege;
		Sound* mVonLeonSkill1_Sound;

		float mSkillDelay;
	};

}
