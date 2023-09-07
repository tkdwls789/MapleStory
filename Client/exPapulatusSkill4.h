#pragma once
#include "exEffectManger.h"

namespace ex
{
	class Animator;
	class Collider;
	class Transform;
	class Papulatus;
	class Sound;

	class PapulatusSkill4 : public EffectManger
	{
	public:
		PapulatusSkill4(Papulatus* _owner);
		virtual ~PapulatusSkill4();

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

		EffectInfo mPapulatusSkill4_Info;
		int	   mPapulatusSkill4_Damege;
		Sound* mPapulatusSkill4_Sound;
	};

}
