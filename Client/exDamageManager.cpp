#include "exDamageManager.h"
#include "exPlayer.h"
#include "exInput.h" 
#include "exTime.h"
#include "exResourceManager.h"
#include "exObject.h"
#include "exCollisionManager.h"
#include "exSceneManager.h"
#include "exSpriteRenderer.h"
#include "exPlayer.h"
#include "exDamageSkin.h"
#include "exMonsterDamageSkin.h"


// Component
#include "exTransform.h"
#include "exAnimator.h"

// PlayerSkill
#include "exRaisingblow.h"
#include "exRush.h"
#include "exUpperCharge.h"

namespace ex
{
	DamageManager::DamageManager(int _attackCount)
		: mDamageSize(0)
		, mPlayerDamage(0)
		, mDamageIndex(0)
		, mDamageIndexArr{}
		, mPlayerResultDamage(0)
		, mMonsterResultDamage(0)
		, mMonsterDamage(0)
		, mDamageCount(_attackCount)
	{
		Player* player = SceneManager::GetPlayer();
		int minDamage = (int)player->GetInfo()->mMinDamage;
		int maxDamage = (int)player->GetInfo()->mMaxDamage;
		mPlayerDamage = minDamage + std::rand() % (maxDamage - minDamage + 1);
	}

	DamageManager::~DamageManager()
	{
	}

	void DamageManager::Initialize()
	{
	}

	void DamageManager::Update()
	{
		UI::Update();
	}

	void DamageManager::Render(HDC _hdc)
	{
		UI::Render(_hdc);
	}

	void DamageManager::PlayPlayerDamageAnimation(int _skillDamage, float _delay)
	{
		// resultDamage = 플레이어의 MaxDamage ~ MinDamage 사이의 랜덤 값 * 스킬 데미지
		mPlayerResultDamage = mPlayerDamage * _skillDamage;


		int temp = mPlayerResultDamage;
		// 데미지의 Size를 구하기
		std::string numStr = std::to_string(temp);
		mDamageSize = static_cast<int>(numStr.length());

		// 데미지를 뒤에부터 하나씩 받기위해 만든 배열
		for (size_t i = 0; i < mDamageSize; ++i)
		{
			int remainder = temp % 10;
			mDamageIndexArr.push_back(remainder);
			temp /= 10;
		}

		// 배열 다시 뒤집어서 정렬
		reverse(mDamageIndexArr.begin(), mDamageIndexArr.end());

		for (size_t j = 0; j < mDamageSize; j++)
		{
			DamageSkin* damageSkin = new DamageSkin(mDamageIndexArr[j]);
			object::ActiveSceneAddGameObject(enums::eLayerType::UI, damageSkin);
			damageSkin->GetComponent<Transform>()->SetPosition(this->GetPosition());
			damageSkin->GetComponent<Transform>()->SetPositionX(this->GetPositionX() + (38.0f * j) - (mDamageSize * 38.0f / 2.0f));
			damageSkin->SetDamageDelay(_delay);
		}
	}

	void DamageManager::PlayMonsterDamageAnimation(int _monsterDamage, int _skillDamage)
	{
		// resultDamage = 몬스터의 Damage값 * 스킬 데미지
		mMonsterResultDamage = _monsterDamage * _skillDamage;

		int temp = mMonsterResultDamage;
		// 데미지의 Size를 구하기
		std::string numStr = std::to_string(temp);
		mDamageSize = static_cast<int>(numStr.length());

		// 데미지를 뒤에부터 하나씩 받기위해 만든 배열
		for (size_t i = 0; i < mDamageSize; ++i)
		{
			int remainder = temp % 10;
			mDamageIndexArr.push_back(remainder);
			temp /= 10;
		}

		// 배열 다시 뒤집어서 정렬
		reverse(mDamageIndexArr.begin(), mDamageIndexArr.end());

		for (size_t i = 0; i < mDamageSize; i++)
		{
			MonsterDamageSkin* monsterDamageSkin = new MonsterDamageSkin(mDamageIndexArr[i]);
			object::ActiveSceneAddGameObject(enums::eLayerType::UI, monsterDamageSkin);
			monsterDamageSkin->GetComponent<Transform>()->SetPosition(this->GetPosition());
			monsterDamageSkin->GetComponent<Transform>()->SetPositionX(this->GetPositionX() + (27.0f * i) - (mDamageSize * 31.0f / 2.0f));
		}
		Player* player = SceneManager::GetPlayer();
		player->GetInfo()->mHp -= mMonsterResultDamage;
		player->SetState(eState::Hit);
		player->SetInvincible(true);
	}

	void DamageManager::OnCollisionEnter(Collider* _other)
	{
	}

	void DamageManager::OnCollisionStay(Collider* _other)
	{
	}

	void DamageManager::OnCollisionExit(Collider* _other)
	{
	}

}
