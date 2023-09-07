#pragma once
#include "exCommonInclude.h"


namespace ex
{
	class Entity
	{
	public:
		Entity();
		virtual ~Entity();

		void SetName(const std::wstring& _name) { mName = _name; }
		std::wstring& GetName() { return mName; }

	private:
		std::wstring mName;

	};
}
