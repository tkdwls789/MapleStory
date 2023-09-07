#include "exSpriteRenderer.h"
#include "exTransform.h"
#include "exGameObject.h"
#include "exCamera.h"
#include "exSceneManager.h"


namespace ex
{
	SpriteRenderer::SpriteRenderer()
		: Component(enums::eComponentType::SpriteRenderer)
		, mScale(math::Vector2::One)
		, mbAffectCamere(true)
		, mTexture(nullptr)
		, mAlpha(1.0f)

	{
	}

	SpriteRenderer::~SpriteRenderer()
	{
	}

	void SpriteRenderer::Initialize()
	{
	}

	void SpriteRenderer::Update()
	{
	}


	void SpriteRenderer::Render(HDC hdc)
	{
		if (nullptr == mTexture)
		{
			return;
		}

		GameObject* gameObj = GetOwner();
		if (nullptr == gameObj)
		{
			return;
		}

		Transform* tr = gameObj->GetTransform();
		if (nullptr == tr)
		{
			return;
		}

		math::Vector2 textureSize = mTexture->GetSize();

		mTexture->Render(hdc
			, tr->GetPosition()
			, textureSize
			, math::Vector2::Zero
			, textureSize
			, mbAffectCamere
			, mScale
			, mAlpha);
	}
}