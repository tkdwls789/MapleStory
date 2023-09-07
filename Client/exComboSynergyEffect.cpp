#include "exComboSynergyEffect.h"
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
#include "exSound.h"

namespace ex
{
	ComboSynergyEffect::ComboSynergyEffect(UINT _type)
		: EffectManger(SceneManager::GetPlayer())
		, mOwner(SceneManager::GetPlayer())
		, mTextureArr{}
		, mTypeNum(_type)
		, mDegree(0.0f)
	{
		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();

		math::Vector2 playerPos = SceneManager::GetPlayer()->GetPosition();
		//// png
		if (mTypeNum == 0)
		{
			mTextureArr[0] = ResourceManager::Load<Texture>(L"ComboSynergyEffect_0"
				, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\ComboSynergy\\Effect\\ComboSynergy_000.png");
			mAnimator->CreateAnimation(L"ComboSynergyEffect_0", mTextureArr[0], math::Vector2(0.0f, 0.0f), math::Vector2(111.0f, 112.0f)
				, math::Vector2(111.0f, 112.0f), 1, math::Vector2(0), 0.1f);
			mAnimator->PlayAnimation(L"ComboSynergyEffect_0", false);
		}
		else if (mTypeNum == 1)
		{
			mTextureArr[1] = ResourceManager::Load<Texture>(L"ComboSynergyEffect_1"
				, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\ComboSynergy\\Effect\\ComboSynergy_001.png");
			mAnimator->CreateAnimation(L"ComboSynergyEffect_1", mTextureArr[1], math::Vector2(0.0f, 0.0f), math::Vector2(111.0f, 112.0f)
				, math::Vector2(111.0f, 112.0f), 1, math::Vector2(0), 0.1f);
			mAnimator->PlayAnimation(L"ComboSynergyEffect_1", false);
		}
		else if (mTypeNum == 2)
		{
			mTextureArr[2] = ResourceManager::Load<Texture>(L"ComboSynergyEffect_2"
				, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\ComboSynergy\\Effect\\ComboSynergy_002.png");
			mAnimator->CreateAnimation(L"ComboSynergyEffect_2", mTextureArr[2], math::Vector2(0.0f, 0.0f), math::Vector2(111.0f, 112.0f)
				, math::Vector2(111.0f, 112.0f), 1, math::Vector2(0), 0.1f);
			mAnimator->PlayAnimation(L"ComboSynergyEffect_2", false);
		}

		else if (mTypeNum == 3)
		{
			mTextureArr[3] = ResourceManager::Load<Texture>(L"ComboSynergyEffect_3"
				, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\ComboSynergy\\Effect\\ComboSynergy_003.png");
			mAnimator->CreateAnimation(L"ComboSynergyEffect_3", mTextureArr[3], math::Vector2(0.0f, 0.0f), math::Vector2(111.0f, 112.0f)
				, math::Vector2(111.0f, 112.0f), 1, math::Vector2(0), 0.1f);
			mAnimator->PlayAnimation(L"ComboSynergyEffect_3", false);
		}
		else
		{
			mTextureArr[4] = ResourceManager::Load<Texture>(L"ComboSynergyEffect_4"
				, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\ComboSynergy\\Effect\\ComboSynergy_004.png");
			mAnimator->CreateAnimation(L"ComboSynergyEffect_4", mTextureArr[4], math::Vector2(0.0f, 0.0f), math::Vector2(111.0f, 112.0f)
				, math::Vector2(111.0f, 112.0f), 1, math::Vector2(0), 0.1f);
			mAnimator->PlayAnimation(L"ComboSynergyEffect_4", false);
		}
	}

	ComboSynergyEffect::~ComboSynergyEffect()
	{
	}

	void ComboSynergyEffect::Initialize()
	{
	}

	void ComboSynergyEffect::Update()
	{
		Player* player = SceneManager::GetPlayer();
		math::Vector2 playerPos = player->GetPosition();
		float offSetPlayerPosX = player->GetPositionX() - 13.0f;
		float offSetPlayerPosY = player->GetPositionY() + 5.0f;

		float degree = 72.0f;
		float radius = 50.0f;
		mDegree -= 72.0f * Time::GetDeltaTime() + 1.0f;

		bool bCheck = player->IsBuffCheck();
		if (bCheck == false)
		{
			Destroy(this);
		}
		else
		{
			// 콤보 시너지 각자 초기위치 값  세팅
			if (mTypeNum == 0)
			{
				mTransform->SetPositionX(cosf(degree / 180 * PI * mTypeNum) * radius);
				mTransform->SetPositionY(sinf(degree / 180 * PI * mTypeNum) * radius);
			}
			else if (mTypeNum == 1)
			{
				mTransform->SetPositionX(cosf(degree / 180 * PI * mTypeNum) * radius);
				mTransform->SetPositionY(sinf(degree / 180 * PI * mTypeNum) * radius);
			}
			else if (mTypeNum == 2)
			{
				mTransform->SetPositionX(cosf(degree / 180 * PI * mTypeNum) * radius);
				mTransform->SetPositionY(sinf(degree / 180 * PI * mTypeNum) * radius);
			}
			else if (mTypeNum == 3)
			{
				mTransform->SetPositionX(cosf(degree / 180 * PI * mTypeNum) * radius);
				mTransform->SetPositionY(sinf(degree / 180 * PI * mTypeNum) * radius);
			}
			else if (mTypeNum == 4)
			{
				mTransform->SetPositionX(cosf(degree / 180 * PI * mTypeNum) * radius);
				mTransform->SetPositionY(sinf(degree / 180 * PI * mTypeNum) * radius);
			}

			// Rotate()에서 회전 방향을 구하고 (resultPos)에 복사
			// 인자로 ComboSynergyEffect 객체의 좌표, 각도 72(mDegree)(360 / 5(객체의 총 개수) = 72) 
			math::Vector2 resultPos = math::Rotate(math::Vector2(mTransform->GetPositionX(), mTransform->GetPositionY()), mDegree);
			
			// 기준점 셋팅(offSetPlayerPos) 0.0에서 플레이어의 위치까지 평행이동하는 거리
			// 회전 방향(resultPos)
			// 플레이어로 부터 떨어져있는 값(radius)
			mTransform->SetPositionX(offSetPlayerPosX + resultPos.x * radius);
			mTransform->SetPositionY(offSetPlayerPosY + resultPos.y * radius);
		}
		GameObject::Update();
	}

	void ComboSynergyEffect::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void ComboSynergyEffect::OnCollisionEnter(Collider* _other)
	{
	}

	void ComboSynergyEffect::OnCollisionStay(Collider* _other)
	{
	}

	void ComboSynergyEffect::OnCollisionExit(Collider* _other)
	{
	}
}