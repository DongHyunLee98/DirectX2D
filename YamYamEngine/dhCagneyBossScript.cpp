#include "dhCagneyBossScript.h"
#include "dhCameraScript.h"
#include "dhTransform.h"
#include "dhGameObject.h"
#include "dhTime.h"
#include "dhInput.h"
#include "dhObject.h"
#include "dhResources.h"


namespace dh
{
	CagneyBossScript::CagneyBossScript()
		: enterWaitTimer(0.0f)
		, enterWaitSwitch(true)
		, enterIdleSwitch(false)
		, mHp(100.0f)
	{
	}
	CagneyBossScript::~CagneyBossScript()
	{
	}
	void CagneyBossScript::Initialize()
	{
		mTrans = this->GetOwner()->GetComponent<Transform>();
		mColl = this->GetOwner()->AddComponent<Collider2D>();
		mAnim = this->GetOwner()->AddComponent<Animator>();
		

		std::shared_ptr<Texture> animEnterWait = Resources::Load<Texture>(L"EnterAnimWait", L"..\\Resources\\Texture\\CagneyCarnation\\Enter\\EnterWait.png");
		std::shared_ptr<Texture> animEnter = Resources::Load<Texture>(L"EnterAnim", L"..\\Resources\\Texture\\CagneyCarnation\\Enter\\EnterAnim.png");
		std::shared_ptr<Texture> animIdle = Resources::Load<Texture>(L"IdleAnim", L"..\\Resources\\Texture\\CagneyCarnation\\Idle\\IdleAnim.png");
		
		// 府家胶 局聪皋捞记栏肺 积己
		mAnim->Create(L"EnterAnim", animEnter, Vector2(0.0f, 0.0f), Vector2(814.0f, 720.0f), 20, 0.08f);
		mAnim->Create(L"EnterAnimWait", animEnter, Vector2(0.0f, 0.0f), Vector2(814.0f, 720.0f), 2, 0.1f);
		mAnim->Create(L"IdleAnim", animIdle, Vector2(0.0f, 0.0f), Vector2(540.0f, 673.0f), 17, 0.07f);
		
		// 角青
		mAnim->PlayAnimation(L"EnterAnimWait", true);

		//mAnim->CreateAnimations(L"..\\Resources\\Texture\\CagneyCarnation\\Idle", Vector2::Zero, 0.1f);
		//mAnim->PlayAnimation(L"EnterAnimWait2", true);
		
		mState = CagneyState::EnterWait;
	}
	void CagneyBossScript::Update()
	{
		// Vector3 pos = tr->GetPosition();
		
		switch (mState)
		{
		case CagneyState::EnterWait:
			EnterWait();
			break;		
		case CagneyState::Enter:
			Enter();
			break;
		case CagneyState::Idle:
			Idle();
			break;
		case CagneyState::HeadLow:
			HeadLow();
			break;
		case CagneyState::HeadMiddle:
			HeadMiddle();
			break;
		case CagneyState::Seed:
			Seed();
			break;
		case CagneyState::TwoPhase:
			TwoPhase();
			break;
		case CagneyState::UpSeed:
			UpSeed();
			break;
		default:
			break;
		}
		
	}
	void CagneyBossScript::OnCollisionEnter(Collider2D* other)
	{
		if (other->GetOwner()->GetName() == L"playerBullet")
		{
			mHp -= 1.0f;
		}
	}
	void CagneyBossScript::OnCollisionStay(Collider2D* other)
	{
	}
	void CagneyBossScript::OnCollisionExit(Collider2D* other)
	{
	}
	void CagneyBossScript::EnterWait()
	{
		if (enterWaitSwitch)
			enterWaitTimer += Time::DeltaTime();

		if (enterWaitTimer >= 2.0f)
		{
			enterWaitSwitch = false;
			enterIdleSwitch = true;
			enterWaitTimer = 0.0f;
			mState = CagneyState::Enter;
			mAnim->PlayAnimation(L"EnterAnim", false);
		}
	}
	void CagneyBossScript::Enter()
	{
		if(enterIdleSwitch)
			enterWaitTimer += Time::DeltaTime();

		if (enterWaitTimer >= 1.5f)
		{
			enterIdleSwitch = false;
			enterWaitTimer = 0.0f;
			mTrans->SetPosition(Vector3(2.0f, 0.0f, 1.001f));
			mTrans->SetScale(Vector3(3.2f, 3.2f, 1.0f));
			mState = CagneyState::Idle;
			mAnim->PlayAnimation(L"IdleAnim", true);
		}
	}
	void CagneyBossScript::Idle()
	{

		if (mHp <= 98.0f)
		{
			int a = 0;
		}
	}
	void CagneyBossScript::HeadMiddle()
	{
	}
	void CagneyBossScript::HeadLow()
	{
	}
	void CagneyBossScript::Seed()
	{
	}
	void CagneyBossScript::TwoPhase()
	{
	}
	void CagneyBossScript::UpSeed()
	{
	}
	void CagneyBossScript::Dead()
	{
		/*
		GameObject* KnockOutObj = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 0.999f), eLayerType::BackGround);
		KnockOutObj->SetName(L"KnockOutObj");
		MeshRenderer* KnockOutMr = KnockOutObj->AddComponent<MeshRenderer>();
		KnockOutMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		KnockOutMr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
		Animator* KnockAnim = KnockOutObj->AddComponent<Animator>();

		std::shared_ptr<Texture> knockOutAnim = Resources::Load<Texture>(L"KnockoutAnim", L"..\\Resources\\Texture\\AKNOCKOUT\\KnockoutAnim.png");
		KnockAnim->Create(L"KnockoutAnim", knockOutAnim, Vector2(0.0f, 0.0f), Vector2(512.0f, 288.0f), 26, 0.07f);
		KnockAnim->PlayAnimation(L"KnockoutAnim", false);

		Transform* KnockOutTrans = KnockOutObj->GetComponent<Transform>();
		KnockOutTrans->SetScale(Vector3(8.0f, 4.5f, 1.0f));
		*/
	}
}
