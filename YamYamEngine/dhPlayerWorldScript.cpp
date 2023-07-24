#include "dhPlayerWorldScript.h"
#include "dhCameraScript.h"
#include "dhTransform.h"
#include "dhGameObject.h"
#include "dhTime.h"
#include "dhInput.h"
#include "dhAnimator.h"
#include "dhResources.h"

namespace dh
{
	PlayerWorldScript::PlayerWorldScript()
		: dirR(false)
	{
	}
	PlayerWorldScript::~PlayerWorldScript()
	{
	}
	void PlayerWorldScript::Initialize()
	{
		// Animator* at = GetOwner()->GetComponent<Animator>();
		// if (at != nullptr) // 버그수정 -> 이걸 추가하지 않으면 애니메이션이 없는 스프라이트도 찾다가 튕김
		//	at->CompleteEvent(L"Idle") = std::bind(&PlayerOverWorldScript::Complete, this);

		// 애니메이션 목록 추가
		//at = GetOwner()->GetComponent<Animator>();
		//at->CompleteEvent(L"Idle") = std::bind(&PlayerScript::Complete, this);

		at = GetOwner()->GetComponent<Animator>();

		std::shared_ptr<Texture> DownIdle = Resources::Load<Texture>(L"Idle_Down", L"..\\Resources\\Texture\\playerWorld\\Idle_Down.png");
		std::shared_ptr<Texture> UpIdle = Resources::Load<Texture>(L"Idle_Up", L"..\\Resources\\Texture\\playerWorld\\Idle_Up.png");
		
		std::shared_ptr<Texture> LeftIdle = Resources::Load<Texture>(L"Idle_Left", L"..\\Resources\\Texture\\playerWorld\\Idle_Left.png");
		std::shared_ptr<Texture> RightIdle = Resources::Load<Texture>(L"Idle_Right", L"..\\Resources\\Texture\\playerWorld\\Idle_Right.png");
		
		std::shared_ptr<Texture> DownWalk = Resources::Load<Texture>(L"Walk_Down", L"..\\Resources\\Texture\\playerWorld\\Walk_Down.png");
		std::shared_ptr<Texture> UpWalk = Resources::Load<Texture>(L"Walk_Up", L"..\\Resources\\Texture\\playerWorld\\Walk_Up.png");

		std::shared_ptr<Texture> LeftWalk = Resources::Load<Texture>(L"Walk_Left", L"..\\Resources\\Texture\\playerWorld\\Walk_Left.png");
		std::shared_ptr<Texture> RightWalk = Resources::Load<Texture>(L"Walk_Right", L"..\\Resources\\Texture\\playerWorld\\Walk_Right.png");

		std::shared_ptr<Texture> Enter = Resources::Load<Texture>(L"Enter", L"..\\Resources\\Texture\\playerWorld\\Enter.png");
		

		// 대각선
		// std::shared_ptr<Texture> EnterObject = Resources::Load<Texture>(L"LeftDash", L"..\\Resources\\Texture\\playerWorld\\playerWorld.png");
		// 엔터

		// 너비,높이

		at->Create(L"Idle_Down", DownIdle, Vector2(0.0f, 0.0f), Vector2(103.0f, 100.0f), 2);
		at->Create(L"Idle_Up", UpIdle, Vector2(0.0f, 0.0f), Vector2(102.0f, 108.0f), 4);

		at->Create(L"Idle_Left", LeftIdle, Vector2(0.0f, 0.0f), Vector2(103.0f, 100.0f), 4);
		at->Create(L"Idle_Right", RightIdle, Vector2(0.0f, 0.0f), Vector2(103.0f, 100.0f), 4);

		at->Create(L"Walk_Up", UpWalk, Vector2(0.0f, 0.0f), Vector2(102.0, 108.0f), 13);
		at->Create(L"Walk_Down", DownWalk, Vector2(0.0f, 0.0f), Vector2(104.0f, 108.0f), 13);
		
		at->Create(L"Walk_Left", LeftWalk, Vector2(0.0f, 0.0f), Vector2(103.0f, 108.0f), 10);
		at->Create(L"Walk_Right", RightWalk, Vector2(0.0f, 0.0f), Vector2(103.0f, 108.0f), 10);

		at->Create(L"Enter", Enter, Vector2(0.0f, 0.0f), Vector2(100.0f, 120.0f), 5);

		// at->PlayAnimation(L"Idle_Down", true);
		at->PlayAnimation(L"Idle_Down", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"LinkSprite", L"..\\Resources\\Texture\\linkSprites.png");
		//at->Create(L"Idle", atlas, Vector2(0.0f, 0.0f), Vector2(120.0f, 130.0f), 3);
		//at->PlayAnimation(L"Idle", true);
	}

