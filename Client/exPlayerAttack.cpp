#include "exPlayerAttack.h"
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
#include "exDamageManager.h"
#include "exMonsters.h"
#include "exSound.h"

namespace ex
{
	PlayerAttack::PlayerAttack(GameObject* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
		, mAttackSound(nullptr)
	{
		mAttackInfo.AttackCount = 1;
		mAttackInfo.DamagePercentage = 9;
		SetEffectInfo(mAttackInfo);
		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mCollider = AddComponent<Collider>();

		math::Vector2 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		mTransform->SetPosition(pos);

		enums::eMoveDir dir = GetOwner()->GetComponent<Transform>()->GetMoveDir();

		mCollider->SetSize(math::Vector2(65.0f, 80.0f));

		if (dir == enums::eMoveDir::Left)
		{
			mCollider->SetOffset(math::Vector2(-68.0f, 10.0f));
		}
		else
		{
			mCollider->SetOffset(math::Vector2(42.0f, 10.0f));
		}

		// 평타 Collider 색 세팅
		mCollider->SetNomalCollor(RGB(255, 255, 0));

		mAttackSound = ResourceManager::Load<Sound>(L"playerAttackSound", L"..\\Resources\\Maple\\Sound\\Player\\player_Attack.wav");
		mAttackSound->Play(false);
	}

	PlayerAttack::~PlayerAttack()
	{
	}

	void PlayerAttack::Initialize()
	{
	}

	void PlayerAttack::Update()
	{
		math::Vector2 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		enums::eMoveDir dir = GetOwner()->GetComponent<Transform>()->GetMoveDir();
		Player* player = SceneManager::GetPlayer();

		eState playerState = SceneManager::GetPlayer()->GetState();
		if (playerState == eState::Attack || playerState == eState::JumpAttack)
		{
			// 충돌 이벤트구현
		}
		else
		{
			// 어택이 끝나면 초기화해줌
			mAttackList.clear();
		}

		bool bCheck = player->GetComponent<Animator>()->IsActiveAnimationComplete();
		if (bCheck)
		{
			Destroy(this);
		}
		mTransform->SetPosition(pos);
		GameObject::Update();

	}

	void PlayerAttack::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}


	void PlayerAttack::OnCollisionEnter(Collider* _other)
	{

		Monsters* monsters = dynamic_cast<Monsters*>(_other->GetOwner());
		if (monsters != nullptr)
		{
			for (size_t i = 1; i <= this->GetEffectInfo().AttackCount; i++)
			{
				if (monsters->GetMonstersState() != eMonsterState::Sleep && 
					monsters->GetMonstersState() != eMonsterState::WakeUp &&
					monsters->GetMonstersState() != eMonsterState::Dead)
				{
					DamageManager* damage = new DamageManager();
					object::ActiveSceneAddGameObject(enums::eLayerType::UI, damage);
					damage->SetPosition(math::Vector2(monsters->GetPositionX(), monsters->GetPositionY() - 28.0f * i));
					damage->PlayPlayerDamageAnimation(this->GetEffectInfo().DamagePercentage);
					monsters->ReductiongHp(damage->GetPlayerResultDamage());
				}
			}
		}
	}

	void PlayerAttack::OnCollisionStay(Collider* _other)
	{
	}

	void PlayerAttack::OnCollisionExit(Collider* _other)
	{
	}
}
