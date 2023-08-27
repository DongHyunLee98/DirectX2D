#include "dhPlayerBossScript.h"
#include "dhCameraScript.h"
#include "dhTransform.h"
#include "dhGameObject.h"
#include "dhTime.h"
#include "dhInput.h"
#include "dhResources.h"
#include "dhGroundScript.h"
#include "dhPlayerBullet.h"
#include "dhRigidbody.h"
#include "dhObject.h"
#include "dhMeshRenderer.h"
#include "dhMesh.h"

namespace dh
{
	PlayerBossScript::PlayerBossScript()
		: dirR(true)
		, jumpState(false)
		, jumpTime(0.0f)
		, attackTime(0.0f)
		, dashTime(0.0f)
		, jumpTimeCheck(false)
		, bulletPos(0.0f,0.0f,0.0f)
		, pos(0.0f,0.0f,0.0f)
		, mBulletTime(0.0f)
		, bulletCoolDown(false)
		, mBulletAttackCool(0.0f)
		, getVelocityCount(0.0f)
		, VelocityGetSwitch(false)
	{
	}
	PlayerBossScript::~PlayerBossScript()
	{
	}
	void PlayerBossScript::Initialize()
	{
		tr = GetOwner()->GetComponent<Transform>();
		at = GetOwner()->AddComponent<Animator>();
		cd = GetOwner()->AddComponent<Collider2D>();
		mRigidbody = GetOwner()->AddComponent<Rigidbody>();

		// 리소스 불러오기
		std::shared_ptr<Texture> EnterIdle = Resources::Load<Texture>(L"Idle_Enter_R", L"..\\Resources\\Texture\\PlayerBoss\\EnterIdle\\EnterIdle_R.png");
		std::shared_ptr<Texture> EnterIdleL = Resources::Load<Texture>(L"Idle_Enter_L", L"..\\Resources\\Texture\\PlayerBoss\\EnterIdle\\EnterIdle_L.png");
		std::shared_ptr<Texture> AirHit = Resources::Load<Texture>(L"Hit_Air", L"..\\Resources\\Texture\\PlayerBoss\\AirHit\\HitAir.png");
		std::shared_ptr<Texture> NormalJumpR = Resources::Load<Texture>(L"Jump_Normal_R", L"..\\Resources\\Texture\\PlayerBoss\\CupheadJump\\Jump_R.png");
		std::shared_ptr<Texture> NormalJumpL = Resources::Load<Texture>(L"Jump_Normal_L", L"..\\Resources\\Texture\\PlayerBoss\\CupheadJump\\Jump_L.png");
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

		// 리소스 애니메이션으로 생성
		at->Create(L"Idle_Enter_R", EnterIdle, Vector2(0.0f, 0.0f), Vector2(98.0f, 155.0f), 8, 0.08f);
		at->Create(L"Idle_Enter_L", EnterIdleL, Vector2(0.0f, 0.0f), Vector2(98.0f, 155.0f), 8, 0.08f);
		at->Create(L"Hit_Air", AirHit, Vector2(0.0f, 0.0f), Vector2(125.0f, 188.0f), 6);
		at->Create(L"Jump_Normal_R", NormalJumpR, Vector2(0.0f, 0.0f), Vector2(88.0f, 109.0f), 8, 0.06f);
		at->Create(L"Jump_Normal_L", NormalJumpL, Vector2(0.0f, 0.0f), Vector2(88.0f, 109.0f), 8, 0.06f);
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
		at->Create(L"Idle_Shoot_R", ShootRIdle, Vector2(0.0f, 0.0f), Vector2(127.0f, 157.0f), 3, 0.07f);
		at->Create(L"Idle_Shoot_L", ShootLIdle, Vector2(0.0f, 0.0f), Vector2(127.0f, 157.0f), 3, 0.07f);
		at->Create(L"Idle_Shoot_Up", ShootUpIdle, Vector2(0.0f, 0.0f), Vector2(108.0f, 172.0f), 3);
		at->Create(L"Idle_Shoot_Down", ShootDownIdle, Vector2(0.0f, 0.0f), Vector2(101.0f, 169.0f), 3);

		// NormalRun
		at->Create(L"Run_Normal_R", NormalRunR, Vector2(0.0f, 0.0f), Vector2(135.0f, 162.0f), 16, 0.07f);
		at->Create(L"Run_Normal_L", NormalRunL, Vector2(0.0f, 0.0f), Vector2(135.0f, 162.0f), 16, 0.07f);

		// ShootingRun
		at->Create(L"Run_Shooting_R", ShootingRunR, Vector2(0.0f, 0.0f), Vector2(144.0f, 157.0f), 16, 0.07f);
		at->Create(L"Run_Shooting_L", ShootingRunL, Vector2(0.0f, 0.0f), Vector2(144.0f, 157.0f), 16, 0.07f);

		// 실행
		at->PlayAnimation(L"Idle_Enter_R", true);
		// 그외
	}

