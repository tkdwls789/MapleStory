#include "exMonsterDamageSkin.h"
#include "exPlayer.h"
#include "exInput.h" 
#include "exTime.h"
#include "exResourceManager.h"
#include "exObject.h"
#include "exCollisionManager.h"
#include "exSceneManager.h"
#include "exSpriteRenderer.h"
#include "exPlayer.h"
#include "exDamageManager.h"
// Component
#include "exTransform.h"
#include "exAnimator.h"

// PlayerSkill
#include "exRaisingblow.h"
#include "exRush.h"
#include "exUpperCharge.h"


namespace ex
{
	MonsterDamageSkin::MonsterDamageSkin(int _index)
		: mDamageIndex(_index)
		, mDamageDelay(0.0f)
		, mDelay(0.0f)
		, mDamageSize(0)
	{
		mMonsterDamageArr[0] = ResourceManager::Load<Texture>(L"MonsterDamage_0"
			, L"..\\Resources\\Maple\\Image\\UI\\DamageSkin\\Monster\\Monster_0.bmp");
		mAnimator->CreateAnimation(L"MonsterDamage_0", mMonsterDamageArr[0], math::Vector2(0.0f, 0.0f), math::Vector2(31.0f, 33.0f)
			, math::Vector2(31.0f, 33.0f), 1, math::Vector2(0.0f, 0.0f), 0.4f);												  
																															  
		mMonsterDamageArr[1] = ResourceManager::Load<Texture>(L"MonsterDamage_1"											  
			, L"..\\Resources\\Maple\\Image\\UI\\DamageSkin\\Monster\\Monster_1.bmp");										  
		mAnimator->CreateAnimation(L"MonsterDamage_1", mMonsterDamageArr[1], math::Vector2(0.0f, 0.0f), math::Vector2(31.0f, 33.0f)
			, math::Vector2(31.0f, 33.0f), 1, math::Vector2(0.0f, 0.0f), 0.4f);												  
																															  
		mMonsterDamageArr[2] = ResourceManager::Load<Texture>(L"MonsterDamage_2"											  
			, L"..\\Resources\\Maple\\Image\\UI\\DamageSkin\\Monster\\Monster_2.bmp");										  
		mAnimator->CreateAnimation(L"MonsterDamage_2", mMonsterDamageArr[2], math::Vector2(0.0f, 0.0f), math::Vector2(31.0f, 33.0f)
			, math::Vector2(31.0f, 33.0f), 1, math::Vector2(0.0f, 0.0f), 0.4f);												  
																															  
		mMonsterDamageArr[3] = ResourceManager::Load<Texture>(L"MonsterDamage_3"											  
			, L"..\\Resources\\Maple\\Image\\UI\\DamageSkin\\Monster\\Monster_3.bmp");										  
		mAnimator->CreateAnimation(L"MonsterDamage_3", mMonsterDamageArr[3], math::Vector2(0.0f, 0.0f), math::Vector2(31.0f, 33.0f)
			, math::Vector2(31.0f, 33.0f), 1, math::Vector2(0.0f, 0.0f), 0.4f);												  
																															  
		mMonsterDamageArr[4] = ResourceManager::Load<Texture>(L"MonsterDamage_4"											  
			, L"..\\Resources\\Maple\\Image\\UI\\DamageSkin\\Monster\\Monster_4.bmp");										  
		mAnimator->CreateAnimation(L"MonsterDamage_4", mMonsterDamageArr[4], math::Vector2(0.0f, 0.0f), math::Vector2(31.0f, 33.0f)
			, math::Vector2(31.0f, 33.0f), 1, math::Vector2(0.0f, 0.0f), 0.4f);												  
																															  
		mMonsterDamageArr[5] = ResourceManager::Load<Texture>(L"MonsterDamage_5"											  
			, L"..\\Resources\\Maple\\Image\\UI\\DamageSkin\\Monster\\Monster_5.bmp");										  
		mAnimator->CreateAnimation(L"MonsterDamage_5", mMonsterDamageArr[5], math::Vector2(0.0f, 0.0f), math::Vector2(31.0f, 33.0f)
			, math::Vector2(31.0f, 33.0f), 1, math::Vector2(0.0f, 0.0f), 0.4f);												  
																															  
		mMonsterDamageArr[6] = ResourceManager::Load<Texture>(L"MonsterDamage_6"											  
			, L"..\\Resources\\Maple\\Image\\UI\\DamageSkin\\Monster\\Monster_6.bmp");										  
		mAnimator->CreateAnimation(L"MonsterDamage_6", mMonsterDamageArr[6], math::Vector2(0.0f, 0.0f), math::Vector2(31.0f, 33.0f)
			, math::Vector2(31.0f, 33.0f), 1, math::Vector2(0.0f, 0.0f), 0.4f);												  
																															  
		mMonsterDamageArr[7] = ResourceManager::Load<Texture>(L"MonsterDamage_7"											  
			, L"..\\Resources\\Maple\\Image\\UI\\DamageSkin\\Monster\\Monster_7.bmp");										  
		mAnimator->CreateAnimation(L"MonsterDamage_7", mMonsterDamageArr[7], math::Vector2(0.0f, 0.0f), math::Vector2(31.0f, 33.0f)
			, math::Vector2(31.0f, 33.0f), 1, math::Vector2(0.0f, 0.0f), 0.4f);												  
																															  
		mMonsterDamageArr[8] = ResourceManager::Load<Texture>(L"MonsterDamage_8"											  
			, L"..\\Resources\\Maple\\Image\\UI\\DamageSkin\\Monster\\Monster_8.bmp");										  
		mAnimator->CreateAnimation(L"MonsterDamage_8", mMonsterDamageArr[8], math::Vector2(0.0f, 0.0f), math::Vector2(31.0f, 33.0f)
			, math::Vector2(31.0f, 33.0f), 1, math::Vector2(0.0f, 0.0f), 0.4f);												  
																															  
		mMonsterDamageArr[9] = ResourceManager::Load<Texture>(L"MonsterDamage_9"											  
			, L"..\\Resources\\Maple\\Image\\UI\\DamageSkin\\Monster\\Monster_9.bmp");										  
		mAnimator->CreateAnimation(L"MonsterDamage_9", mMonsterDamageArr[9], math::Vector2(0.0f, 0.0f), math::Vector2(31.0f, 33.0f)
			, math::Vector2(31.0f, 33.0f), 1, math::Vector2(0.0f, 0.0f), 0.4f);

		switch (mDamageIndex)
		{
		case 0:
			mAnimator->PlayAnimation(L"MonsterDamage_0", false);
			break;
		case 1:
			mAnimator->PlayAnimation(L"MonsterDamage_1", false);
			break;
		case 2:
			mAnimator->PlayAnimation(L"MonsterDamage_2", false);
			break;
		case 3:
			mAnimator->PlayAnimation(L"MonsterDamage_3", false);
			break;
		case 4:
			mAnimator->PlayAnimation(L"MonsterDamage_4", false);
			break;
		case 5:
			mAnimator->PlayAnimation(L"MonsterDamage_5", false);
			break;
		case 6:
			mAnimator->PlayAnimation(L"MonsterDamage_6", false);
			break;
		case 7:
			mAnimator->PlayAnimation(L"MonsterDamage_7", false);
			break;
		case 8:
			mAnimator->PlayAnimation(L"MonsterDamage_8", false);
			break;
		case 9:
			mAnimator->PlayAnimation(L"MonsterDamage_9", false);
			break;
		default:
			break;
		}

	}

	MonsterDamageSkin::~MonsterDamageSkin()
	{
	}

	void MonsterDamageSkin::Initialize()
	{
	}

	void MonsterDamageSkin::Update()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}

		UI::Update();
	}

	void MonsterDamageSkin::Render(HDC _hdc)
	{
		UI::Render(_hdc);
	}

	void MonsterDamageSkin::OnCollisionEnter(Collider* _other)
	{
	}

	void MonsterDamageSkin::OnCollisionStay(Collider* _other)
	{
	}

	void MonsterDamageSkin::OnCollisionExit(Collider* _other)
	{
	}

}
