#pragma once
#include "exCommonInclude.h"
#include "exCollider.h"

namespace ex
{
#define LAYER_MAX (UINT)(enums::eLayerType::End)

	// left(UINT : 4Byte) + right(UINT : 4Byte)
	// 위의 두 변수가 UINT64 id를 구성한다.
	// 왜냐면....union은 가장 큰 멤버 변수의 크기를 공간으로 잡기 때문.
	//   |   left   |   right   |
	// ==|          id          |
	// 어렵다면 공용체라는 뜻을 같은 메모리 공간을 나눠서 사용하고 있다 생각하면 된다.
	union ColliderID
	{
		struct
		{
			UINT left;
			UINT right;
		};
		UINT64 id;
	};


	class CollisionManager
	{
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC _hdc);
		static void Release();

		static void Clear();
		static void CollisionLayerCheck(enums::eLayerType _left, enums::eLayerType _right, bool _enable);
		static void LayerCollision(class Scene* _scene, enums::eLayerType _left, enums::eLayerType _right);
		static void ColliderCollision(Collider* _left, Collider* _right);
		static bool Intersect(Collider* _left, Collider* _right);


	private:
		static std::map<UINT64, bool> mCollisionMap;
		static std::bitset<LAYER_MAX> mLayerMasks[LAYER_MAX];
	};
}
