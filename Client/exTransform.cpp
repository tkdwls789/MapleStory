#include "exTransform.h"
#include "exTime.h"
#include "exInput.h"

ex::Transform::Transform()
	: Component(enums::eComponentType::Transform)
	, mRotation(0.0f)
	, mMoveDir(enums::eMoveDir::End)
{
}

ex::Transform::~Transform()
{
}

void ex::Transform::Initialize()
{
}

void ex::Transform::Update()
{
}

void ex::Transform::Render(HDC hdc)
{
}
