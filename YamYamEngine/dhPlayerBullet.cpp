#include "dhPlayerBullet.h"
#include "dhTime.h"
#include "dhTransform.h"
#include "dhCollider2D.h"
#include "dhGameObject.h"
#include "dhObject.h"
#include "dhAnimator.h"
#include "dhPlayerBossScript.h"

namespace dh
{
	
	PlayerBullet::PlayerBullet()
		: mSpeed(2.0f)
		, mAliveTime(5.0f)
	{
	}
	PlayerBullet::~PlayerBullet()
	{
	}
	void PlayerBullet::Initialize()
	{
		Collider2D* mColl = this->GetOwner()->AddComponent<Collider2D>();
		mColl->SetSize(Vector2(0.5f, 0.5f));
		mTrans = GetOwner()->GetComponent<Transform>();
		

		// PlayerBossScript* playerObj = GetOwner()->AddComponent<PlayerBossScript>();
		// pos = playerObj->GetPosition();
		// player->GetComponent<Transform>()->SetPosition(Vector3(-2.0f, 0.0f, 1.0001f));
		// this->GetOwner()->SetState(eState::Active);
	}
	void PlayerBullet::Update()
	{
		// mAliveTime -= Time::DeltaTime();
		//if (mAliveTime <= 0.0f)
		//{
		//	
		//}
		// pos = playerPos;
		// playerPos = playerObj->GetPosition();
		pos.x += 10.0f * Time::DeltaTime();
		mTrans->SetPosition(pos);
	
		//else if (mDir = false)
		//{
		//	pos.x -= 100.0f * Time::DeltaTime();
		//}
		
	}
	
}
