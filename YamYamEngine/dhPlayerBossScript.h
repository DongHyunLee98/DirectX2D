#pragma once
#include <dhScript.h>
#include <dhAnimator.h>

namespace dh
{
	// class Rigidbody;
	class PlayerBossScript : public Script
	{
	public:
		enum class PlayerState
		{
			Idle,
			Move,
			Enter,
			Aiming,
			Shoot,
			MovingShoot,
			UpDown,
			Jump,
			Dash,
			Ghost,
			Hit,
			// Up,
			// Down,
			// Left,
			// Light,
		};

		PlayerBossScript();
		~PlayerBossScript();


		virtual void Initialize() override;
		virtual void Update() override;

		void Complete();

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;


		Transform* GetTransform() { return tr; }
		Animator* GetAnimator() { return at; }
		Collider2D* GetCollider() { return cd; }

		void SetAnimator(Animator* mAt) { at = mAt; }

		// void SetCenter(Vector2 size) { mCenter = size; }
		// UINT GetColliderID() { return mColliderID; }

	private:
		Animator* at;
		Transform* tr;
		Collider2D* cd;
		PlayerState pState;
		Vector3 pos;
		// Rigidbody* rigid;

		// VectorR velocity;
		bool dirR; // 1¿À¸¥ÂÊ 0¿ÞÂÊ ÃÊ±ê°ª 0(true)
		float jumpTime;
		float attackTime;
		float dashTime;
		bool jumpSwitch;

		float gravity = 2.0f;

	private:
		void Idle();
		void Move();
		void Enter();
		void Aiming();
		void Shoot();
		void MovingShoot();
		void UpDown();
		void Jump();
		void Dash();
		void Ghost();
		void Hit();
	};
}