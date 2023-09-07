#pragma once
#include "exGameObject.h"

namespace ex
{
	class Collider;
	class Transform;
	class Animator;
	class DamageManager;

	struct EffectInfo
	{
		int AttackCount;
		int DamagePercentage;
	};

	class EffectManger : public GameObject
	{
	public:
		EffectManger(GameObject* _owner);
		virtual ~EffectManger();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* _other) override;
		virtual void OnCollisionStay(Collider* _other) override;
		virtual void OnCollisionExit(Collider* _other) override;

		EffectInfo GetEffectInfo() { return mEffectInfo; }
		void SetEffectInfo(EffectInfo _info) { mEffectInfo = _info; }

		GameObject* GetOwner() { return mOwner; }

		void SetDamageStorage(DamageManager* _damage) { mDamageStorage.push_back(_damage); }
		std::vector<DamageManager*> GetDamageStorage() { return mDamageStorage; }

	private:
		GameObject* mOwner;
		EffectInfo  mEffectInfo;

		std::vector<DamageManager*> mDamageStorage;
	};

}
