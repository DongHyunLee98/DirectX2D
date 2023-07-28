#include "dhPlayerBossScript.h"
#include "dhCameraScript.h"
#include "dhTransform.h"
#include "dhGameObject.h"
#include "dhTime.h"
#include "dhInput.h"
#include "dhAnimator.h"
#include "dhResources.h"

namespace dh
{
	PlayerBossScript::PlayerBossScript()
		: dirR(false)
	{
	}
	PlayerBossScript::~PlayerBossScript()
	{
	}
	void PlayerBossScript::Initialize()
	{
		// Animator* at = GetOwner()->GetComponent<Animator>();
		// if (at != nullptr) // 버그수정 -> 이걸 추가하지 않으면 애니메이션이 없는 스프라이트도 찾다가 튕김
		//	at->CompleteEvent(L"Idle") = std::bind(&PlayerOverWorldScript::Complete, this);

		// 애니메이션 목록 추가
		//at = GetOwner()->GetComponent<Animator>();
		//at->CompleteEvent(L"Idle") = std::bind(&PlayerScript::Complete, this);
		tr = GetOwner()->GetComponent<Transform>();

		at = GetOwner()->GetComponent<Animator>();

		std::shared_ptr<Texture> EnterIdle = Resources::Load<Texture>(L"Idle_Enter", L"..\\Resources\\Texture\\PlayerBoss\\EnterIdle\\EnterIdle.png");


		// 대각선
		// std::shared_ptr<Texture> EnterObject = Resources::Load<Texture>(L"LeftDash", L"..\\Resources\\Texture\\playerWorld\\playerWorld.png");
		// 엔터

		// 너비,높이

		at->Create(L"Idle_Enter", EnterIdle, Vector2(0.0f, 0.0f), Vector2(98.0f, 155.0f), 8);


		// at->PlayAnimation(L"Idle_Down", true);
		at->PlayAnimation(L"Idle_Enter", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"LinkSprite", L"..\\Resources\\Texture\\linkSprites.png");
		//at->Create(L"Idle", atlas, Vector2(0.0f, 0.0f), Vector2(120.0f, 130.0f), 3);
		//at->PlayAnimation(L"Idle", true);
	}

	void PlayerBossScript::Update()
	{

		pos = tr->GetPosition();



		//if (Input::GetKey(eKeyCode::LEFT))
		//{
		//	pos.x -= 2.0f * Time::DeltaTime();
		//	tr->SetPosition(pos);
		//}
		//else if (Input::GetKey(eKeyCode::RIGHT))
		//{
		//	pos.x += 2.0f * Time::DeltaTime();
		//	tr->SetPosition(pos);
		//}
		//else if (Input::GetKey(eKeyCode::DOWN))
		//{
		//	pos.y -= 2.0f * Time::DeltaTime();
		//	tr->SetPosition(pos);
		//}
		//else if (Input::GetKey(eKeyCode::UP))
		//{
		//	pos.y += 2.0f * Time::DeltaTime();
		//	tr->SetPosition(pos);
		//}

		switch (pState)
		{
			// case dh::PlayerOverWorldScript::PlayerState::Idle:
			// 	break;
		case PlayerBossScript::PlayerState::Idle:
			Idle();
			break;
		case dh::PlayerBossScript::PlayerState::Move:
			Move();
			break;
		case dh::PlayerBossScript::PlayerState::Enter:
			Enter();
		default:
			break;
		}

	}
	void PlayerBossScript::Complete()
	{
		int a = 0;
	}

	void PlayerBossScript::Idle()
	{
		
	}

	void PlayerBossScript::Move()
	{
		
	}

	void PlayerBossScript::Enter()
	{
		
	}

}
