#include "exComponent.h"


namespace ex
{
	Component::Component(enums::eComponentType _type)
		: mType(_type)
		, mOwner(nullptr)
	{
	}

	Component::~Component()
	{
	}

	void Component::Initialize()
	{
	}

	void Component::Update()
	{
	}

	void Component::Render(HDC _hdc)
	{
	}
}