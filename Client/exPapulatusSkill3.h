#pragma once
#include "exEffectManger.h"

namespace ex
{
	class Animator;
	class Collider;
	class Transform;
	class Papulatus;
	class Sound;

	class PapulatusSkill3 : public EffectManger
	{
	public:
		PapulatusSkill3(Papulatus* _owner);
		virtual ~PapulatusSkill3();

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

		EffectInfo mPapulatusSkill3_Info;
		int	   mPapulatusSkill3_Damege;
		Sound* mPapulatusSkill3_Sound;
		float mSkillDelay;
	};

}
