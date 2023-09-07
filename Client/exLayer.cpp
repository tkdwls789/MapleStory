#include "exLayer.h"

namespace ex
{
	Layer::Layer()
	{
	}

	Layer::~Layer()
	{
		for (GameObject* obj : mGameObjects)
		{
			delete obj;
			obj = nullptr;
		}
	}

	void Layer::Initialize()
	{
		for (size_t i = 0; i < mGameObjects.size(); i++)
		{
			if (mGameObjects[i]->GetObjectState() == GameObject::eObjectState::Pause)
				continue;

			mGameObjects[i]->Initialize();
		}
	}

	void Layer::Update()
	{
		for (size_t i = 0; i < mGameObjects.size(); ++i)
		{
			if (mGameObjects[i]->GetObjectState() == GameObject::eObjectState::Pause)
			{
				continue;
			}
			mGameObjects[i]->Update();
		}
	}

	void Layer::Render(HDC _hdc)
	{
		for (size_t i = 0; i < mGameObjects.size(); ++i)
		{
			if (mGameObjects[i]->GetObjectState() == GameObject::eObjectState::Pause)
			{
				continue;
			}

			mGameObjects[i]->Render(_hdc);
		}

		// Dead 오브젝트는 Layer에서 제외
		for (std::vector<GameObject*>::iterator iter = mGameObjects.begin()
			; iter != mGameObjects.end()
			; )
		{
			if ((*iter)->GetObjectState() == GameObject::eObjectState::Dead)
			{
				GameObject* obj = *iter;
				iter = mGameObjects.erase(iter);
				delete obj;
				obj = nullptr;
			}
			else
			{
				iter++;
			}
		}
	}


	void Layer::RemoveGameObject(GameObject* _gameObj)
	{
		// mGameObjects 내에서 해당 오브젝트의 iterator 를 찾아온다
		std::vector<GameObject*>::iterator iter = find(mGameObjects.begin(), mGameObjects.end(), _gameObj);
		// mGameObjects벡터 에서 해당 오브젝트가 존재한다면 제외한다
		if (iter != mGameObjects.end())
			mGameObjects.erase(iter);
	}

	void Layer::RemoveGameObjects()
	{
		mGameObjects.clear();
	}

	std::vector<GameObject*>& Layer::GetGameObjects()
	{
		return mGameObjects;
	}

	void Layer::DeleteObjects()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (nullptr != obj)
			{
				delete obj;
				obj = nullptr;
			}
		}
		mGameObjects.clear();
	}
}
