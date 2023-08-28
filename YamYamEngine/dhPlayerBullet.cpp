#include "dhPlayerBullet.h"
#include "dhTime.h"
#include "dhInput.h"
#include "dhTransform.h"
#include "dhCollider2D.h"
#include "dhGameObject.h"
#include "dhObject.h"
#include "dhAnimator.h"
#include "dhPlayerBossScript.h"
#include "dhResources.h"

#include "dhCameraScript.h"

namespace dh
{
	
	PlayerBullet::PlayerBullet()
		: mSpeed(0.0f)
	{
	}
	PlayerBullet::~PlayerBullet()
	{
	}

	void PlayerBullet::Initialize()
	{
		mColl = GetOwner()->AddComponent<Collider2D>();
		mColl->SetSize(Vector2(0.4f, 0.2f));
		mColl->SetCenter(Vector2(0.1f, 0.0f));

		mTrans = GetOwner()->GetComponent<Transform>();

		mAnim = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Texture> animBullet = Resources::Load<Texture>(L"animBulletName", L"..\\Resources\\Texture\\Bullet\\BulletOriginalAnim.png");
		mAnim->Create(L"animBulletName", animBullet, Vector2(0.0f, 0.0f), Vector2(124.0f, 44.0f), 8, 0.08f);
		mAnim->PlayAnimation(L"animBulletName", false);

		mPos = mTrans->GetPosition();

	}
	void PlayerBullet::Update()
	{
		if (mBullet != nullptr)
		{
			mBullet = this->GetOwner();
		}
		if (mPlayerBullet != nullptr)
		{
			mPlayerBullet = this->GetOwner()->AddComponent< PlayerBullet>();
		}

		mPos.x += 4.5f * Time::DeltaTime();
		mTrans->SetPosition(mPos);


	}

	void PlayerBullet::OnCollisionEnter(Collider2D* other)
	{
		if (other->GetOwner()->GetName() == L"bulletDestroy")
		{
			SetBullet(nullptr);
			SetBulletScript(nullptr);
			// object::Destroy(mBullet);
		}
	}

	void PlayerBullet::OnCollisionStay(Collider2D* other)
	{
	}

	void PlayerBullet::OnCollisionExit(Collider2D* other)
	{
	}
}
