#pragma once
#include "exEffectManger.h"

namespace ex
{
	class Animator;
	class Collider;
	class Transform;
	class VonLeon;
	class Sound;

	class VonLeonSkill5 : public EffectManger
	{
	public:
		VonLeonSkill5(VonLeon* _owner);
		virtual ~VonLeonSkill5();

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

		EffectInfo mVonLeonSkill5_Info;
		int	   mVonLeonSkill5_Damege;
		Sound* mVonLeonSkill5_Sound;

		float mSkillDelay;
	};

}
