#pragma once
#include "exEntity.h"
#include "exGameObject.h"

namespace ex
{
	class Layer : public Entity
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		
		void AddGameObject(GameObject* _gameObj)
		{
			mGameObjects.push_back(_gameObj);
		}

		void RemoveGameObject(GameObject* _gameObj);
		void RemoveGameObjects();
		void DeleteObjects();
		std::vector<GameObject*>& GetGameObjects();

	private:
		std::vector<GameObject*> mGameObjects;
	};
}