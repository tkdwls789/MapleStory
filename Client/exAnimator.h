#pragma once
#include "exComponent.h"
#include "exAnimation.h"

namespace ex
{
	class Animator : public Component
	{
	public:
		Animator();
		virtual ~Animator();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		// 아틀라스 이미지를 가져와 애니메이션을 생성할때 사용하는 함수
		Animation* CreateAnimation(const std::wstring& _name
			, class Texture* _texture
			, math::Vector2 _leftTop
			, math::Vector2 _size
			, math::Vector2 _interval
			, UINT _spriteLength
			, math::Vector2 _offset = math::Vector2::Zero
			, float _duration = 0.2f);

		// 폴더 단위로 이미지를 읽어와 애니메이션을 생성할때 사용하는 함수
		void CreateAnimationFolder(const std::wstring& _name
			, const std::wstring& _path
			, math::Vector2 _offset = math::Vector2::Zero
			, float _duration = 0.1f);


		// map구조에 저장되있는 m_Animations을 키값을 인자로 넣어서 찾으면 주소 반환(Animation*)
		// 없으면 nullptr 반환
		Animation* FindAnimation(const std::wstring& _name);
		
		bool IsActiveAnimationComplete() { return mActiveAnimation->IsComplete(); }

		void PlayAnimation(const std::wstring& _name, bool _loop = false);

		bool GetAffectedCamera() { return mbAffectedCamera; }
		void SetAffectedCamera(bool _enable) { mbAffectedCamera = _enable; }

		float GetAlpha() { return mAlpha; }
		void SetAlpha(float _alpha) { mAlpha = _alpha; }

		math::Vector2 GetScale() { return mScale; }
		void SetScale(math::Vector2 scale) { mScale = scale; }


	private:
		std::map<std::wstring, Animation*> mAnimations;

		Animation* mActiveAnimation;
		bool m_bLoop;
		bool mbAffectedCamera;
		float mAlpha;
		math::Vector2 mScale;
	};

}
