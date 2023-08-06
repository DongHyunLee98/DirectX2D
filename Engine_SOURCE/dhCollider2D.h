#pragma once
#include "dhComponent.h"
#include "dhTransform.h"


namespace dh
{
	class Collider2D : public Component
	{
	public:
		Collider2D();
		~Collider2D();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void OnCollisionEnter(Collider2D* other);
		void OnCollisionStay(Collider2D* other);
		void OnCollisionExit(Collider2D* other);

		void SetType(eColliderType type) { mType = type; }
		Vector2 GetSize() { return mSize; }
		void SetSize(Vector2 size) { mSize = size; }
		void SetCenter(Vector2 size) { mCenter = size; }
		UINT GetColliderID() { return mColliderID; }

		// RigidBody 정보를 얻기위함
		eColliderOwner GetColliderOwner() { return mColliderOwner; }
		void SetColliderOwner(eColliderOwner colOwner) { mColliderOwner = colOwner; }

	private:
		static UINT mColliderNumber;
		UINT mColliderID;
		eColliderType mType;
		Transform* mTransform;

		// Rigid정보 얻기위함
		eColliderOwner mColliderOwner;

		Vector3 mPosition;
		Vector2 mSize;
		Vector2 mCenter;


		bool mGrounded;
	};
}
