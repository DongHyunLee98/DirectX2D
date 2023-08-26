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
			if(width >= 10000.0f && width < 24999.0f && height > 700.0f)
				sprite.atlasSize = Vector2(800.0f / width, 700.0f / height);
			else if(width > 25000.0f && height > 890.0f)
				sprite.atlasSize = Vector2(800.0f / width, 700.0f / height);
			else if(width >= 8000 && width < 10000.0f && height > 400.0f && height <= 700.0f)
				sprite.atlasSize = Vector2(650.0f / width, 650.0f / height);
			else if (width > 8500 && width <= 8800 && height < 300.0f)
				sprite.atlasSize = Vector2(350.0f / width, 200.0f / height);
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