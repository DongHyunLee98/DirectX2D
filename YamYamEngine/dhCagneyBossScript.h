#pragma once
#include <dhScript.h>
#include "dhAnimator.h"

namespace dh
{
	class CagneyBossScript : public Script
	{
	public:
		enum class CagneyState
		{
			EnterWait,
			Enter,
			Idle,
			HeadLow,
			HeadMiddle,
			Seed,
			TwoPhaseEnter1,
			TwoPhaseEnter2,
			TwoPhaseIdle,
			UpSeed,
			Dead,
		};

		CagneyBossScript();
		~CagneyBossScript();

		virtual void Initialize() override;
		virtual void Update() override;	

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		Transform* GetTransform() { return mTrans; }
		Animator* GetAnimator() { return mAnim; }
		Collider2D* GetCollider() { return mColl; }

		void ChangeState(CagneyState state) { mCurState = state; }
		void SetAnimator(Animator* at) { mAnim = at; }

		void CreateVine1();
		void CreateVine();
		void KnockOut();

	private:
		Animator* mAnim;
		Transform* mTrans;
		Collider2D* mColl;
		CagneyState mState;
		Vector3 pos;

		CagneyState mCurState;
		float patternTime;
		
		float mHp;

	private:
		float enterWaitTimer;
		bool enterWaitSwitch;
		bool enterIdleSwitch;

		float twoPhaseTime;
		bool twoPhaseSwitch;

		float patternCoolTime;
		bool patternCoolSwitch;

		float vineCreateTime;
		bool vineCreateSwitch;

		bool KnockOutSwitch;
		float KnockOutTimer;
		GameObject* mKnockOutObject;

	private:
		void EnterWait();
		void Enter();
		void Idle();
		void HeadMiddle();
		void HeadLow();
		void Seed();
		void TwoPhaseEnter1();
		void TwoPhaseEnter2();
		void TwoPhaseIdle();
		void UpSeed();
		void Dead();
	};
}