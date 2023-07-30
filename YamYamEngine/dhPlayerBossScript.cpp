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
		tr = GetOwner()->GetComponent<Transform>();
		at = GetOwner()->GetComponent<Animator>();

		// ���ҽ� �ҷ�����
		std::shared_ptr<Texture> EnterIdle = Resources::Load<Texture>(L"Idle_Enter_R", L"..\\Resources\\Texture\\PlayerBoss\\EnterIdle\\EnterIdle_R.png");
		std::shared_ptr<Texture> EnterIdleL = Resources::Load<Texture>(L"Idle_Enter_L", L"..\\Resources\\Texture\\PlayerBoss\\EnterIdle\\EnterIdle_L.png");
		std::shared_ptr<Texture> AirHit = Resources::Load<Texture>(L"Hit_Air", L"..\\Resources\\Texture\\PlayerBoss\\AirHit\\HitAir.png");
		std::shared_ptr<Texture> NormalJump = Resources::Load<Texture>(L"Jump_Normal", L"..\\Resources\\Texture\\PlayerBoss\\CupheadJump\\Jump.png");
		std::shared_ptr<Texture> AirDash = Resources::Load<Texture>(L"Dash_Air", L"..\\Resources\\Texture\\PlayerBoss\\DashAir\\DashAir.png");
		std::shared_ptr<Texture> NormalGhost = Resources::Load<Texture>(L"Ghost_Normal", L"..\\Resources\\Texture\\PlayerBoss\\Ghost\\Ghost.png");
		std::shared_ptr<Texture> NormalParry = Resources::Load<Texture>(L"Parry_Normal", L"..\\Resources\\Texture\\PlayerBoss\\HandParry\\Parry.png");
		std::shared_ptr<Texture> EffectParry = Resources::Load<Texture>(L"Parry_Effect", L"..\\Resources\\Texture\\PlayerBoss\\HandParry\\ParryHit.png");

		// Idle
		std::shared_ptr<Texture> StRIdle = Resources::Load<Texture>(L"Idle_Straight", L"..\\Resources\\Texture\\PlayerBoss\\IdleImage\\Straight\\cuphead_aim_straight_0001.png");
		std::shared_ptr<Texture> StLIdle = Resources::Load<Texture>(L"Idle_Straight_L", L"..\\Resources\\Texture\\PlayerBoss\\IdleImage\\Straight\\cuphead_aim_straight_0001_L.png");
		std::shared_ptr<Texture> UpIdle = Resources::Load<Texture>(L"Idle_Up_B", L"..\\Resources\\Texture\\PlayerBoss\\IdleImage\\Up\\IdleUp.png");
		std::shared_ptr<Texture> DownIdle = Resources::Load<Texture>(L"Idle_Down_B", L"..\\Resources\\Texture\\PlayerBoss\\IdleImage\\Down\\pIdleDown.png");

		// Idle Shoot
		std::shared_ptr<Texture> ShootRIdle = Resources::Load<Texture>(L"Idle_Shoot_R", L"..\\Resources\\Texture\\PlayerBoss\\Shoot\\Straight\\IdleShootR.png");
		std::shared_ptr<Texture> ShootLIdle = Resources::Load<Texture>(L"Idle_Shoot_L", L"..\\Resources\\Texture\\PlayerBoss\\Shoot\\Straight\\IdleShootL.png");
		std::shared_ptr<Texture> ShootUpIdle = Resources::Load<Texture>(L"Idle_Shoot_Up", L"..\\Resources\\Texture\\PlayerBoss\\Shoot\\Up\\IdleUpShoot.png");
		std::shared_ptr<Texture> ShootDownIdle = Resources::Load<Texture>(L"Idle_Shoot_Down", L"..\\Resources\\Texture\\PlayerBoss\\Shoot\\Down\\IdleShootDown.png");
		
		
		// Run
		std::shared_ptr<Texture> NormalRunR = Resources::Load<Texture>(L"Run_Normal_R", L"..\\Resources\\Texture\\PlayerBoss\\Run\\Normal\\RunNormalR.png");
		std::shared_ptr<Texture> NormalRunL = Resources::Load<Texture>(L"Run_Normal_L", L"..\\Resources\\Texture\\PlayerBoss\\Run\\Normal\\RunNormalL.png");

		// RunShoot
		std::shared_ptr<Texture> ShootingRunR = Resources::Load<Texture>(L"Run_Shooting_R", L"..\\Resources\\Texture\\PlayerBoss\\Run\\Shooting\\Straight\\RunShootR.png");
		std::shared_ptr<Texture> ShootingRunL = Resources::Load<Texture>(L"Run_Shooting_L", L"..\\Resources\\Texture\\PlayerBoss\\Run\\Shooting\\Straight\\RunShootL.png");
		// std::shared_ptr<Texture> EnterIdle = Resources::Load<Texture>(L"Run_Shooting_Diagonal_R", L"..\\Resources\\Texture\\PlayerBoss\\IRun\\Shooting\\Straight\\RunShootR.png");

		// ���ҽ� �ִϸ��̼����� ����
		at->Create(L"Idle_Enter_R", EnterIdle, Vector2(0.0f, 0.0f), Vector2(98.0f, 155.0f), 8);
		at->Create(L"Idle_Enter_L", EnterIdleL, Vector2(0.0f, 0.0f), Vector2(98.0f, 155.0f), 8);
		at->Create(L"Hit_Air", AirHit, Vector2(0.0f, 0.0f), Vector2(125.0f, 188.0f), 6);
		at->Create(L"Jump_Normal", NormalJump, Vector2(0.0f, 0.0f), Vector2(88.0f, 109.0f), 8);
		at->Create(L"Dash_Air", AirDash, Vector2(150.0f, 0.0f), Vector2(446.0f, 126.0f), 6);
		at->Create(L"Ghost_Normal", NormalGhost, Vector2(0.0f, 0.0f), Vector2(140.0f, 208.0f), 24);
		at->Create(L"Parry_Normal", NormalParry, Vector2(0.0f, 0.0f), Vector2(137.0f, 146.0f), 8);
		at->Create(L"Parry_Effect", EffectParry, Vector2(0.0f, 0.0f), Vector2(265.0f, 280.0f), 9);
		
		// Idle
		at->Create(L"Idle_Straight", StRIdle, Vector2(0.0f, 0.0f), Vector2(129.0f, 152.0f), 1);
		at->Create(L"Idle_Straight_L", StLIdle, Vector2(0.0f, 0.0f), Vector2(129.0f, 152.0f), 1);
		at->Create(L"Idle_Up_B", UpIdle, Vector2(0.0f, 0.0f), Vector2(106.0f, 175.0f), 8);
		at->Create(L"Idle_Down_B", DownIdle, Vector2(0.0f, 0.0f), Vector2(99.0f, 168.0f), 5);

		// IdleShoot
		at->Create(L"Idle_Shoot_R", ShootRIdle, Vector2(0.0f, 0.0f), Vector2(127.0f, 157.0f), 3);
		at->Create(L"Idle_Shoot_L", ShootLIdle, Vector2(0.0f, 0.0f), Vector2(127.0f, 157.0f), 3);
		at->Create(L"Idle_Shoot_Up", ShootUpIdle, Vector2(0.0f, 0.0f), Vector2(108.0f, 172.0f), 3);
		at->Create(L"Idle_Shoot_Down", ShootDownIdle, Vector2(0.0f, 0.0f), Vector2(101.0f, 169.0f), 3);

		// NormalRun
		at->Create(L"Run_Normal_R", NormalRunR, Vector2(0.0f, 0.0f), Vector2(135.0f, 162.0f), 16);
		at->Create(L"Run_Normal_L", NormalRunL, Vector2(0.0f, 0.0f), Vector2(135.0f, 162.0f), 16);

		// ShootingRun
		at->Create(L"Run_Shooting_R", ShootingRunR, Vector2(0.0f, 0.0f), Vector2(144.0f, 157.0f), 16);
		at->Create(L"Run_Shooting_L", ShootingRunL, Vector2(0.0f, 0.0f), Vector2(144.0f, 157.0f), 16);

		// ����
		at->PlayAnimation(L"Idle_Enter_R", true);
		// �׿�
		jumpTime = 0.0f;
		attackTime = 0.0f;
		dashTime = 0.0f;
	}

	void PlayerBossScript::Update()
	{
		pos = tr->GetPosition();

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
			break;
		case dh::PlayerBossScript::PlayerState::Jump:
			Jump();
			break;
		case dh::PlayerBossScript::PlayerState::Shoot:
			Shoot();
			break;
		case dh::PlayerBossScript::PlayerState::MovingShoot:
			MovingShoot();
			break;
		case dh::PlayerBossScript::PlayerState::UpDown:
			UpDown();
			break;
		case dh::PlayerBossScript::PlayerState::Dash:
			Dash();
			break;
		case dh::PlayerBossScript::PlayerState::Ghost:
			Ghost();
			break;
		case dh::PlayerBossScript::PlayerState::Hit:
			Hit();
			break;
		default:
			break;
		}

	}
	void PlayerBossScript::Complete()
	{
		int a = 0;
	}
	void PlayerBossScript::OnCollisionEnter(Collider2D* other)
	{
		// if(other == )
	}

	void PlayerBossScript::Idle()
	{
		if (Input::GetKey(eKeyCode::LEFT))
		{
			pState = PlayerState::Move;
			at->PlayAnimation(L"Run_Normal_L", true);
			dirR = false;
		}
		else if (Input::GetKey(eKeyCode::RIGHT) && !(Input::GetKey(eKeyCode::X)))
		{
			pState = PlayerState::Move;
			at->PlayAnimation(L"Run_Normal_R", true);
			dirR = true;
		}
		else if (Input::GetKey(eKeyCode::UP))
		{
			pState = PlayerState::UpDown;
			at->PlayAnimation(L"Idle_Up_B", true);
		}
		else if (Input::GetKey(eKeyCode::DOWN))
		{
			pState = PlayerState::UpDown;
			at->PlayAnimation(L"Idle_Down_B", true);
		}


		// Jump
		if (Input::GetKeyDown(eKeyCode::Z))
		{
			pState = PlayerState::Jump;
			at->PlayAnimation(L"Jump_Normal", false);
		}
		// Attack
		if (Input::GetKey(eKeyCode::X) && dirR == true)
		{
			pState = PlayerState::Shoot;
			at->PlayAnimation(L"Idle_Shoot_R", true);
		}
		else if (Input::GetKey(eKeyCode::X) && dirR == false)
		{
			pState = PlayerState::Shoot;
			at->PlayAnimation(L"Idle_Shoot_L", true);
		}
		// Dash
		if (Input::GetKey(eKeyCode::SPACE))
		{
			pState = PlayerState::Dash;
			at->PlayAnimation(L"Dash_Air", false);
		}



		// Ghost
		if (Input::GetKeyUp(eKeyCode::G))
		{
			pState = PlayerState::Ghost;
			at->PlayAnimation(L"Ghost_Normal", false);
			dirR = true;
		}
		// Hit
		if (Input::GetKeyUp(eKeyCode::H))
		{
			pState = PlayerState::Hit;
			at->PlayAnimation(L"Hit_Air", false);
			dirR = true;
		}

		// �ʻ�� V
	}

	void PlayerBossScript::Move()
	{
		// �̵���� ����
		if (Input::GetKey(eKeyCode::X) && dirR == true) // DIRüũ
		{
			// pos.x -= 2.0f * Time::DeltaTime();
			// tr->SetPosition(pos);
			pState = PlayerState::MovingShoot;
			at->PlayAnimation(L"Run_Shooting_R", true);
		}
		else if (Input::GetKey(eKeyCode::X) && dirR == false) // DIRüũ
		{
			// pos.x -= 2.0f * Time::DeltaTime();
			// tr->SetPosition(pos);
			pState = PlayerState::MovingShoot;
			at->PlayAnimation(L"Run_Shooting_L", true);
		}

		if (Input::GetKeyUp(eKeyCode::LEFT))
		{
			pState = PlayerState::Idle;
			at->PlayAnimation(L"Idle_Enter_L", true);
			dirR = false;
		}
		else if (Input::GetKeyUp(eKeyCode::RIGHT))
		{
			pState = PlayerState::Idle;
			at->PlayAnimation(L"Idle_Enter_R", true);
			dirR = true;
		}


		else if (Input::GetKeyUp(eKeyCode::UP))
		{
			pState = PlayerState::Idle;
			at->PlayAnimation(L"Idle_Enter_R", true);
		}
		else if (Input::GetKeyUp(eKeyCode::DOWN))
		{
			pState = PlayerState::Idle;
			at->PlayAnimation(L"Idle_Enter_R", true);
		}
	


		if (Input::GetKey(eKeyCode::UP))
		{
			// pos.y += 2.0f * Time::DeltaTime();
			// tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::DOWN))
		{
			// pos.y -= 2.0f * Time::DeltaTime();
			// tr->SetPosition(pos);
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

		// Jump
		if (Input::GetKeyDown(eKeyCode::Z))
		{
			pState = PlayerState::Jump;
			at->PlayAnimation(L"Jump_Normal", false);
		}
	}

	void PlayerBossScript::Enter()
	{
		
	}

	void PlayerBossScript::Aiming()
	{
	}

	void PlayerBossScript::Shoot()
	{
		// Attack
		//if (Input::GetKeyDown(eKeyCode::X))
		//{
		//	pState = PlayerState::Idle;
		//	at->PlayAnimation(L"Idle_Enter", false);
		//	dirR = true;
		//}
		// �̵���� ����
		if (Input::GetKey(eKeyCode::RIGHT) && dirR == true)
		{
			// pos.x -= 2.0f * Time::DeltaTime();
			// tr->SetPosition(pos);
			pState = PlayerState::MovingShoot;
			at->PlayAnimation(L"Run_Shooting_R", true);
		}
		else if (Input::GetKey(eKeyCode::LEFT) && dirR == false)
		{
			// pos.x -= 2.0f * Time::DeltaTime();
			// tr->SetPosition(pos);
			pState = PlayerState::MovingShoot;
			at->PlayAnimation(L"Run_Shooting_L", true);
		}

		if (Input::GetKeyUp(eKeyCode::X) && dirR == true)
		{
			pState = PlayerState::Idle;
			at->PlayAnimation(L"Idle_Enter_R", true);
		}
		else if (Input::GetKeyUp(eKeyCode::X) && dirR == false)
		{
			pState = PlayerState::Idle;
			at->PlayAnimation(L"Idle_Enter_L", true);
		}

	}

	void PlayerBossScript::MovingShoot()
	{

		// �̵���� Ż�� (XŰ ��)
		if (Input::GetKeyUp(eKeyCode::X) && dirR == false)// (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::Pressed)) // DIRüũ
		{
			pState = PlayerState::Move;
			at->PlayAnimation(L"Run_Normal_L", true);
		}
		// �̵���� Ż�� (XŰ ��)
		else if (Input::GetKeyUp(eKeyCode::X) && dirR == true) // DIRüũ
		{
			pState = PlayerState::Move;
			at->PlayAnimation(L"Run_Normal_R", true);
		}

		// �̵���� Ż�� (������Ű ��)
		else if (Input::GetKeyUp(eKeyCode::RIGHT) && dirR == true) // && (Input::GetKeyState(eKeyCode::X) == eKeyState::Pressed)) // DIRüũ
		{
			pState = PlayerState::Shoot;
			at->PlayAnimation(L"Idle_Shoot_R", true);
		}
		else if (Input::GetKeyUp(eKeyCode::LEFT) && dirR == false) // && (Input::GetKeyState(eKeyCode::X) == eKeyState::Pressed)) // DIRüũ
		{
			pState = PlayerState::Shoot;
			at->PlayAnimation(L"Idle_Shoot_L", true);
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
	}

	void PlayerBossScript::UpDown()
	{
		if (Input::GetKeyUp(eKeyCode::UP))
		{
			pState = PlayerState::Idle;
			at->PlayAnimation(L"Idle_Enter_R", true);
		}
		else if (Input::GetKeyUp(eKeyCode::DOWN))
		{
			pState = PlayerState::Idle;
			at->PlayAnimation(L"Idle_Enter_R", true);
		}
	}

	void PlayerBossScript::Jump()
	{
		jumpTime += 3.8f * Time::DeltaTime();

		pos.y += 2.0f * Time::DeltaTime();
		if (jumpTime <= 2.9f)
		{
			if (Input::GetKeyDown(eKeyCode::Z))
			{
				pState = PlayerState::Jump;
				at->PlayAnimation(L"Parry_Normal", false);
			}
		}

		if (jumpTime > 3.0f)
		{
			pState = PlayerState::Idle;
			at->PlayAnimation(L"Idle_Enter_R", true);
			jumpTime = 0.0f;
		}
		// �������¿��� ZŰ�� �ٽ� ������ �丮

	}

	void PlayerBossScript::Dash()
	{
		pos.x += 2.0f * Time::DeltaTime();
		tr->SetPosition(pos);

		dashTime += 2.0f * Time::DeltaTime();
		if (dashTime >= 1.1f)
		{
			pState = PlayerState::Idle;
			at->PlayAnimation(L"Idle_Enter_R", true);
			dashTime = 0.0f;
		}
	}

	void PlayerBossScript::Ghost()
	{
		if (Input::GetKeyUp(eKeyCode::DOWN))
		{
			pState = PlayerState::Idle;
			at->PlayAnimation(L"Idle_Enter_R", true);
		}
		
	}

	void PlayerBossScript::Hit()
	{
		if (Input::GetKeyUp(eKeyCode::DOWN))
		{
			pState = PlayerState::Idle;
			at->PlayAnimation(L"Idle_Enter_R", true);
		}
	}


}
