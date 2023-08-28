#include "dhCagneyBossScript.h"
#include "dhCameraScript.h"
#include "dhTransform.h"
#include "dhGameObject.h"
#include "dhTime.h"
#include "dhInput.h"
#include "dhObject.h"
#include "dhResources.h"
#include "dhMeshRenderer.h"
#include "dhVineOneScript.h"
#include "dhVineMainScript.h"
#include "dhBossOneScene.h"

namespace dh
{
	CagneyBossScript::CagneyBossScript()
		: enterWaitTimer(0.0f)
		, enterWaitSwitch(true)
		, enterIdleSwitch(false)
		, mHp(0.0f)
		, twoPhaseTime(0.0f)
		, twoPhaseSwitch(true)
		, patternCoolSwitch(false)
		, patternCoolTime(0.0f)
		, vineCreateSwitch(false)
		, vineCreateTime(0.0f)
		, KnockOutSwitch(false)
		, KnockOutTimer(0.0f)
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


		// Final Form
		std::shared_ptr<Texture> finalFormEnter1 = Resources::Load<Texture>(L"FinalFormEnterAnim1", L"..\\Resources\\Texture\\CagneyCarnation\\FinalFormIntro\\FinalFormEnter1.png");
		std::shared_ptr<Texture> finalFormEnter2 = Resources::Load<Texture>(L"FinalFormEnterAnim2", L"..\\Resources\\Texture\\CagneyCarnation\\FinalFormIntro\\FinalFormEnter2.png");
		std::shared_ptr<Texture> finalFormIdle = Resources::Load<Texture>(L"FinalFormIdleAnim", L"..\\Resources\\Texture\\CagneyCarnation\\FinalForm\\FinalIdleAnim.png");

		std::shared_ptr<Texture> deadAnim = Resources::Load<Texture>(L"DeadAnim", L"..\\Resources\\Texture\\CagneyCarnation\\Dead\\DeadAnim.png");
		
		// 府家胶 局聪皋捞记栏肺 积己
		mAnim->Create(L"EnterAnim", animEnter, Vector2(0.0f, 0.0f), Vector2(814.0f, 720.0f), 20, 0.08f);
		mAnim->Create(L"EnterAnimWait", animEnter, Vector2(0.0f, 0.0f), Vector2(814.0f, 720.0f), 2, 0.1f);
		mAnim->Create(L"IdleAnim", animIdle, Vector2(0.0f, 0.0f), Vector2(540.0f, 673.0f), 17, 0.07f);
		
		mAnim->Create(L"FinalFormEnterAnim1", finalFormEnter1, Vector2(0.0f, 0.0f), Vector2(660.0f, 660.0f), 18, 0.1f);
		mAnim->Create(L"FinalFormEnterAnim2", finalFormEnter2, Vector2(0.0f, 0.0f), Vector2(660.0f, 660.0f), 10, 0.1f);
		mAnim->Create(L"FinalFormIdleAnim", finalFormIdle, Vector2(0.0f, 0.0f), Vector2(514.0f, 706.0f), 18, 0.07f);

		mAnim->Create(L"DeadAnim", deadAnim, Vector2(0.0f, 0.0f), Vector2(491.0f, 634.0f), 12, 0.07f);

		// 角青
		mAnim->PlayAnimation(L"EnterAnimWait", true);
		// mAnim->PlayAnimation(L"DeadAnim", true);

		//mAnim->CreateAnimations(L"..\\Resources\\Texture\\CagneyCarnation\\Idle", Vector2::Zero, 0.1f);
		//mAnim->PlayAnimation(L"EnterAnimWait2", true);
		
		mState = CagneyState::EnterWait;
		mHp = 30.0f;

