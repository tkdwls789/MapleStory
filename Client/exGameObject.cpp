#include "exGameObject.h"
#include "exSpriteRenderer.h"
#include "exCollider.h"
#include "exRigidbody.h"

namespace ex
{
	GameObject::GameObject()
		: mObjectState(eObjectState::Active)
	{
		// GameObject는 기본적으로 위치정보를 사용하기 때문에
		// Transform을 생성자에서 AddComponent해준다
		AddComponent<Transform>();
	}

	GameObject::~GameObject()
	{
		for (Component* comp : mComponents)
		{
			delete comp;
			comp = nullptr;
		}
	}

	void GameObject::Initialize()
	{
		for (Component* comp : mComponents)
		{
			comp->Initialize();
		}
	}

	void GameObject::Update()
	{
		for (Component* comp : mComponents)
		{
			comp->Update();
		}
	}

	void GameObject::Render(HDC _hdc)
	{
		for (Component* comp : mComponents)
		{
			comp->Render(_hdc);
		}
	}

	Transform* GameObject::GetTransform()
	{
		Transform* tr = nullptr;
		tr = GetComponent<Transform>();
		return tr;
	}

	void GameObject::OnCollisionEnter(Collider* _other)
	{
	}

	void GameObject::OnCollisionStay(Collider* _other)
	{
	}

	void GameObject::OnCollisionExit(Collider* _other)
	{
	}


}