#pragma once
//#include "yaScript.h"
#include <dhScript.h>
#include <dhAnimator.h>

namespace dh
{
	class PlayerWorldScript : public Script
	{
	public:
		enum class PlayerState
		{
			Idle,
			Move,
			Enter,
			// Up,
			// Down,
			// Left,
			// Light,
		};

		PlayerWorldScript();
		~PlayerWorldScript();


		virtual void Initialize() override;
		virtual void Update() override;

		void Complete();

		//virtual void OnCollisionEnter(Collider2D* other) override;
		//virtual void OnCollisionStay(Collider2D* other) override;
		//virtual void OnCollisionExit(Collider2D* other) override;

	private:
		Animator* at;
		PlayerState pState;
		Transform* tr;
		Vector3 pos;

		bool dirR; // 1¿À¸¥ÂÊ 0¿ÞÂÊ ÃÊ±ê°ª 0(true)

	private:
		void Idle();
		void Move();
		void Enter();
	};
}