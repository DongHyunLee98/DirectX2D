#include "dhVineOneScript.h"
#include "dhTime.h"
#include "dhInput.h"
#include "dhTransform.h"
#include "dhCollider2D.h"
#include "dhGameObject.h"
#include "dhObject.h"
#include "dhAnimator.h"
#include "dhResources.h"

#include "dhCameraScript.h"

namespace dh
{
	VineOneScript::VineOneScript()
		: vineOneDeleteSwitch(false)
		, vineOneDeleteTime(0.0f)
	{
	}

	VineOneScript::~VineOneScript()
	{
	}

	void VineOneScript::Initialize()
	{
		mObject = this->GetOwner();

		mColl = GetOwner()->AddComponent<Collider2D>();
		mColl->SetSize(Vector2(1.0f, 0.5f));
		mColl->SetCenter(Vector2(0.0f, 0.0f));

		mTrans = GetOwner()->GetComponent<Transform>();
		mTrans->SetScale(Vector3(4.5f, 1.0f, 1.0f));
		mTrans->SetPosition(Vector3(-0.85f, -1.1f, 1.001f));

		mAnim = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Texture> VineUpAnim1 = Resources::Load<Texture>(L"vineUpAnim1", L"..\\Resources\\Texture\\CagneyCarnation\\Vine1\\VineUp1Anim.png");
		mAnim->Create(L"vineUpAnim1", VineUpAnim1, Vector2(0.0f, 0.0f), Vector2(635.0f, 221.0f), 10, 0.1f);
		mAnim->PlayAnimation(L"vineUpAnim1", false);
	}

	void VineOneScript::Update()
	{
		if (vineOneDeleteSwitch == false)
			vineOneDeleteTime += 1.0f * Time::DeltaTime();

		if (vineOneDeleteTime > 1.01f)
		{
			object::Destroy(mObject);
		}

	}

	void VineOneScript::OnCollisionEnter(Collider2D* other)
	{
	}
	void VineOneScript::OnCollisionStay(Collider2D* other)
	{
	}
}