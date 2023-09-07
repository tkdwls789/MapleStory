#pragma once
#include "exEffectManger.h"

namespace ex
{
	class Animator;
	class Collider;
	class Transform;
	class Papulatus;
	class Sound;

	class PapulatusSkill1 : public EffectManger
	{
	public:
		PapulatusSkill1(Papulatus* _owner);
		virtual ~PapulatusSkill1();

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

		EffectInfo mPapulatusSkill1_Info;
		int	   mPapulatusSkill1_Damege;
		Sound* mPapulatusSkill1_Sound;
	};

}
