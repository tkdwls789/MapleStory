#include "exPapulatusSkill4.h"
#include "exTexture.h"
#include "exResourceManager.h"
#include "exAnimator.h"
#include "exTransform.h"
#include "exCollider.h"
#include "exTime.h"
#include "exPlayer.h"
#include "exSceneManager.h"
#include "exCollisionManager.h"
#include "exObject.h"
#include "exAnimation.h"
#include "exMonsters.h"
#include "exDamageManager.h"
#include "exPapulatus.h"
#include "exSound.h"
#include "exMasterCronus.h"

namespace ex
{
	PapulatusSkill4::PapulatusSkill4(Papulatus* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
		, mPapulatusSkill4_Damege(0)
		, mPapulatusSkill4_Sound(nullptr)
	{
		mPapulatusSkill4_Info.AttackCount = 3;
		mPapulatusSkill4_Info.DamagePercentage = 0;
		SetEffectInfo(mPapulatusSkill4_Info);

		mPapulatusSkill4_Sound = ResourceManager::Load<Sound>(L"PapulatusSkill4_Sound", L"..\\Resources\\Maple\\Sound\\Monster\\Papulatus\\Papulatus_Skill4.wav");
		mPapulatusSkill4_Sound->Play(false);

		mAnimator = _owner->GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mCollider = AddComponent<Collider>();



		bool randomDir = rand() % 2;
		float randomDelay = rand() % 8 + 4.3f;

		MasterCronus* masterCronus1 = object::Instantiate<MasterCronus>(enums::eLayerType::Monster);
		Transform* masterCronustr1 = masterCronus1->GetComponent<Transform>();
		if (randomDir == 1)
		{
			masterCronustr1->SetMoveDir(enums::eMoveDir::Left);
		
		}
		else
		{
			masterCronustr1->SetMoveDir(enums::eMoveDir::Right);
		}
		masterCronustr1->SetPosition(math::Vector2(_owner->GetPositionX(), _owner->GetPositionY()));
		masterCronus1->SetMoveDelay(randomDelay);
		masterCronus1->Initialize();


		randomDir = rand() % 2;
		randomDelay = rand() % 8 + 4.3f;

		MasterCronus* masterCronus2 = object::Instantiate<MasterCronus>(enums::eLayerType::Monster);
		Transform* masterCronustr2 = masterCronus2->GetComponent<Transform>();
		if (randomDir == 1)
		{
			masterCronustr2->SetMoveDir(enums::eMoveDir::Left);

		}
		else
		{
			masterCronustr2->SetMoveDir(enums::eMoveDir::Right);
		}
		masterCronustr2->SetPosition(math::Vector2(_owner->GetPositionX() + 80.0f, _owner->GetPositionY()));
		masterCronus2->SetMoveDelay(randomDelay);
		masterCronus2->Initialize();

		randomDir = rand() % 2;
		randomDelay = rand() % 8 + 4.3f;

		MasterCronus* masterCronus3 = object::Instantiate<MasterCronus>(enums::eLayerType::Monster);
		Transform* masterCronustr3 = masterCronus3->GetComponent<Transform>();
		if (randomDir == 1)
		{
			masterCronustr3->SetMoveDir(enums::eMoveDir::Left);

		}
		else
		{
			masterCronustr3->SetMoveDir(enums::eMoveDir::Right);
		}
		masterCronustr3->SetPosition(math::Vector2(_owner->GetPositionX() + 160.0f, _owner->GetPositionY()));
		masterCronus3->SetMoveDelay(randomDelay);
		masterCronus3->Initialize();

		MasterCronus* masterCronus4 = object::Instantiate<MasterCronus>(enums::eLayerType::Monster);
		Transform* masterCronustr4 = masterCronus4->GetComponent<Transform>();
		if (randomDir == 1)
		{
			masterCronustr4->SetMoveDir(enums::eMoveDir::Left);

		}
		else
		{
			masterCronustr4->SetMoveDir(enums::eMoveDir::Right);
		}
		masterCronustr4->SetPosition(math::Vector2(_owner->GetPositionX() -80.0f, _owner->GetPositionY()));
		masterCronus4->SetMoveDelay(randomDelay);
		masterCronus4->Initialize();



	}

	PapulatusSkill4::~PapulatusSkill4()
	{
	}

	void PapulatusSkill4::Initialize()
	{
	}

	void PapulatusSkill4::Update()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}

		GameObject::Update();
	}

	void PapulatusSkill4::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void PapulatusSkill4::OnCollisionEnter(Collider* _other)
	{
	}

	void PapulatusSkill4::OnCollisionStay(Collider* _other)
	{
	}

	void PapulatusSkill4::OnCollisionExit(Collider* _other)
	{
	}
}