#include "dhAnimator.h"

namespace dh
{
	Animator::Animator()
		: Component(eComponentType::Animator)
	{
	}
	Animator::~Animator()
	{
	}
	void Animator::Initialize()
	{
	}
	void Animator::Update()
	{
		if (mActiveAnimation == nullptr)
			return;

		if (mActiveAnimation->IsComplete() && mbLoop)
		{
			mActiveAnimation->Reset();
		}

		mActiveAnimation->LateUpdate();
	}
	void Animator::LateUpdate()
	{
	}
	void Animator::Render()
	{
	}
	Animation* Animator::Create(const std::wstring& name
		, std::shared_ptr<graphics::Texture> atlas
		, Vector2 leftTop
		, Vector2 size
		, UINT columnLength
		, Vector2 offset
		, float duration)
	{
		Animation* animation = FindAnimation(name);
		if (nullptr != animation)
			return animation;

		animation = new Animation();
		animation->SetKey(name);

		animation->Create(name
			, atlas
			, leftTop
			, size
			, columnLength
			, offset
			, duration);

		// 애니메이션에서 랜더할필요없고 세이더에서 해준다.
		mAnimations.insert(std::make_pair(name, animation)); 
	}

	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		std::map<std::wstring, Animation*>::iterator iter
			= mAnimations.find(name);

		if (iter == mAnimations.end())
			return nullptr;

		return iter->second;
	}

	void Animator::PlayAnimation(const std::wstring& name, bool loop)
	{
		Animation* animation = FindAnimation(name);
		if (animation)
		{
			mActiveAnimation = animation;
		}

		mbLoop = loop;
		mActiveAnimation->Reset();
	}

	void Animator::Binds()
	{
		if (mActiveAnimation == nullptr)
			return;

		mActiveAnimation->Binds();
	}
}
