#pragma once
#include "exComponent.h"

namespace ex
{
	class Collider : public Component
	{
	public:
		Collider();
		virtual ~Collider();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void SetSize(math::Vector2 _size) { mSize = _size; }
		void SetSize(float _x, float _y) { mSize = math::Vector2(_x, _y); }
		void SetSizeX(float _sizeX) { mSize.x = _sizeX; }
		void SetSizeY(float _sizeY) { mSize.y = _sizeY; }

		math::Vector2 GetSize() { return mSize; }
		float GetSizeX() { return mSize.x; }
		float GetSizeY() { return mSize.y; }

		void SetOffset(math::Vector2 _offset) { mOffset = _offset; }
		void SetOffsetX(float _x) { mOffset.x = _x; }
		void SetOffsetY(float _y) { mOffset.y = _y; }

		math::Vector2 GetOffset() { return mOffset; }
		float GetOffsetX() { return mOffset.x; }
		float GetOffsetY() { return mOffset.y; }

		void OnCollisionEnter(Collider* _other);
		void OnCollisionStay(Collider* _other);
		void OnCollisionExit(Collider* _other);

		math::Vector2 GetPosition() { return mPosition; }
		UINT GetCollisionNumber() { return mCollisionNumber; }

		bool GetCollisionType() { return mbCollisionType; }
		void SetCollisionType(bool _type) { mbCollisionType = _type; }

		bool GetRopeCollision() { return mbRopeCollision; }
		void SetRopeCollision(bool _type) { mbRopeCollision = _type; }

		bool GetCollisonCheck() { return mbIsneedtoCollisonCheck; }
		void SetCollisonCheck(bool _check) { mbIsneedtoCollisonCheck = _check; }

		COLORREF GetCollisionCollor() { return mCollisionCollor; }
		void SetCollisionCollor(COLORREF _color) { mCollisionCollor = _color; }

		COLORREF GetNomalCollor() { return mNomalCollor; }
		void SetNomalCollor(COLORREF _color) { mNomalCollor = _color; }

	private:
		math::Vector2 mSize;
		math::Vector2 mOffset;
		math::Vector2 mPosition;

		static UINT mCollisionCount;
		UINT mCollisionNumber;
		bool mbIsCollision;
		bool mbCollisionType;
		bool mbRopeCollision;

		bool mbIsneedtoCollisonCheck;
		bool mbAffectedCamera;
		COLORREF mNomalCollor;
		COLORREF mCollisionCollor;
	};
}
