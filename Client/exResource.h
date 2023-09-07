#pragma once
#include "exEntity.h"


// 이미지와 사운드 등을 리소스로 관리한다
namespace ex
{
	class Resource : public Entity
	{

	public:
		Resource();
		virtual ~Resource();

		// 리소스 클래스의 자식이 항상 Load를 구현하게 하기위해 순수 가상함수로 만들어줌
		virtual HRESULT Load(const std::wstring& _path) = 0;

		// 저장한 이미지의 경로를 반환해준다 (멤버 변수가 private이기 때문에 Get함수 이용)
		std::wstring& GetPath() { return mPath; }

		//  이미지의 경로를 멤버 변수에 복사해준다(멤버 변수가 private이기 때문에 Set함수 이용)
		void SetPath(const std::wstring& _path) { mPath = _path; }


	private:
		std::wstring mPath;
	};

}



