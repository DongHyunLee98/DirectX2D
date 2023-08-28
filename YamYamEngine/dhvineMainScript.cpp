#include "dhVineMainScript.h"
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
	VineMainScript::VineMainScript()
	{
	}

	VineMainScript::~VineMainScript()
	{
	}

	void VineMainScript::Initialize()
	{
		mColl = GetOwner()->AddComponent<Collider2D>();
		mColl->SetSize(Vector2(1.0f, 0.5f));
		mColl->SetCenter(Vector2(0.0f, -0.1f));

		mTrans = GetOwner()->GetComponent<Transform>();
		mTrans->SetScale(Vector3(6.0f, 1.0f, 1.0f));
		mTrans->SetPosition(Vector3(-1.59f, -1.13f, 1.001f));

		mAnim = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Texture> VineUpAnimMain = Resources::Load<Texture>(L"vineUpAnimMain", L"..\\Resources\\Texture\\CagneyCarnation\\Vine2\\VineUp2Anim.png");
		mAnim->Create(L"vineUpAnimMain", VineUpAnimMain, Vector2(0.0f, 0.0f), Vector2(946.0f, 200.0f), 13, 0.08f);
		mAnim->PlayAnimation(L"vineUpAnimMain", false);
	}

	void VineMainScript::Update()
	{

	}

	void VineMainScript::OnCollisionEnter(Collider2D* other)
	{
	}
	void VineMainScript::OnCollisionStay(Collider2D* other)
	{
	}
}