		if(mKnockOutObject != nullptr)
			mKnockOutObject = nullptr;
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
		case CagneyState::TwoPhaseEnter1:
			TwoPhaseEnter1();
			break;
		case CagneyState::TwoPhaseEnter2:
			TwoPhaseEnter2();
			break;
		case CagneyState::TwoPhaseIdle:
			TwoPhaseIdle();
			break;
		case CagneyState::UpSeed:
			UpSeed();
			break;
		default:
			break;
		}
		
		if (KnockOutSwitch == true)
		{
			KnockOutTimer += 1.0f * Time::DeltaTime();
		}
		if (KnockOutTimer >= 1.95f)
		{
			object::Destroy(mKnockOutObject);
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
			mTrans->SetScale(Vector3(4.0f, 4.0f, 1.0f));
			mColl->SetCenter(Vector2(0.0f, 0.5f));
			mState = CagneyState::Idle;
			mAnim->PlayAnimation(L"IdleAnim", true);
		}
	}
	void CagneyBossScript::Idle()
	{

		if (mHp <= 15.0f)
		{
			mState = CagneyState::TwoPhaseEnter1;
			mAnim->PlayAnimation(L"FinalFormEnterAnim1", false);
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
	void CagneyBossScript::TwoPhaseEnter1()
	{
		if (twoPhaseSwitch == true)
			twoPhaseTime += Time::DeltaTime();

		if (twoPhaseTime >= 1.8f)
		{
			twoPhaseSwitch = false;
			twoPhaseTime = 0.0f;
			mTrans->SetPosition(Vector3(2.3f, 0.0f, 1.001f));
			mTrans->SetScale(Vector3(3.6f, 3.4f, 1.0f));

			CreateVine1();

			mState = CagneyState::TwoPhaseEnter2;
			mAnim->PlayAnimation(L"FinalFormEnterAnim2", false);
		}
	}
	void CagneyBossScript::TwoPhaseEnter2()
	{
		mTrans->SetPosition(Vector3(2.0f, 0.0f, 1.001f));
		mTrans->SetScale(Vector3(3.6f, 3.4f, 1.0f));

		if (twoPhaseSwitch == false)
			twoPhaseTime += Time::DeltaTime();

		if (twoPhaseTime >= 1.0f)
		{
			twoPhaseSwitch = true;
			twoPhaseTime = 0.0f;

			CreateVine();

			mTrans->SetPosition(Vector3(2.5f, -0.1f, 1.001f));
			mTrans->SetScale(Vector3(4.0f, 4.0f, 1.0f));
			mColl->SetCenter(Vector2(0.0f, 0.5f));
			mState = CagneyState::TwoPhaseIdle;
			mAnim->PlayAnimation(L"FinalFormIdleAnim", true);
		}
	}
	void CagneyBossScript::TwoPhaseIdle()
	{
		if (patternCoolSwitch == false)
			patternCoolTime += 1.0f * Time::DeltaTime();

		if (patternCoolTime >= 3.0f)
		{
			// mState = CagneyState::TwoPhaseShoot;
			// mAnim->PlayAnimation(L"FinalFormShoot", false);
		}

		if (mHp <= 0.0f)
		{
			if (mKnockOutObject == nullptr)
				KnockOut();

			mTrans->SetPosition(Vector3(2.5f, -0.4f, 1.001f));
			mTrans->SetScale(Vector3(3.5f, 3.5f, 1.0f));
			mColl->SetCenter(Vector2(0.0f, 0.5f));
			mState = CagneyState::Dead;
			mAnim->PlayAnimation(L"DeadAnim", true);
		}

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

	void CagneyBossScript::CreateVine1()
	{
		GameObject* vineOne
			= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.001f), eLayerType::MonsterBullet);
		vineOne->SetName(L"vineOne");
		vineOne->AddComponent<VineOneScript>();
		MeshRenderer* mrVineOne = vineOne->AddComponent<MeshRenderer>();
		mrVineOne->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mrVineOne->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

	}
	void CagneyBossScript::CreateVine()
	{
		GameObject* vineMain
			= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.001f), eLayerType::MonsterBullet);
		vineMain->SetName(L"vineMain");
		vineMain->AddComponent<VineMainScript>();
		MeshRenderer* mrVineMain = vineMain->AddComponent<MeshRenderer>();
		mrVineMain->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mrVineMain->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

	}

	void CagneyBossScript::KnockOut()
	{
		KnockOutSwitch = true;

		mKnockOutObject = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 0.999f), eLayerType::BackGround);
		mKnockOutObject->SetName(L"KnockOutObj");
		MeshRenderer* mrKnockOut = mKnockOutObject->AddComponent<MeshRenderer>();
		mrKnockOut->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mrKnockOut->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
		Animator* mKnockOutAnim = mKnockOutObject->AddComponent<Animator>();

		std::shared_ptr<Texture> knockOutAnim = Resources::Load<Texture>(L"KnockOutAnim", L"..\\Resources\\Texture\\AKNOCKOUT\\KnockOutAnim.png");
		mKnockOutAnim->Create(L"KnockOutAnim", knockOutAnim, Vector2(0.0f, 0.0f), Vector2(512.0f, 288.0f), 27, 0.07f);
		mKnockOutAnim->PlayAnimation(L"KnockOutAnim", false);

		Transform* KnockOutTrans = mKnockOutObject->GetComponent<Transform>();
		KnockOutTrans->SetScale(Vector3(10.0f, 4.5f, 1.0f));
		
	}
}
