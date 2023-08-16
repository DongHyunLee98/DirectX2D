#pragma once
#include "dhPlayerBossScript.h"

namespace dh
{
	class GameObject;
	class PlayerBullet : public Script
	{
	public:
		PlayerBullet();
		~PlayerBullet();

		virtual void Initialize();
		virtual void Update();

		Transform* GetTransform() { return mTrans; }
		void SetTransform(Transform* trans) { mTrans = trans; }
		void SetPosition(Vector3 _pos) { pos = _pos; }

	public:
		Vector2 mDir;
		Vector2 mDestPos;
		Vector3 pos;
		Transform*mTrans;
		Vector3 playerPos;

	private:
		float mSpeed;
		float mAliveTime;
		PlayerBossScript* mPBS;
		
	};
	
}