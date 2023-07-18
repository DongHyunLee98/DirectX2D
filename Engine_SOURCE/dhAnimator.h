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

�ִϸ��̼�
�ð��� �־���� leftTop size duration ����
�� �������� ���� offset
��ǥ�����
�ִϸ��̼� �����
���߼������� �ִϸ����� ���� -> �̳��߰�

�̺�Ʈ���� -> �ڼ��Ѱ� �������̺�Ʈ ���
���۷�����()�� �̿��ؼ� �Լ��� �Լ� �̰ŷ� �θ� -> �̺�Ʈ
����� �̺�Ʈ �ϳ� ����ְ�
���� ����ǰ� �־���ϴ� �ִϸ��̼� ��� �߰�

������� ������ش� �������� CB����
1���� ��ƼŬ/ 3���� �ִϸ��̼ǽ��� �Ҵ�
globals�� t12�� ��Ʋ���ؽ���
�������b3 (�������� CBUFER�� ��Ʋ������)

������cpp�� �ε���ۿ� �߰� �������� b3�۷ι��� ����


-> �ִϸ����� �۾��ϸ� ��
FSM�� �ٽ����ʿ��? C++ FSM
map iter vector

*/