#pragma once
#include "exResource.h"

namespace ex
{
	class ResourceManager
	{

	public:
		template <typename T>
		static T* Find(const std::wstring& name)
		{
			// auto로 자동 타입 추론 (map)으로 관리중인 m_Resource의 name(key)가 있는지 탐색
			auto iter = mResources.find(name);

			// 없으면 end가 반환될 것이므로 nullptr 반환
			if (iter == mResources.end())
				return nullptr;

			// 해당 타입인지 dynamic_cast를 이용하여 검증 후(상속 관계인지) 반환
			return dynamic_cast<T*>(iter->second);
		}

		template <typename T>
		static T* Load(const std::wstring& _name, const std::wstring& _path)
		{
			// 인자로 넘겨준 타입을 T에 치환하여 T 포인터 타입의 변수에 name(key)가 있는지
			// 찾아주는 함수 실행
			T* resource = ResourceManager::Find<T>(_name);

			// 예외처리로 nullptr이 아니면 찾아낸 것이므로
			// 찾아낸 리소스를 반환한다.
			if (resource != nullptr)
				return resource;

			// 전달받은 타입으로 동적할당을 이용해서 새로 생성한다.
			resource = new T();

			// 리소스를 전달받은 경로 인자(path)를 이용하여 Load한다.
			// 반환받은 결과에 따라 Fail인 경우 코드블록 내부의 동작을 수행한다.
			if (FAILED(resource->Load(_path)))
			{
				// 메시지 박스를 이용하여 에러 발생을 나타낸다.
				MessageBox(nullptr, L"Resource Load Failed!", L"Error", MB_OK);
				// 동적할당을 이용해서 리소스를 생성했었으므로 삭제 처리를 한다. 안 그러면
				// 메모리가 해제되지 않아서 memory leak이 남는다.
				delete resource;
				// 실패이므로 nullptr을 반환한다.
				return nullptr;
			}

			// 성공했으면 (Entity class)이름설정
			resource->SetName(_name);
			// 성공했으면 경로설정
			resource->SetPath(_path);

			// 관리하고 있는 구조체에 넣어준다.
			mResources.insert(std::make_pair(_name, resource));

			// 생성한 리소스를 반환한다.
			return resource;
		}

		template <typename T>
		static void Insert(const std::wstring& name, T* resource)
		{
			resource->SetName(name);
			mResources.insert(std::make_pair(name, resource));
		}

		static void Release()
		{
			for (auto iter : mResources)
			{
				delete iter.second;
				iter.second = nullptr;
			}
		}



	private:
		// 리소스 매니저 클래스에서 리소스를 관리하기 위하여 
		// 시간복잡도가 vector를 이용했을때 보다 빠르기때문에
		// 자료구조 map(tree구조)을 이용하여 관리한다
		// (std::wstring(key), Type)을 받는다
		// 전역으로 접근하기위해서 static을 사용한다
		// 그런데 직접접근을 막기위해서 private으로 접근을 제한하고
		// static 멤버 함수를 통해서 접근하는것만 허용한다
		static std::map<std::wstring, Resource*> mResources;

	};

}
