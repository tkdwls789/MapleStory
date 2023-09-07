#pragma once
#include "exEffectManger.h"

namespace ex
{
	class Animator;
	class Collider;
	class Transform;
	class Sound;

	class LevelUp : public EffectManger
	{
	public:
		LevelUp(GameObject* _owner);
		virtual ~LevelUp();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* _other) override;
		virtual void OnCollisionStay(Collider* _other) override;
		virtual void OnCollisionExit(Collider* _other) override;


	private:
		GameObject* mOwner;

		Animator* mAnimator;
		Collider* mCollider;
		Transform* mTransform;
		Sound* mLevelUpSound;
	};

}
