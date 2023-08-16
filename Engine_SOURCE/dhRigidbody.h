#pragma once
#include "dhComponent.h"

namespace dh
{
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		~Rigidbody();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetMass(float mass) { mMass = mass; }
		void AddForce(Vector3 force);
		void SetGround(bool ground) { mbGround = ground; }
		void SetVelocity(Vector3 velocity) { mVelocity = velocity; }
		Vector3 GetVelocity() { return mVelocity; }
		Vector3 GetForce() { return mForce; }

		bool GetGround() { return mbGround; }

		void ForceReset() { mForce = Vector3::Zero; }

	private:
		float mMass;
		Vector3 mForce;
		Vector3 mAccelation;
		Vector3 mVelocity;
		Vector3 mLimitedVelocity;

		Vector3 mGravity;
		float mFriction;
		bool mbGround;

		float mGravityAccel;
	};
}
