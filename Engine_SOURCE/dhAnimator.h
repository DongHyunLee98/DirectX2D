#pragma once
#include "yaComponent.h"
#include "dhAnimation.h"

namespace ya
{
	class Animator : public Component
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}
			void operator()()
			{
				if (mEvent)
					mEvent();
			}

			std::function<void()> mEvent;
		};

		struct Events
		{
			Event startEvent;
			Event completeEvent;
			Event endEvent;
		};

		Animator();
		~Animator();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void Create(std::wstring name
			, std::shared_ptr<graphics::Texture> atlas
			, Vector2 leftTop
			, Vector2 size
			, UINT columnLength
			, Vector2 offset = Vector2::Zero
			, float duration = 0.0f);

	private:
		std::map<std::wstring, Animation*> mAnimations;
		std::map<std::wstring, Events*> mEvents;
		Animation* mActiveAnimation;

		bool mbLoop;
	};
}

/*

애니메이션
시간도 있어야함 leftTop size duration 들어옴
발 기준으로 잡을 offset
좌표만들고
애니메이션 만들고
나중순번으로 애니메이터 만듬 -> 이넘추가

이벤트만듬 -> 자세한건 스파인이벤트 방식
오퍼레이터()를 이용해서 함수를 함수 이거로 부름 -> 이벤트
멤버로 이벤트 하나 들고있고
현재 실행되고 있어야하는 애니메이션 멤버 추가

상수버퍼 만들어준다 랜더러에 CB슬롯
1번은 파티클/ 3번에 애니메이션슬롯 할당
globals에 t12로 아틀라스텍스쳐
상수버퍼b3 (랜더러에 CBUFER로 아틀라스있음)

랜더러cpp에 로드버퍼에 추가 레지스터 b3글로벌스 주의


-> 애니메이터 작업하면 끝
FSM은 다시할필요없? C++ FSM
map iter vector

*/