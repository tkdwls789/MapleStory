#pragma once
#include "exResource.h"

namespace ex
{
	enum class eTextureType
	{
		Bmp,
		AlphaBmp,
		Png,
		None,
	};

	// 리소스 클래스를 상속 받는다
	class Texture : public Resource
	{
	public:
		Texture();
		virtual ~Texture();

		void Render(HDC hdc
			, math::Vector2 _pos
			, math::Vector2 _size
			, math::Vector2 _leftTop
			, math::Vector2 _rightBottom
			, bool _affectCamera
			, math::Vector2 _scale = math::Vector2::One
			, float _alpha = 1.0f
			, float _rotate = 0.0f);


		// 부모 클래스인 Resource가 순수가상함수를 선언한 추상 클래스이기 때문에
		// 상속을 받을려면 Load함수를 오버라이드 해야한다
		virtual HRESULT Load(const std::wstring& _path) override;

		// 이미지의 가로값 반환(멤버가 private이기 때문에 Get함수사용)
		UINT GetWidth() { return mWidth; }
		void SetWidth(UINT _width) { mWidth = _width; }
		// 이미지의 세로값 반환(멤버가 private이기 때문에 Get함수사용)
		UINT GetHeight() { return mHeight; }
		void SetHeight(UINT _height) { mHeight = _height; }

		COLORREF GetTexturePixel(int _x, int _y);

		math::Vector2 GetSize() { return math::Vector2(static_cast<float>(mWidth), static_cast<float>(mHeight)); }

		// 사용중인 HDC반환(멤버가 private이기 때문에 Get함수사용)
		HDC GetHdc() { return mHdc; }


		// 이미지의 타입(bmp,png) 반환
		eTextureType GetTextType() { return mTexType; }
		void SetTextType(eTextureType _type) { mTexType = _type; }

		Gdiplus::Image* GetImage() { return mImage; }
		
		HBITMAP GetBitmap() { return mBitmap; }
		void SetHBitmap(HBITMAP _bitmap) { mBitmap = _bitmap; }
		void SetHdc(HDC _hdc) { mHdc = _hdc; }

		static Texture* Create(const std::wstring& _name, UINT _width, UINT _height, COLORREF rgb = RGB(255, 255, 255));


	private:
		eTextureType mTexType;
		Gdiplus::Image* mImage;
		Gdiplus::Bitmap* mGdiBitMap;

		HBITMAP mBitmap;
		HDC mHdc;
		UINT mWidth;
		UINT mHeight;
		bool mbAffectCamera;


	};

}
