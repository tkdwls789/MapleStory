#include "exAnimation.h"
#include "exTexture.h"
#include "exAnimator.h"
#include "exTime.h"
#include "exTransform.h"
#include "exGameObject.h"
#include "exCamera.h"

namespace ex
{
	// 초기화
	Animation::Animation()
		: mAnimator(nullptr)
		, mTexture(nullptr)
		, mSpriteSheet{}
		, mIndex(-1)
		, mTime(0.0f)
		, mbComplete(false)
	{
	}

	// 전달받은 Animation을 깊은 복사로 복사해낸다.
	Animation::Animation(const Animation& _anim)
		: mAnimator(nullptr)
		, mTexture(_anim.mTexture)
		, mIndex(-1)
		, mTime(_anim.mTime)
		, mbComplete(false)
	{
		// 그냥 내 습관임(니가 다시 확인해봐) 복사하기 위해서 가변배열을 resize()로 공간의 크기를 변경해준다.
		mSpriteSheet.resize(_anim.mSpriteSheet.size());

		// 전달받은 애니메이션이 관리하고 있는 Sprite Sheet의 시작부터 끝까지를 가져와서
		// 복사해준다.
		std::copy(_anim.mSpriteSheet.begin(), _anim.mSpriteSheet.end(), mSpriteSheet.begin());
	}

	Animation::~Animation()
	{
	}

	void Animation::Initialize()
	{
	}


	void Animation::Update()
	{
		// 완료되었으면 더 이상 재생할 필요가 없으므로 데이터의 갱신을 해 주지 않음.
		if (mbComplete)
		{
			return;
		}

		// Time 클래스로부터 델타타임을 받아와서 현재 프레임이 되고 난 후의 재생 시간에 더해준다.
		mTime += Time::GetDeltaTime();
		// 현재 재생할 순번의 시트의 duration보다 해당 프레임이 되고 난 후의 시간이 더 크다면
		// 다음 프레임으로 변경해야 한다.
		if (mSpriteSheet[mIndex].duration < mTime)
		{
			// 프레임이 변경될 것이므로 유지시간에 관련된 변수인 m_Time을 0.f로 초기화해준다.
			mTime = 0.0f;

			// m_Index는 0 부터 시작하므로 크기의 -1보다 작다면 인덱스를 증가시켜준다.
			if (mIndex < mSpriteSheet.size() - 1)
			{
				mIndex++;
			}
			// else는 같거나 크다는 것이므로 마지막 프레임에 도달한 것이기 때문에 m_bComplete를
			// true로 바꿔준다.
			else
			{
				mbComplete = true;
			}
		}
	}

	// 전달받은 HDC를 이용하여 프레임을 그려낸다.
	void Animation::Render(HDC _hdc)
	{
		// 그려낼 때 참고할 아틀라스 텍스처가 nullptr이라면 존재하지 않는 것이므로
		// 예외처리를 위해서 return 처리
		if (mTexture == nullptr)
		{
			return;

		}

		// 현재 index의 Sprite 정보를 가져온다.
		Sprite sprite = mSpriteSheet[mIndex];

		// 예외처리를 위한 처리
		if (nullptr == mAnimator)
		{
			return;
		}

		// 트랜스폼 컴포넌트를 가져올 방법은 GameObject에 접근하는 방법밖에 없는데
		// GameObject에 접근하기 위해서 보유하고 있는 m_Animator로부터 GetOwner()를 호출하여
		// Transform을 보유할 것으로 예상되는 GameObject에 접근한다.
		// 그 다음으로 GetComponent<Transform>()으로 해당 GameObject가 보유한 Transform 객체를 가져온다.
		GameObject* owner = mAnimator->GetOwner();
		// 예외처리
		if (!owner)
		{
			return;
		}

		Transform* tr = mAnimator->GetOwner()->GetComponent<Transform>();
		// 예외처리
		if (!tr)
		{
			return;
		}

		// 위치를 트랜스폼으로부터 가져오고 현재 프레임에 offset 값을 더해서 그려질 최종 위치를 구한다.
		math::Vector2 pos = tr->GetPosition() + sprite.offset;

		// m_Texture에 접근해서 Render 함수를 호출한다.
		mTexture->Render(_hdc
			, pos
			, sprite.size
			, sprite.leftTop
			, sprite.size
			, mAnimator->GetAffectedCamera()
			, mAnimator->GetScale()
			, mAnimator->GetAlpha());
	}

	// 전달받은 인자를 이용해서 m_SpriteSheet에 실제 프레임 정보를 넣어준다.
	// 근데, 이 함수는 애니메이션을 만들 때, 한 줄로 프레임을 찾아내서 넣어준다.
	void Animation::Create(const std::wstring& _name, Texture* _texture
		, math::Vector2 _leftTop, math::Vector2 _size, math::Vector2 _interval, math::Vector2 _offset
		, UINT _spriteLength, float _duration)
	{
		SetName(_name);
		mTexture = _texture;


		for (UINT i = 0; i < _spriteLength; i++)
		{
			int temp = i;

			// 이미지를 뒤에서 부터 읽어야 할 경우 1번 인덱스부터 읽게 만들어준다.
			if (0 > _interval.x)
			{
				++temp;
			}

			Sprite sprite = {};

			sprite.leftTop.x = _leftTop.x + (_interval.x * temp);
			sprite.leftTop.y = _leftTop.y;
			// 아틀라스 이미지의 한 동작이 다음줄 까지 이어질때
			// 가져온 텍스처의 이미지의 가로 길이를 넘어서 다음줄에서 다시 읽어야 할경우
			if (sprite.leftTop.x > _texture->GetWidth())
			{
				sprite.leftTop.x = sprite.leftTop.x - _texture->GetWidth();
				sprite.leftTop.y = _leftTop.y + _size.y;
			}
			sprite.size = _size;
			sprite.offset = _offset;
			sprite.duration = _duration;

			mSpriteSheet.push_back(sprite);
		}
	}

	void Animation::Reset()
	{
		mTime = 0.0f;
		mIndex = 0;
		mbComplete = false;
	}

}
