#include "dhPlayerScript.h"
#include "dhCameraScript.h"
#include "dhTransform.h"
#include "dhGameObject.h"
#include "dhTime.h"
#include "dhInput.h"
#include "dhAnimator.h"

namespace dh
{
	PlayerScript::PlayerScript()
	{
	}
	PlayerScript::~PlayerScript()
	{
	}
	void PlayerScript::Initialize()
	{
		
		Animator* at = GetOwner()->GetComponent<Animator>();
		if(at != nullptr) // 버그수정 -> 이걸 추가하지 않으면 애니메이션이 없는 스프라이트도 찾다가 튕김
			at->CompleteEvent(L"Idle") = std::bind(&PlayerScript::Complete, this);
	}

	void PlayerScript::Update()
	{

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();



		if (Input::GetKey(eKeyCode::LEFT))
		{
			pos.x -= 5.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::RIGHT))
		{
			pos.x += 5.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::DOWN))
		{
			pos.y -= 5.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::UP))
		{
			pos.y += 5.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}

	}
	void PlayerScript::Complete()
	{
		int a = 0;
	}
}