	void PlayerWorldScript::Update()
	{

		tr = GetOwner()->GetComponent<Transform>();
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
		case PlayerWorldScript::PlayerState::Idle:
			Idle();
			break;
		case dh::PlayerWorldScript::PlayerState::Move:
			Move();
			break;
		case dh::PlayerWorldScript::PlayerState::Enter:
			Enter();
		default:
			break;
		}
		
	}
	void PlayerWorldScript::Complete()
	{
		int a = 0;
	}

	void PlayerWorldScript::Idle()
	{
		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			pState = PlayerState::Move;
			at->PlayAnimation(L"Walk_Left", true);
			dirR = false;
		}
		else if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			pState = PlayerState::Move;
			at->PlayAnimation(L"Walk_Right", true);
			dirR = true;
		}
		else if (Input::GetKeyDown(eKeyCode::UP))
		{
			pState = PlayerState::Move;
			at->PlayAnimation(L"Walk_Up", true);
		}
		else if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			pState = PlayerState::Move;
			at->PlayAnimation(L"Walk_Down", true);
		}

		if (Input::GetKeyUp(eKeyCode::C))
		{
			pState = PlayerState::Enter;
			at->PlayAnimation(L"Enter", false);
		}
	}

	void PlayerWorldScript::Move()
	{
		if (Input::GetKeyUp(eKeyCode::LEFT))
		{
			pState = PlayerState::Idle;
			at->PlayAnimation(L"Idle_Left", true);
			dirR = false;
		}
		else if (Input::GetKeyUp(eKeyCode::RIGHT))
		{
			pState = PlayerState::Idle;
			at->PlayAnimation(L"Idle_Right", true);
			dirR = true;
		}
		else if (Input::GetKeyUp(eKeyCode::UP))
		{
			pState = PlayerState::Idle;
			at->PlayAnimation(L"Idle_Up", true);
		}
		else if (Input::GetKeyUp(eKeyCode::DOWN))
		{
			pState = PlayerState::Idle;
			at->PlayAnimation(L"Idle_Down", true);
		}


		if (Input::GetKey(eKeyCode::UP))
		{
			pos.y += 2.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::DOWN))
		{
			pos.y -= 2.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			pos.x -= 2.0f * Time::DeltaTime();
			tr->SetPosition(pos);
			dirR = false;
		}
		else if (Input::GetKey(eKeyCode::RIGHT))
		{
			pos.x += 2.0f * Time::DeltaTime();
			tr->SetPosition(pos);
			dirR = true;
		}

		if (Input::GetKeyUp(eKeyCode::C))
		{
			pState = PlayerState::Enter;
			at->PlayAnimation(L"Enter", false);
		}
	}

	void PlayerWorldScript::Enter()
	{
		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			pState = PlayerState::Idle;
			at->PlayAnimation(L"Idle_Down", true);
		}
		if (Input::GetKeyDown(eKeyCode::UP))
		{
			pState = PlayerState::Idle;
			at->PlayAnimation(L"Idle_Down", true);
		}
	}

}
