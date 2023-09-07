#include "exCollider.h"
#include "exTransform.h"
#include "exGameObject.h"
#include "exCamera.h"
#include "exInput.h"

namespace ex
{
	UINT Collider::mCollisionCount = 0;

	Collider::Collider()
		: Component(enums::eComponentType::Collider)
		, mSize(math::Vector2::One)
		, mOffset(math::Vector2::Zero)
		, mCollisionNumber(-1)
		, mbIsCollision(false)
		, mbCollisionType(false)
		, mbRopeCollision(false)
		, mbIsneedtoCollisonCheck(false)
		, mNomalCollor(RGB(50, 255, 50))
		, mCollisionCollor(RGB(255, 50, 50))
		, mbAffectedCamera(true)
	{
		mCollisionNumber = mCollisionCount;
		++mCollisionCount;
	}
	Collider::~Collider()
	{
	}
	void Collider::Initialize()
	{
	}
	void Collider::Update()
	{
	}
	void Collider::Render(HDC _hdc)
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		mPosition = pos + mOffset;

		pos.x -= mSize.x / 2.0f;
		pos.y -= mSize.y / 2.0f;
		pos.x += mOffset.x;
		pos.y += mOffset.y;

		if (mbAffectedCamera)
		{
			pos = Camera::CalculatePosition(pos);
		}

		HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, transparentBrush);

		HPEN pen = NULL;

		bool bCheck = Camera::GetColliderCheck();

		if (bCheck)
		{
			if (mbIsCollision)
			{
				pen = CreatePen(PS_SOLID, 2, mCollisionCollor);
			}
			else
			{
				pen = CreatePen(PS_SOLID, 2, mNomalCollor);
			}

			HPEN oldPen = (HPEN)SelectObject(_hdc, pen);

			Rectangle(_hdc
				, (int)pos.x
				, (int)pos.y
				, (int)(pos.x + mSize.x)
				, (int)(pos.y + mSize.y));

			SelectObject(_hdc, oldBrush);
			DeleteObject(transparentBrush);

			SelectObject(_hdc, oldPen);
			DeleteObject(pen);
		}
	}

	void Collider::OnCollisionEnter(Collider* _other)
	{
		mbIsCollision = true;
		GetOwner()->OnCollisionEnter(_other);
	}
	void Collider::OnCollisionStay(Collider* _other)
	{
		GetOwner()->OnCollisionStay(_other);
	}
	void Collider::OnCollisionExit(Collider* _other)
	{
		mbIsCollision = false;
		GetOwner()->OnCollisionExit(_other);
	}
}
