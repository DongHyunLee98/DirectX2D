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
		void SetSize(Vector2 size) { mSize = size; } // 충돌체 크기 임의로 조정
		void SetCenter(Vector2 size) { mCenter = size; } // 센터 값 오류
		UINT GetColliderID() { return mColliderID; }

	private:
		static UINT mColliderNumber;
		UINT mColliderID;
		eColliderType mType;
		Transform* mTransform;

		// 충돌체의 최종 위치를 따로 저장해두는 멤버
		Vector3 mPosition;
		Vector2 mSize;
		Vector2 mCenter;
		int mCollCheck = 0;
	};
}
