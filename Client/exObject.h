#pragma once
#include "exScene.h"
#include "exGameObject.h"
#include "exSceneManager.h" 

namespace ex::object
{
	template<typename T>
	static __forceinline T* Instantiate(enums::eLayerType _type)
	{
		T* gameObject = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(_type, gameObject);
		gameObject->SetLayerType(_type);

		return gameObject;
	}

	static __forceinline void ActiveSceneAddGameObject(enums::eLayerType _type, GameObject* _obj)
	{
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(_type, _obj);
	}
}