#pragma once
#include "exEntity.h"
#include "exLayer.h"



namespace ex
{
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC _hdc);

		virtual void SceneIN();
		virtual void SceneOut();


		Layer& GetLayer(enums::eLayerType _type);


		// 벡터 레이어타입 배열의 인덱스(레이어 타입)에 게임 오브젝트를 추가한다
		void AddGameObject(enums::eLayerType _type, GameObject* _gameObj)
		{
			mLayers[(int)_type].AddGameObject(_gameObj);
		}

		void RemoveGameObject(enums::eLayerType _type, GameObject* _gameObj)
		{
			mLayers[(int)_type].RemoveGameObject(_gameObj);
		}

		void DeleteLayer(enums::eLayerType type)
		{
			// 해당 레이어 안의 오브젝트를 삭제
			mLayers[(int)type].DeleteObjects();
		}

		void RemoveLayer(enums::eLayerType type)
		{
			// 해당 레이어 안의 오브젝트를 삭제
			mLayers[(int)type].RemoveGameObjects();
		}

		void DeleteAllLayer()
		{
			// 모든 레이어의 오브젝트 삭제
			for (size_t i = 0; i < mLayers.size(); i++)
			{
				DeleteLayer((enums::eLayerType)i);
			}
		}

	private:
		std::vector<Layer> mLayers;
	};

}
