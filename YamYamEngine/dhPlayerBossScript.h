#pragma once
#include <dhScript.h>
#include "dhAnimator.h"
// #include "dhRigidbody.h"

namespace dh
{
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

		void ChangeState(PlayerState state) { mCurState = state; }

		void SetAnimator(Animator* mAt) { at = mAt; }

		// void SetCenter(Vector2 size) { mCenter = size; }
		// UINT GetColliderID() { return mColliderID; }
		bool GetDir() { return dirR; }

		Vector3 GetPosition() { return pos; }

	private:
		Animator* at;
		Transform* tr;
		Collider2D* cd;
		PlayerState pState;
		Vector3 pos;
		// Rigidbody* mRigidbody;

		PlayerState mCurState;

		bool dirR; // 1¿À¸¥ÂÊ 0¿ÞÂÊ ÃÊ±ê°ª 0(true)
		// VectorR velocity;

		bool jumpState;
		bool jumpTimeCheck;
		float jumpTime;
		
		float attackTime;

		float dashTime;

		float gravity;
		Vector3 bulletPos;

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