#include "dhAnimation.h"
#include "dhTime.h"
#include "dhAnimator.h"
#include "dhRenderer.h"
#include "dhConstantBuffer.h"

namespace dh
{
	Animation::Animation()
		: Resource(enums::eResourceType::Animation)
		, mAtlas(nullptr)
		, mAnimator(nullptr)
		, mSprites{}
		, mIndex(-1)
		, mTime(0.0f)
		, mbComplete(false)
	{

	}

	Animation::~Animation()
	{
	}
	void Animation::Update()
	{
	}
	void Animation::LateUpdate()
	{
		if (mbComplete)
			return;

		mTime += Time::DeltaTime();

		if (mSprites[mIndex].duration <= mTime)
		{
			mIndex++;
			mTime = 0.0f;

			if (mSprites.size() <= mIndex)
			{
				mIndex = mSprites.size() - 1;
				mbComplete = true;
			}
		}
	}
	void Animation::Render()
	{
	}
	void Animation::Create(std::wstring name
		, std::shared_ptr<graphics::Texture> atlas
		, Vector2 leftTop
		, Vector2 size
		, UINT columnLength
		, float duration
		, Vector2 offset)
	{
		SetKey(name);
		mAtlas = atlas;


		float width = (float)atlas->GetWidth();
		float height = (float)atlas->GetHeight();

		for (size_t i = 0; i < columnLength; i++)
		{
			Sprite sprite = {};
			sprite.leftTop.x = leftTop.x + (i * size.x) / width;
			sprite.leftTop.y = leftTop.y / height;
			sprite.size.x = size.x / width;
			sprite.size.y = size.y / height;
			sprite.offset = offset;

			// 큰 이미지용
			if(width >= 10000.0f && width < 24999.0f && height <= 800.0f && height > 670.0f)
				sprite.atlasSize = Vector2(800.0f / width, 700.0f / height);

			else if (width >= 10000.0f && width < 12000.0f && height <= 670.0f && height > 650.0f)
			sprite.atlasSize = Vector2(800.0f / width, 600.0f / height);

			// 9252x706
			// else if (width > 9500 && width <= 9000 && height < 800.0f && height >= 700.0f)
			// 	sprite.atlasSize = Vector2(600.0f / width, 700.0f / height);
			else if (width <= 12000.0f && width > 10000.0f && height <= 210.0f)
				sprite.atlasSize = Vector2(700.0f / width, 200.0f / height);

			// KnockOut
			else if (width > 13800 && width <= 13900 && height < 290.0f && height >= 280.0f)
				sprite.atlasSize = Vector2(600.0f / width, 200.0f / height);
			// EnterSpot
			else if (width > 8500 && width <= 8800 && height < 300.0f)
				sprite.atlasSize = Vector2(350.0f / width, 200.0f / height);


			// 9180x673
			else if(width <= 10000.0f && width > 8000 && height > 400.0f && height <= 710.0f)
				sprite.atlasSize = Vector2(650.0f / width, 670.0f / height);


			else if (width <= 8000.0f && width > 6000 && height > 400.0f && height <= 700.0f)
				sprite.atlasSize = Vector2(600.0f / width, 600.0f / height);

			// Vine1
			else if (width < 7000.0f && width >= 6000 && height <= 230.0f && height > 210.0f)
				sprite.atlasSize = Vector2(700.0f / width, 250.0f / height);

			// Vine2
			else if (width < 12300.0f && width >= 12200 && height <= 209.0f && height > 199.0f)
				sprite.atlasSize = Vector2(1000.0f / width, 200.0f / height);

			// CargneyDead
			else if (width < 6000.0f && width >= 5800 && height <= 640.0f && height > 630.0f)
				sprite.atlasSize = Vector2(700.0f / width, 700.0f / height);

			else
				sprite.atlasSize = Vector2(200.0f / width, 200.0f / height);

			sprite.duration = duration;

			mSprites.push_back(sprite);
		}

	}

	void Animation::Binds()
	{
		// texture bind
		mAtlas->BindShaderResource(graphics::eShaderStage::PS, 12);

		// AnimationCB
		renderer::AnimatorCB data = {};

		data.spriteLeftTop = mSprites[mIndex].leftTop;
		data.spriteSize = mSprites[mIndex].size;
		data.spriteOffset = mSprites[mIndex].offset;
		data.atlasSize = mSprites[mIndex].atlasSize;
		data.animationType = 1;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Animator];
		cb->SetData(&data);

		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
	}
	void Animation::Reset()
	{
		mTime = 0.0f;
		mbComplete = false;
		mIndex = 0;
	}
}