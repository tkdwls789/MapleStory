#include "exAnimator.h"
#include "exResourceManager.h"
#include "exTexture.h"

namespace ex
{

	Animator::Animator()
		: Component(enums::eComponentType::Animator)
		, mAlpha(1.0f)
		, mbAffectedCamera(true)
		, mScale(math::Vector2::One)
		, mActiveAnimation(nullptr)
		, m_bLoop(false)
	{
	}

	Animator::~Animator()
	{
 		for (auto& iter : mAnimations)
		{
			if (nullptr != iter.second)
			{
				delete iter.second;
				iter.second = nullptr;
			}
		}
	}

	void Animator::Initialize()
	{
	}

	void Animator::Update()
	{
		if (mActiveAnimation)
		{
			mActiveAnimation->Update();
			if (mActiveAnimation->IsComplete() && m_bLoop)
			{
				mActiveAnimation->Reset();
			}
		}
	}

	void Animator::Render(HDC hdc)
	{
		if (mActiveAnimation)
		{
			mActiveAnimation->Render(hdc);

		}
	}

	Animation* Animator::CreateAnimation(const std::wstring& name
		, class Texture* texture
		, math::Vector2 leftTop, math::Vector2 size
		, math::Vector2 interval, UINT spriteLength
		, math::Vector2 offset, float duration)
	{

		//// 애니메이션이 절대로 만들어 지지 않는다.
		//// 따라서 복사 생성자를 통해서 복사해서 처리한다.
		//// 첫번째 모션만 나오고 이미 값이 있기때문에 두번째 모션부터는 나오지않게된다
		//if (animation != nullptr)
		//{
		//	auto iter = m_Animations.find(name);
		//	if (iter == m_Animations.end())
		//	{
		//		animation = new Animation(*animation);
		//		if (animation)
		//		{
		//			animation->SetAnimator(this);
		//			m_Animations.insert(std::make_pair(name, animation));
		//			return;
		//		}
		//	}
		//	// 여기서 바로 return이 아니라 만들어진거를 가져다 써야되는데....
		//	return;
		//}
		Animation* animation = nullptr;
		animation = FindAnimation(name);
		if (animation != nullptr)
		{
			return animation;
		}

		animation = new Animation();
		animation->Create(name, texture
			, leftTop, size, interval, offset
			, spriteLength, duration);
		animation->SetAnimator(this);

		mAnimations.insert(std::make_pair(name, animation));

		return animation;

	}

	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		auto iter = mAnimations.find(name);
		if (iter == mAnimations.end())
		{
			return nullptr;
		}

		return iter->second;
	}

	void Animator::CreateAnimationFolder(const std::wstring& name
		, const std::wstring& path, math::Vector2 offset, float duration)
	{
		UINT width = 0;
		UINT height = 0;
		UINT fileCout = 0;

		std::filesystem::path fs(path);
		std::vector<Texture*> images = {};
		eTextureType tempType = eTextureType::None;

		// for each문 터짐 
		std::filesystem::recursive_directory_iterator it(fs);
		std::filesystem::recursive_directory_iterator end;
		//for (auto& p : std::filesystem::recursive_directory_iterator(path))
		for (; it != end; ++it)
		{
			std::wstring fileName = it->path().filename();
			std::wstring fullName = it->path();

			// 이미지 로드
			Texture* image = ResourceManager::Load<Texture>(fileName, fullName);
			tempType = image->GetTextType();

			images.push_back(image);

			if (width < image->GetWidth())
				width = image->GetWidth();

			if (height < image->GetHeight())
				height = image->GetHeight();

			fileCout++;
		}

		Texture* spriteSheet = Texture::Create(name, width * fileCout, height);

		// Video 기본 타입 Bmp로 설정
		spriteSheet->SetTextType(tempType);


		int idx = 0;
		for (Texture* image : images)
		{
			::BitBlt(spriteSheet->GetHdc(), width * idx, 0
				, image->GetWidth(), image->GetHeight()
				, image->GetHdc(), 0, 0, SRCCOPY);

			idx++;
		}

		CreateAnimation(name
			, spriteSheet, math::Vector2(0.0f, 0.0f)
			, math::Vector2(static_cast<float>(width), static_cast<float>(height))
			, math::Vector2(static_cast<float>(width), 0), fileCout, offset, duration);
	}

	void Animator::PlayAnimation(const std::wstring& name, bool loop)
	{

		Animation* animation = FindAnimation(name);
		if (animation == nullptr)
		{
			return;
		}

		// 현재 animation과 다시 FindAnimation animation이 같으면 리턴
		if (mActiveAnimation == animation)
		{
			return;
		}

		mActiveAnimation = animation;
		// 같은 animation이 들어와도 리셋되어서 animation이 끝까지 실행되지않음
		mActiveAnimation->Reset();
		m_bLoop = loop;

	}

}