	void PlayerBossScript::Update()
	{
		// 방향체크
		if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::RIGHT))
		{
			dirR = true;
		}
		else if (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKey(eKeyCode::LEFT))
		{
			dirR = false;
		}

		pos = tr->GetPosition();

		if (mBullet != nullptr)
		{
			mBulletTime += 1.0f * Time::DeltaTime();

			if (mBulletTime >= 0.5f)
			{
				mBulletTime = 0.0f;
				// object::Destroy(mBullet);
				SetBullet(nullptr);
				SetBulletScript(nullptr);
			}
		}

		switch (pState)
		{
			// case dh::PlayerOverWorldScript::PlayerState::Idle:
			// 	break;
		case PlayerState::Idle:
			Idle();
			break;
		case PlayerState::Move:
			Move();
			break;
		case PlayerState::Enter:
			Enter();
			break;
		case PlayerState::Jump:
			Jump();
			break;
		case PlayerState::Shoot:
			Shoot();
			break;
		case PlayerState::MovingShoot:
			MovingShoot();
			break;
		case PlayerState::UpDown:
			UpDown();
			break;
		case PlayerState::Dash:
			Dash();
			break;
		case PlayerState::Ghost:
			Ghost();
			break;
		case PlayerState::Hit:
			Hit();
			break;
		default:
			break;
		}

		if (pState == PlayerState::Shoot)
		{
			if (bulletCoolDown == false)
			{
				CreateBullet();
				bulletCoolDown = true;
			}
			if (bulletCoolDown == true)
			{
				mBulletAttackCool += 2.0f * Time::DeltaTime();
				
				if (mBulletAttackCool >= 0.5f)
				{
					bulletCoolDown = false;
					mBulletAttackCool = 0.0f;
				}
			}
		}
		
		if (VelocityGetSwitch == true)
		{
			getVelocityCount += 2.0f * Time::DeltaTime();
		}

	}
	void PlayerBossScript::Complete()
	{
		int a = 0;
	}
	void PlayerBossScript::OnCollisionEnter(Collider2D* other)
	{
		if (other->GetOwner()->GetName() == L"Ground")
		{
			mRigidbody->SetGround(true);
			mRigidbody->SetVelocity(Vector2::Zero);
		}

		if (other->GetOwner()->GetName() == L"Platform1" && getVelocityCount >= 1.5f)
		{
			mRigidbody->SetGround(true);
			mRigidbody->SetVelocity(Vector2::Zero);
			VelocityGetSwitch = false;
			getVelocityCount = 0.0f;

		}
	}

	void PlayerBossScript::OnCollisionStay(Collider2D* other)
	{
	}

	void PlayerBossScript::OnCollisionExit(Collider2D* other)
	{
		if (other->GetOwner()->GetName() == L"Ground")
		{
			getVelocityCount = 0.5f;
			VelocityGetSwitch = true;
			mRigidbody->SetGround(false);
		}

		if (other->GetOwner()->GetName() == L"Platform1")
		{
			VelocityGetSwitch = true;
			mRigidbody->SetGround(false);
		}
	}

	void PlayerBossScript::Idle()
	{
		if (Input::GetKey(eKeyCode::LEFT))
		{
			// dirR = false;
			pState = PlayerState::Move;
			at->PlayAnimation(L"Run_Normal_L", true);
		}
		else if (Input::GetKey(eKeyCode::RIGHT) && !(Input::GetKey(eKeyCode::X)))
		{
			// dirR = true;
			pState = PlayerState::Move;
			at->PlayAnimation(L"Run_Normal_R", true);
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
				Vector2 velocity = mRigidbody->GetVelocity();
				velocity.y += 6.0f;
				mRigidbody->SetVelocity(velocity);
				mRigidbody->SetGround(false);

				if (dirR == true)
				{
					at->PlayAnimation(L"Jump_Normal_R", true);
					pState = PlayerState::Jump;
				}
				else if (dirR == false)
				{
					at->PlayAnimation(L"Jump_Normal_L", true);
					pState = PlayerState::Jump;
				}
		}
		// Attack
		if (Input::GetKey(eKeyCode::X) && dirR == true)
		{
			pState = PlayerState::Shoot;
			at->PlayAnimation(L"Idle_Shoot_R", true);
		}
		else if (Input::GetKey(eKeyCode::X) && dirR == false)
		{
			if (mBullet == nullptr)
				CreateBullet();

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
			// dirR = true;
		}
		// Hit
		if (Input::GetKeyUp(eKeyCode::H))
		{
			pState = PlayerState::Hit;
			at->PlayAnimation(L"Hit_Air", false);
			// dirR = true;
		}

		// 필살기 V
	}

	void PlayerBossScript::Move()
	{
		// 이동사격 진입
		if (Input::GetKey(eKeyCode::X) && dirR == true) // DIR체크
		{
			// pos.x -= 2.0f * Time::DeltaTime();
			// tr->SetPosition(pos);
			pState = PlayerState::MovingShoot;
			at->PlayAnimation(L"Run_Shooting_R", true);
		}
		else if (Input::GetKey(eKeyCode::X) && dirR == false) // DIR체크
		{
			// pos.x -= 2.0f * Time::DeltaTime();
			// tr->SetPosition(pos);
			pState = PlayerState::MovingShoot;
			at->PlayAnimation(L"Run_Shooting_L", true);
		}

		// 중력체크
		{
			// pos = tr->GetPosition();
			// tr->SetPosition(pos);
		}
		
		// Jump
		if (Input::GetKeyDown(eKeyCode::Z))
		{
			Vector2 velocity = mRigidbody->GetVelocity();

			if (dirR == true)
			{
				velocity.y += 6.0f;
				// velocity.x += 2.0f;
				mRigidbody->SetVelocity(velocity);
				mRigidbody->SetGround(false);

				at->PlayAnimation(L"Jump_Normal_R", true);
				pState = PlayerState::Jump;
			}
			else if (dirR == false)
			{
				velocity.y += 6.0f;
				// velocity.x -= 2.0f;
				mRigidbody->SetVelocity(velocity);
				mRigidbody->SetGround(false);

				at->PlayAnimation(L"Jump_Normal_L", true);
				pState = PlayerState::Jump;
			}
		}
		
		if (Input::GetKeyUp(eKeyCode::LEFT))
		{
			pState = PlayerState::Idle;
			at->PlayAnimation(L"Idle_Enter_L", true);
			// dirR = false;
		}
		else if (Input::GetKeyUp(eKeyCode::RIGHT))
		{
			pState = PlayerState::Idle;
			at->PlayAnimation(L"Idle_Enter_R", true);
			// dirR = true;
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
			pos.x -= 2.5f * Time::DeltaTime();
			tr->SetPosition(pos);
			// dirR = false;
		}
		else if (Input::GetKey(eKeyCode::RIGHT))
		{
			pos.x += 2.5f * Time::DeltaTime();
			tr->SetPosition(pos);
			// dirR = true;
		}

		tr->SetPosition(pos);
	}

	void PlayerBossScript::Enter()
	{
		
	}

	void PlayerBossScript::Aiming()
	{
	}

	void PlayerBossScript::Shoot()
	{
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			// dirR = true;
		}
		else if (Input::GetKey(eKeyCode::LEFT))
		{
			// dirR = false;
		}

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

		// Jump
		if (Input::GetKeyDown(eKeyCode::Z))
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y += 2.3f;
			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);

			if (dirR == true)
			{
				pState = PlayerState::Jump;
				at->PlayAnimation(L"Jump_Normal_R", true);
			}
			else if (dirR == false)
			{
				pState = PlayerState::Jump;
				at->PlayAnimation(L"Jump_Normal_L", true);
			}
		}

	}

	void PlayerBossScript::MovingShoot()
	{
		if (Input::GetKey(eKeyCode::LEFT))
		{
			pos.x -= 2.5f * Time::DeltaTime();
			tr->SetPosition(pos);
			dirR = false;
		}
		else if (Input::GetKey(eKeyCode::RIGHT))
		{
			pos.x += 2.5f * Time::DeltaTime();
			tr->SetPosition(pos);
			dirR = true;
		}

		// Jump
		if (Input::GetKeyDown(eKeyCode::Z))
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y += 2.3f;
			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);

			if (dirR == true)
			{
				pState = PlayerState::Jump;
				at->PlayAnimation(L"Jump_Normal_R", true);
			}
			else if (dirR == false)
			{
				pState = PlayerState::Jump;
				at->PlayAnimation(L"Jump_Normal_L", true);
			}
		}


		// 이동사격 탈출 (X키 땜)
		if (Input::GetKeyUp(eKeyCode::X) && dirR == false)// (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::Pressed)) // DIR체크
		{
			pState = PlayerState::Move;
			at->PlayAnimation(L"Run_Normal_L", true);
		}
		// 이동사격 탈출 (X키 땜)
		else if (Input::GetKeyUp(eKeyCode::X) && dirR == true) // DIR체크
		{
			pState = PlayerState::Move;
			at->PlayAnimation(L"Run_Normal_R", true);
		}

		// 이동사격 탈출 (오른쪽키 땜)
		else if (Input::GetKeyUp(eKeyCode::RIGHT) && dirR == true) // && (Input::GetKeyState(eKeyCode::X) == eKeyState::Pressed)) // DIR체크
		{
			pState = PlayerState::Shoot;
			at->PlayAnimation(L"Idle_Shoot_R", true);
		}
		else if (Input::GetKeyUp(eKeyCode::LEFT) && dirR == false) // && (Input::GetKeyState(eKeyCode::X) == eKeyState::Pressed)) // DIR체크
		{
			pState = PlayerState::Shoot;
			at->PlayAnimation(L"Idle_Shoot_L", true);
		}
	}

	void PlayerBossScript::UpDown()
	{
		if (Input::GetKey(eKeyCode::LEFT))
		{
			// dirR = false;
		}
		else if (Input::GetKey(eKeyCode::RIGHT))
		{
			// dirR = true;
		}

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
		Vector2 velocity = mRigidbody->GetVelocity();
		if (Input::GetKey(eKeyCode::LEFT))
			velocity.x -= 0.03f;

		if (Input::GetKey(eKeyCode::RIGHT))
			velocity.x += 0.03f;

		if (velocity.x > 1.8f)
			velocity.x = 1.8f;

		if (velocity.x < -1.8f)
			velocity.x = -1.8f;

		mRigidbody->SetVelocity(velocity);

		if (mRigidbody->GetGround() == true)
		{
			// mRigidbody->SetVelocity(Vector2::Zero);
			// mRigidbody->SetGround(true);
			pState = PlayerState::Idle;
			if (dirR == 0)
			{
				at->PlayAnimation(L"Idle_Enter_L", true);
			}
			if (dirR == 1)
			{
				at->PlayAnimation(L"Idle_Enter_R", true);
			}
		}
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

	void PlayerBossScript::CreateBullet()
	{
		// xbulletCoolDown = true;

		Vector3 posBullet = tr->GetPosition();

		// int a = rand() % 101;

		GameObject* pBullet
			= object::Instantiate<GameObject>(Vector3(posBullet.x + 0.5f, posBullet.y, 1.0004f), eLayerType::PlayerBullet);

		SetBullet(pBullet);

		pBullet->SetName(L"playerBullet");


		MeshRenderer* mrBullet = pBullet->AddComponent<MeshRenderer>();
		mrBullet->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mrBullet->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
		pBullet->AddComponent<PlayerBullet>();

		// pBullet->GetComponent<Transform>()->SetScale(Vector3(1.0f, 1.0f, 1.0f));

		// Animator* bulletAt = pBullet->AddComponent<Animator>();

	}
	void PlayerBossScript::CreateBulletL()
	{
		/*
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		GameObject* Devide
			= object::Instantiate<GameObject>(Vector3(pos.x + 0.5f, pos.y + 0.2f, 1.0004f), eLayerType::Skill);

		SetDevide(Devide);

		Devide->SetName(L"Devide");


		MeshRenderer* mr = Devide->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		Devide->GetComponent<Transform>()->SetScale(Vector3(3.0f, 3.0f, 1.0005f));

		Animator* at = Devide->AddComponent<Animator>();
		Devide->AddComponent<SkillScript>();

		SkillScript* ss = Devide->GetComponent<SkillScript>();
		ss->SetDir(true);
		*/
	}
}
