#pragma once
#include <dhScript.h>
#include <dhAnimation.h>
#include "dhPlayerBossScript.h"

namespace dh
{
	class GameObject;
	class PlayerBullet : public Script
	{
	public:
		PlayerBullet();
		~PlayerBullet();

		//enum class bulletState
		//{
		//	Bullet,
		//	LeftBullet,
		//};

		virtual void Initialize() override;
		virtual void Update() override;

		// void Complete();
		void SetDir(bool dir) { dirR = dir; }

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		// Transform* GetTransform() { return mTrans; }
		// void SetTransform(Transform* trans) { mTrans = trans; }
		// void SetPosition(Vector3 _pos) { pos = _pos; }

	public:
		Vector2 mDir;
		Vector2 mDestPos;
		Transform*mTrans;
		Collider2D* mColl;
		Vector3 playerPos;
		Vector3 mPos;
		Animator* mAnim;

	private:
		float mSpeed;
		bool dirR;
		PlayerBossScript* mPBS;
		
	private:
		//bulletState mBulletState;
	};
	
}