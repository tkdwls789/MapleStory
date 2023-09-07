#pragma once
#include "exUI.h"
#include "exTexture.h"

namespace ex
{
	class Transform;
	

	class DamageManager : public UI
	{
	public:
		DamageManager(int _attackCount = 0);
		virtual ~DamageManager();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* _other) override;
		virtual void OnCollisionStay(Collider* _other) override;
		virtual void OnCollisionExit(Collider* _other) override;

		void PlayPlayerDamageAnimation(int _skillDamage, float _delay = 0);
		void PlayMonsterDamageAnimation(int _monsterDamage, int _skillDamage = 1);


		int GetPlayerDamage() { return mPlayerDamage; }
		int GetMonsterDamage() { return mMonsterDamage; }
		int GetDamageSize() { return mDamageSize; }
		int GetDamageIndex() { return mDamageIndex; }
		int GetPlayerResultDamage() { return mPlayerResultDamage; }
		int GetMonsterResultDamage() { return mMonsterResultDamage; }


	private:
		std::vector<int> mDamageIndexArr;

		int		 mPlayerDamage;
		int		 mMonsterDamage;
		int		 mDamageSize;
		int		 mDamageIndex;
		int		 mPlayerResultDamage;
		int		 mMonsterResultDamage;
		int		 mDamageCount;
	};

}
