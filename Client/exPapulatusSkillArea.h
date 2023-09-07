#pragma once
#include "exEffectManger.h"

namespace ex
{
	class Animator;
	class Collider;
	class Transform;
	class Papulatus;
	class Sound;

	class PapulatusSkillArea : public EffectManger
	{
	public:
		PapulatusSkillArea(UINT _type);
		virtual ~PapulatusSkillArea();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* _other) override;
		virtual void OnCollisionStay(Collider* _other) override;
		virtual void OnCollisionExit(Collider* _other) override;

		std::set<GameObject*>* GetAttackList() { return &mAttackList; }
	private:
		std::set<GameObject*> mAttackList;

		Animator* mAnimator;
		Collider* mCollider;
		Transform* mTransform;

		EffectInfo mPapulatusSkillArea_Info;
		int	   mPapulatusSkillArea_Damege;
		Sound* mPapulatusSkillArea_Sound;

		float mSkillDelay;
	};

}
