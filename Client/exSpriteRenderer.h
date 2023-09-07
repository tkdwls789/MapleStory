#pragma once
#include "exComponent.h"
#include "exTexture.h"


namespace ex
{
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();
		virtual ~SpriteRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		// 이미지를 멤버 변수에 세팅할 함수
		void SetImage(Texture* _texture) { mTexture = _texture; }
		Texture* GetImage() { return mTexture; }

		// 이미지 크기에 곱할 값을 세팅할 함수
		void SetScale(math::Vector2 _scale) { mScale = _scale; }
		void SetScaleX(float _scaleX) { mScale = _scaleX; }
		void SetScaleY(float _scaleY) { mScale = _scaleY; }

		// m_bAffectCamere에 카메라의 영향을 받을건지 true or false를 세팅할 함수
		void SetAffectCamera(bool _enable) { mbAffectCamere = _enable; }

		// 투명도를 반환할 함수
		float GetAlpha() { return mAlpha; }

		// 투명도를 세팅할 함수
		void SetAlpha(float _alpha) { mAlpha = _alpha; }

	private:
		// SpriteRenderer에서 이미지를 그리기위해 Texture*으로 멤버를 가지고있는다
		// 사용할 이미지의 주소를 복사받을 변수
		Texture* mTexture;

		// 이미지의 크기를 키우기위해 x,y값에 곱해줄 변수
		math::Vector2 mScale;

		// 카메라의 영향을 받을건지 정하는 bool타입 변수
		bool mbAffectCamere;

		// 화면의 투명도를 설정할 변수 (1.0f 부터 0에 가까울수록 더 투명해짐)
		float mAlpha;
	};
}