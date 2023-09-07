#pragma once
// Resource를 상속받기 위해서 Resource.h 헤더 포함
#include "exResource.h"

namespace ex
{
	// 전방선언 추가
	class Texture;
	class Animator;

	// Animation 클래스는 public으로 Resource를 상속받는다.
	class Animation : public Resource
	{
	public:
		// public으로 구조체 Sprite를 선언한다.
		// Sprite는 애니메이션의 각 프레임을 의미한다고 생각하면 된다.
		// http://popkon.konkuk.ac.kr/news/articleView.html?idxno=10836 프레임에 대한 설명
		struct Sprite
		{
			// Sprite는 일반적으로 아틀라스 이미지를 사용한다고 간주하기 때문에 해당 프레임의 영역이
			// 어디일지를 알 필요가 존재한다.
			// Atlas Image는 여러 개의 프레임 이미지를 모아둔 거대한 이미지 파일이다.
			// Atlas Image가 존재하는 이유는 메모리의 계층구조 때문이다.
			// 일반적으로 컴퓨터 구조에서 CPU의 레지스터 내부를 접근하는 것이 가장 고속이고
			// 그 다음이 우리가 아는 램(Memory)에 접근하는 것이 빠르고
			// 그 다음으로 우리가 아는 하드디스크 혹은 SSD에 접근하는 것이 빠르다.
			// 이미지 파일은 하드디스크 혹은 SSD에 접근해서 파일을 읽고 이를 램(Memory)에 올리는 동작이기
			// 때문에 아틀라스 이미지에 여러 개의 프레임 이미지를 합쳐서 사용하는 것을 선호하게 되었다.
			// 즉 여러 개의 프레임 이미지가 각 파일 하나 하나로 이루어져 있다면 이를 읽는 시간이 각각
			// 필요해져서 불필요한 로드 시간이 증가하게 된다. 이러한 불필요한 시간 혹은 비용을 오버헤드라고
			// 한다.

			// LeftTop : 좌상단의 위치 좌표
			math::Vector2 leftTop;
			// Size : 좌상단으로부터 우하단까지의 크기
			math::Vector2 size;
			// offset : 별도로 위치를 변조해서 그려주기 위해 별도로 가지는 값
			math::Vector2 offset;
			// duration : 해당 프레임이 재생(유지)될 시간(유지 시간이라고 생각하면 된다)
			float duration;

			// Sprite의 초기화를 위한 구조체 생성자
			Sprite()
				: leftTop(math::Vector2::Zero)
				, size(math::Vector2::Zero)
				, offset(math::Vector2::Zero)
				, duration(0.0f)
			{

			}
		};

	public:
		// 생성자
		Animation();
		// 복사 생성자
		Animation(const Animation& _anim);
		// 가상 소멸자
		// virtual 키워드를 붙임으로써 자손 클래스부터 부모 클래스까지 각각의 소멸자를 호출하면서
		// 각각의 클래스가 가지는 변수 등의 공간을 삭제시켜준다.
		virtual ~Animation();

		// 초기화를 위한 Initialize 함수
		void Initialize();
		// 애니메이션의 재생과 관련된 로직을 처리해준다.
		void Update();
		// 애니메이션의 프레임을 그려준다.
		void Render(HDC _hdc);

		// 부모 클래스인 Resource로부터 override(재정의)한 Load 함수.
		// 추후 애니메이션 자체를 파일로 저장할 가능성이 있지만
		// 지금은 사용하지 않기 때문에 간단하게 return S_FALSE 처리
		virtual HRESULT Load(const std::wstring& _path) { return S_FALSE; };

		// 애니메이션을 생성해준다.
		// 인자 목록
		// name : 애니메이션의 이름
		// Texture : 아틀라스 텍스처
		// leftTop : 각 프레임이 시작할 좌상단 위치
		// size : 각 프레임의 크기
		// spriteLength : 아틀라스 텍스처에서 추출할 프레임의 개수
		// duration : 각 프레임당 유지 시간
		void Create(const std::wstring& _name, class Texture* _texture
					, math::Vector2 _leftTop, math::Vector2 _size, math::Vector2 _Interval, math::Vector2 _offset
					, UINT _spriteLength, float _duration);

		// 재생과 관련된 정보를 전부 초기화해준다. 즉, 애니메이션이 재생되기 전으로
		// 되돌아 간다는 뜻이다.
		void Reset();

		// 애니메이션의 재생이 완료되었는지를 반환하는 getter 함수
		bool IsComplete() { return mbComplete; }
		// 자신을 관리하고 있는 애니메이터를 설정해준다. 게임 오브젝트의 컴포넌트 중
		// Transform에 접근해서 현재 위치를 알아내야 이에 영향을 받아서 그려줄 위치를
		// 정해줄 수 있기 때문에 이 애니메이션을 가지고 있는 애니메이터를 설정해준다.
		void SetAnimator(Animator* _animator) { mAnimator = _animator; }

		// private 접근 지정을 해 두었다면 아래의 변수는 외부에서 접근할 수 없다는 뜻이다.
	private:
		// 해당 애니메이션을 관리하고 있는 애니메이터 객체를 가리킨다.
		Animator* mAnimator;
		// 이 애니메이션이 render될 때, 참조하여 그려낼 아틀라스 텍스처
		Texture* mTexture;

		// 각 프레임 정보를 가변 배열로 관리한다.
		std::vector<Sprite> mSpriteSheet;
		// 현재 프레임 번호
		int mIndex;
		// 현재 프레임으로 되고 난 후 재생된 시간
		float mTime;
		// 애니메이션의 재생 완료 여부
		bool mbComplete;
	};

}
