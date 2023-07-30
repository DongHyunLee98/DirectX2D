#pragma once
//#include "yaScript.h"
#include <dhScript.h>
#include <dhAnimator.h>

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
		//virtual void OnCollisionStay(Collider2D* other) override;
		//virtual void OnCollisionExit(Collider2D* other) override;

	private:
		Animator* at;
		PlayerState pState;
		Transform* tr;
		Vector3 pos;

		bool dirR; // 1¿À¸¥ÂÊ 0¿ÞÂÊ ÃÊ±ê°ª 0(true)
		float jumpTime;
		float attackTime;
		float dashTime;

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