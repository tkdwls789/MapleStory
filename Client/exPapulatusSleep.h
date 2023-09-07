#pragma once
#include "exEffectManger.h"

namespace ex
{
	class Animator;
	class Collider;
	class Transform;
	class Papulatus;
	class Sound;

	class PapulatusSleep : public EffectManger
	{
	public:
		PapulatusSleep(Papulatus* _owner);
		virtual ~PapulatusSleep();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* _other) override;
		virtual void OnCollisionStay(Collider* _other) override;
		virtual void OnCollisionExit(Collider* _other) override;

		std::set<GameObject*>* GetAttackList() { return &mAttackList; }
	private:
		Papulatus* mOwner;
		std::set<GameObject*> mAttackList;

		Animator* mAnimator;
		Collider* mCollider;
		Transform* mTransform;

		int	   mPapulatusSleep_Heal;
		Sound* mPapulatusSleep_Sound;
	};

}
