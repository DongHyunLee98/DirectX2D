#include "dhAnimator.h"
#include "dhResources.h"

namespace dh
{
	Animator::Animator()
		: Component(eComponentType::Animator)
	{
	}
	Animator::~Animator()
	{
		for (auto& iter : mAnimations)
		{
			delete iter.second;
			iter.second = nullptr;
		}


		for (auto& iter : mEvents)
		{
			delete iter.second;
			iter.second = nullptr;
		}
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
			Events* events
				= FindEvents(mActiveAnimation->GetKey());
			if (events)
				events->completeEvent();

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

	void Animator::Create(const std::wstring& name
		, std::shared_ptr<graphics::Texture> atlas
		, Vector2 leftTop
		, Vector2 size
		, UINT columnLength
		, Vector2 offset
		, float duration)
	{
		Animation* animation = FindAnimation(name);
		if (nullptr != animation)
			return;

		animation = new Animation();
		animation->SetKey(name);

		animation->Create(name
			, atlas
			, leftTop
			, size
			, columnLength
			, offset
			, duration);

		mAnimations.insert(std::make_pair(name, animation));

		Events* events = FindEvents(name);
		if (events != nullptr)
			return;

		events = new Events();
		mEvents.insert(std::make_pair(name, events));
	}
	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		std::map<std::wstring, Animation*>::iterator iter
			= mAnimations.find(name);

		if (iter == mAnimations.end())
			return nullptr;

		return iter->second;
	}
	Animator::Events* Animator::FindEvents(const std::wstring& name)
	{
		std::map<std::wstring, Events*>::iterator iter
			= mEvents.find(name);

		if (iter == mEvents.end())
			return nullptr;

		return iter->second;
	}
	void Animator::PlayAnimation(const std::wstring& name, bool loop)
	{
		Animation* prevAnimation = mActiveAnimation;

		Events* events;
		if (prevAnimation != nullptr)
		{

			events = FindEvents(prevAnimation->GetKey());
			if (events)
				events->endEvent();
		}

		Animation* animation = FindAnimation(name);
		if (animation)
		{
			mActiveAnimation = animation;
		}

		events = FindEvents(mActiveAnimation->GetKey());
		if (events)
			events->startEvent();

		mbLoop = loop;
		mActiveAnimation->Reset();
	}
	void Animator::Binds()
	{
		if (mActiveAnimation == nullptr)
			return;

		mActiveAnimation->Binds();
	}
	std::function<void()>& Animator::StartEvent(const std::wstring key)
	{
		Events* events = FindEvents(key);

		return events->startEvent.mEvent;
	}

	std::function<void()>& Animator::CompleteEvent(const std::wstring key)
	{
		Events* events = FindEvents(key);

		return events->completeEvent.mEvent;
	}

	std::function<void()>& Animator::EndEvent(const std::wstring key)
	{
		Events* events = FindEvents(key);

		return events->endEvent.mEvent;
	}
	/*
	void Animator::CreateAnimations(const std::wstring& path, Vector2 offset, float duration)
	{
		UINT width = 0;
		UINT height = 0;
		UINT fileCount = 0;

		std::filesystem::path fs(path);
		std::vector<Image*> images = {};
		for (const auto& p : std::filesystem::recursive_directory_iterator(path))
		{
			std::wstring fileName = p.path().filename();
			std::wstring fullName = path + L"\\" + fileName;

			const std::wstring ext = p.path().extension();
			if (ext == L".png")
				continue;

			Image* image = Resources::Load<Image>(fileName, fullName);
			images.push_back(image);

			if (width < image->GetWidth())
			{
				width = image->GetWidth();
			}
			if (height < image->GetHeight())
			{
				height = image->GetHeight();
			}
			fileCount++;
		}

		std::wstring key = fs.parent_path().filename();
		key += fs.filename();
		mSpriteSheet = Image::Create(key, width * fileCount, height);
	}
	*/
}
