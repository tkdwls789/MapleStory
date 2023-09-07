#pragma once
#include "exEntity.h"
#include "exComponent.h"
#include "exTransform.h"
#include "exRigidbody.h"

namespace ex
{
	class Collider;

	//// 오브젝트의 상태
	//enum class eObjectState
	//{
	//	// 활성화 상태, Update(OK), Render(OK)
	//	Active,
	//	// 멈춰있는 상태, Update(X), Render(X)
	//	Pause,
	//	// 이번 Render가 마무리되고 이 객체가 삭제되어야 하는 경우. Render가 끝나고 이 객체를 삭제하도록. ex) Bullet.
	//	Dead,
	//	End,
	//};
	


	class GameObject : public Entity
	{
	public:
		enum class eState
		{
			Idle,
			Move,
			Jump,
			DoubleJump,
			Down,
			Fall,
			Rope,
			RopeDown,
			Attack,
			Hit,
			Invincible,
			Death,
			JumpAttack,
			RaisingBlow,
			UpperCharge,
			Rush,
			ComboDeathFault,
			Buff,
			Stun,
			End,
		};

		enum class eMonsterState
		{
			Idle,
			Move,
			Attack,
			Chase,
			Hit,
			Dead,
			Skill1,
			Skill2,
			Skill3,
			Skill4,
			Skill5,
			Teleport,
			Sleep,
			WakeUp,

		};

		enum class eObjectState
		{
			Active,
			Pause,
			Dead,
			End,
		};

		friend static __forceinline void Destroy(GameObject* gameObject);

		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC _hdc);

		template <typename T>
		T* AddComponent();
		template <typename T>
		T* GetComponent();

		Transform* GetTransform();

		void SetPosition(math::Vector2 pos) { GetTransform()->SetPosition(pos); }
		void SetPosition(float x, float y) { GetTransform()->SetPosition(x, y); }
		// 각각 입력을 받을 수 있게
		void SetPositionX(float x) { GetTransform()->SetPositionX(x); }
		void SetPositionY(float y) { GetTransform()->SetPositionY(y); }

		// 세팅한 위치정보를 가지고있는 m_Pos 변수를 가져오는 함수
		math::Vector2 GetPosition() { return GetTransform()->GetPosition(); }
		// 각각 입력을 받을 수 있게
		float GetPositionX() { return GetTransform()->GetPositionX(); }
		float GetPositionY() { return GetTransform()->GetPositionY(); }

		// 회전할 각도를 가질 m_Rotation 변수를 세팅하는 함수
		void SetRotation(float rotation) { GetTransform()->SetRotation(rotation); }

		// 세팅한 각도를 들고있는 m_Rotation을 가져오는 함수
		float GetRotation() { return GetTransform()->GetRotation(); }

		virtual void OnCollisionEnter(Collider* _other);
		virtual void OnCollisionStay(Collider* _other);
		virtual void OnCollisionExit(Collider* _other);

		void SetLayerType(enums::eLayerType _type) { mLayerType = _type; }
		enums::eLayerType GetLayerType() { return mLayerType; }

		eObjectState GetObjectState() { return mObjectState; }

	private:
		void death() { mObjectState = eObjectState::Dead; }
		void Pause() { mObjectState = eObjectState::Pause; }

	private:
		std::vector<Component*> mComponents;
		enums::eLayerType		mLayerType;
		eObjectState			mObjectState;

	};

	static __forceinline void Destroy(GameObject* gameObject)
	{
		gameObject->death();
	}




	// Component를 추가 해주는 함수
	template<typename T>
	__forceinline T* GameObject::AddComponent()
	{
		for (Component* com : mComponents)
		{
			Component* temp = dynamic_cast<T*>(com);
			if (temp != nullptr)
			{
				assert(nullptr);
			}
		}

		// 들어온 Component 타입의 새로운 객체를 생성하고 
		T* comp = new T();

		// vector<Component*> m_Components에 넣어준다
		mComponents.push_back(comp);

		// 해당 속성을 가지는 GameObject 객체를 알기위해
		// Component는 자신을 소유한 GameObject(this)를 가리키고있다.
		comp->SetOwner(this);

		return comp;
	}

	// 추가된 Component가 있다면 가져오는 함수
	template<typename T>
	__forceinline T* GameObject::GetComponent()
	{
		// 템플릿으로 들어온 타입의 T* comp를 선언하고
		T* comp = nullptr;

		// m_Components안에 Component를 상속받은 자식타입이 있다면
		for (Component* c : mComponents)
		{
			// 자식타입과 T타입이 일치한다면
			// 주소를 반환 그렇지않다면 nullptr 반환
			comp = dynamic_cast<T*>(c);

			// 들어온 타입이 형변환에 성공했다면
			if (comp != nullptr)
				return comp;
		}

		// 없다면 nullptr을 리턴
		return comp;
	}

}

