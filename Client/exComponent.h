#pragma once
#include "exEntity.h"

namespace ex
{
	class GameObject;
	class Component : public Entity
	{
	public:	
		// Component를 상속받을 클래스는 부모 생성자가 인자를 받기떄문에
		// enum class에 정의된 타입으로 type에 초기화 해줘야한다.
		Component(enums::eComponentType _type);
		virtual ~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC _hdc);


		// Component를 상속받은 클래스들이 서로를 참조하려 할때
		// Component가 속한 게임 오브젝트에 대한 접근을 할 수 있게 함으로써
		// GameObjcet와 Component 간의 상호작용과 게임 플로우를 원활하게 조정할 수 있게 됩니다.
		void SetOwner(GameObject* _owner) { mOwner = _owner; }
		GameObject* GetOwner() { return mOwner; }

	private:
		const enums::eComponentType mType;
		GameObject* mOwner;
	};
}

