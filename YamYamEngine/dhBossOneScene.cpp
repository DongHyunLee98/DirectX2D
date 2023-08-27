#include "dhBossOneScene.h"
#include "dhTransform.h"
#include "dhMeshRenderer.h"
#include "dhResources.h"
#include "dhMesh.h"
#include "dhCameraScript.h"
#include "dhCamera.h"
#include "dhSceneManager.h"
#include "dhInput.h"
#include "dhGridScript.h"
#include "dhObject.h"
#include "dhRenderer.h"
#include "dhCollider2D.h"
#include "dhPlayerScript.h"
#include "dhCollisionManager.h"
#include "dhAnimator.h"

#include "dhPlayerBossScript.h"
#include "dhCagneyBossScript.h"

#include "dhPaintShader.h"
#include "dhConstantBuffer.h"
#include "dhParticleSystem.h"

#include "dhGroundScript.h"
#include "dhPlayer.h"

#include "dhAudioListener.h"
#include "dhAudioClip.h"
#include "dhAudioSource.h"

#include "dhTime.h"

namespace dh
{
	BossOneScene::BossOneScene()
		: EnterCheckTime(0.0f)
		, EnterCheck(false)
	{
	}
	BossOneScene::~BossOneScene()
	{
	}
	void BossOneScene::Initialize()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::PlayerBullet, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::PlayerBullet, eLayerType::Wall, true);

		// CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);

		//std::shared_ptr<PaintShader> paintShader = Resources::Find<PaintShader>(L"PaintShader");
		//std::shared_ptr<Texture> paintTexture = Resources::Find<Texture>(L"PaintTexuture");
		//paintShader->SetTarget(paintTexture);
		//paintShader->OnExcute();

		//// 변경된 Smile(페인트텍스쳐)
		//{
		//	GameObject* paint = new GameObject();
		//	paint->SetName(L"paint");
		//	AddGameObject(eLayerType::Monster, paint);
		//	MeshRenderer* paintMr = paint->AddComponent<MeshRenderer>();
		//	paintMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//	paintMr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial02"));
		//	paint->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 1.0f, 1.0f));
		//	Collider2D* cd = paint->AddComponent<Collider2D>();
		//}	
		// Particle
		{
			GameObject* particleObj = new GameObject();
			particleObj->SetName(L"Particle");
			AddGameObject(eLayerType::BackGround, particleObj);
			ParticleSystem* mr = particleObj->AddComponent<ParticleSystem>();
			particleObj->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.0f));
			particleObj->GetComponent<Transform>()->SetScale(Vector3(0.2f, 0.2f, 0.2f));
		}
		// Player
		{
			
			Player* player = object::Instantiate<Player>(Vector3(-2.5f, 6.0f, 1.0001f), eLayerType::Player);

			player->SetName(L"Player_Boss");
			MeshRenderer* playerMr = player->AddComponent<MeshRenderer>();
			playerMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			playerMr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

			
			// Animator* at = player->AddComponent<Animator>();
			PlayerBossScript* pBossScript = player->AddComponent<PlayerBossScript>();
			// Animator* mAt = player->AddComponent<Animator>();
			// pBossScript->SetAnimator(at);
			pBossScript->GetAnimator();

			Collider2D* playerCd = pBossScript->GetCollider();
			playerCd->SetSize(Vector2(0.4f, 0.5f));
			playerCd->SetCenter(Vector2(0.0f, 0.0f));
			Transform* playerTr = pBossScript->GetTransform();
			playerTr->SetScale(Vector3(1.3f, 1.3f, 1.0f));
			
			}
		
		
		// Boss
		{			
			GameObject* bossObj
				= object::Instantiate<GameObject>(Vector3(1.5f, 0.1f, 1.001f), eLayerType::Monster);
			bossObj->SetName(L"CagneyBoss");
			MeshRenderer* bossMr = bossObj->AddComponent<MeshRenderer>();
			bossMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

			bossMr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
			
			CagneyBossScript* bossScript = bossObj->AddComponent<CagneyBossScript>();
			
			bossScript->GetAnimator();
		
			Collider2D* bossCollider = bossScript->GetCollider();
			bossCollider->SetSize(Vector2(0.4f, 1.0f));
			bossCollider->SetCenter(Vector2(0.5f, 0.0f));
			Transform* bossTr = bossScript->GetTransform();
			bossTr->SetScale(Vector3(4.0f, 4.0f, 1.0f)); 
			
		}

		// Platform1 Propeller
		{
			GameObject* platform1
				= object::Instantiate<GameObject>(Vector3(-2.99f, -0.48f, 1.002f), eLayerType::BackGround);
			platform1->SetName(L"Platform1Propeller");

			MeshRenderer* platformMr1 = platform1->AddComponent<MeshRenderer>();
			platformMr1->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			platformMr1->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

			Animator* mPlat1Anim = platform1->AddComponent<Animator>();
			std::shared_ptr<Texture> animPlat1 = Resources::Load<Texture>(L"animPlatform", L"..\\Resources\\Texture\\CagneyCarnation\\Platform\\PropellerAnim.png");
			mPlat1Anim->Create(L"animPlatform", animPlat1, Vector2(0.0f, 0.0f), Vector2(117.0f, 39.0f), 9, 0.08f);
			mPlat1Anim->PlayAnimation(L"animPlatform", true);

			Transform* platform1Tr = platform1->GetComponent<Transform>();
			platform1Tr->SetScale(Vector3(1.5f, 1.0f, 1.0f));
		}
		// platform1 Ground
		{
			GameObject* platform1
				= object::Instantiate<GameObject>(Vector3(-3.0f, -0.25f, 1.001f), eLayerType::BackGround);
			platform1->SetName(L"Platform1Texture");

			MeshRenderer* platformMr1 = platform1->AddComponent<MeshRenderer>();
			platformMr1->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			platformMr1->SetMaterial(Resources::Find<Material>(L"PlatformOne_Material"));

			Transform* platform1Tr = platform1->GetComponent<Transform>();
			platform1Tr->SetScale(Vector3(1.0f, 0.5f, 1.0f));
		}
		// platform1 Collider
		{
			GameObject* platform1
				= object::Instantiate<GameObject>(Vector3(-3.0f, -0.02f, 1.003f), eLayerType::Ground);
			platform1->SetName(L"Platform1");
			platform1->AddComponent<GroundScript>();

			Transform* platform1Tr = platform1->GetComponent<Transform>();
			platform1Tr->SetScale(Vector3(1.0f, 0.5f, 1.0f));

			Collider2D* platform1Coll = platform1->GetComponent<Collider2D>();
			platform1Coll->SetSize(Vector2(0.8f, 0.2f));
			platform1Coll->SetCenter(Vector2(0.0f, 0.0f));
		}

		// Ground
		{
			GameObject* ground
				= object::Instantiate<GameObject>(Vector3(0.0f, -1.5f, 1.001f), eLayerType::Ground);
			ground->SetName(L"Ground");
			ground->AddComponent<GroundScript>();

			Transform* groundTr = ground->GetComponent<Transform>();
			groundTr->SetScale(Vector3(8.0f, 0.5f, 1.0f));

			//Collider2D* cd = ground->AddComponent<Collider2D>();
			//cd->SetSize(Vector2(1.0f, 1.0f));
		}
		// BulletDestroyWall
		{
			GameObject* bulletDestroyWall = object::Instantiate<GameObject>(Vector3(4.0f, 0.0f, 1.001f), eLayerType::Wall);
			bulletDestroyWall->SetName(L"bulletDestroy");
			bulletDestroyWall->AddComponent<GroundScript>();

			Transform* bulletDestroyWallTr = bulletDestroyWall->GetComponent<Transform>();
			bulletDestroyWallTr->SetScale(Vector3(0.3f, 4.0f, 1.0f));
		}
	
		// HP
		{
			GameObject* hpBar
				= object::Instantiate<GameObject>(Vector3(-3.6f, -2.0f, 1.0f), eLayerType::BackGround);
			hpBar->SetName(L"HP3");
			MeshRenderer* mr = hpBar->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"HP3_Material"));
			hpBar->GetComponent<Transform>()->SetScale(Vector3(0.5f, 0.2f, 1.00001f));
			//player->AddComponent<CameraScript>();
			//cd->SetSize(Vector2(1.2f, 1.2f));
		}
		
		// BG
		{
			GameObject* BossOneBG
				= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.999f), eLayerType::BackGround);
			MeshRenderer* BossOneMr = BossOneBG->AddComponent<MeshRenderer>();
			BossOneMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			BossOneMr->SetMaterial(Resources::Find<Material>(L"BossStage1_Material"));
			BossOneBG->GetComponent<Transform>()->SetScale(Vector3(7.99f, 4.5f, 1.0f));
			// BossOneBG->GetComponent<Transform>()->SetScale(Vector3(16.0f, 9.0f, 1.0f));

			// AudioSource* as = BossOneBG->AddComponent<AudioSource>();
			// as->SetClip(Resources::Load<AudioClip>(L"TestSound", L"..\\Resources\\Sound\\0.mp3"));
			// as->Play();
		}
		
		// BG
		{
			GameObject* FlowerFrontBG
				= object::Instantiate<GameObject>(Vector3(0.0f, -1.9f, 1.00002f), eLayerType::BackGround);
			MeshRenderer* FlowerFrontMr = FlowerFrontBG->AddComponent<MeshRenderer>();
			FlowerFrontMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			FlowerFrontMr->SetMaterial(Resources::Find<Material>(L"FlowerFront_Material"));
			FlowerFrontBG->GetComponent<Transform>()->SetScale(Vector3(10.0f, 2.0f, 1.0f));
		}
		
		// Enter Spot Object
		{
			EnterSpotObj
				= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 0.999f), eLayerType::BackGround);
			EnterSpotObj->SetName(L"EnterSpot");
			MeshRenderer* mrEnterSpot = EnterSpotObj->AddComponent<MeshRenderer>();
			mrEnterSpot->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mrEnterSpot->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
			Animator* EnterAnim = EnterSpotObj->AddComponent<Animator>();

			std::shared_ptr<Texture> enterAnimSpot = Resources::Load<Texture>(L"EnterAnimSpot", L"..\\Resources\\Texture\\EnterSpot\\EnterSpotAnim.png");
			EnterAnim->Create(L"EnterAnimSpot", enterAnimSpot, Vector2(0.0f, 0.0f), Vector2(508.0f, 287.0f), 17, 0.07f);
			EnterAnim->PlayAnimation(L"EnterAnimSpot", false);

			Transform* EnterSpotTrans = EnterSpotObj->GetComponent<Transform>();
			EnterSpotTrans->SetScale(Vector3(8.0f, 4.5f, 1.0f));

		}

		//Main Camera
		Camera* cameraComp = nullptr;
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
			renderer::cameras.push_back(cameraComp);
			renderer::mainCamera = cameraComp;

			// camera->AddComponent<AudioListener>();
		}
		
		//UI Camera
		{
			// GameObject* camera = new GameObject();
			// AddGameObject(eLayerType::Camera, camera);
			//GameObject* camera = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, -10.0f), eLayerType::Camera);
			// camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			//Camera* cameraComp = camera->AddComponent<Camera>();
			//cameraComp->TurnLayerMask(eLayerType::Player, false);
			//cameraComp->TurnLayerMask(eLayerType::Monster, false);
			//cameraComp->TurnLayerMask(eLayerType::NotMonster, false);
			//cameraComp->TurnLayerMask(eLayerType::BackGround, false);
			//camera->AddComponent<CameraScript>();
		}
		// Light (test), Direct
		{
			GameObject* light = new GameObject();
			light->SetName(L"Light");
			AddGameObject(eLayerType::Light, light);
			Light* lightComp = light->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetColor(Vector4(0.8f, 0.8f, 0.8f, 1.0f));
		}
	}

	void BossOneScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(L"WinScene");
		}
		if(EnterCheck == false)
			EnterCheckTime += 1.2f * Time::DeltaTime();
		if (EnterCheckTime > 4.0f)
		{
			EnterCheck = true;
			object::Destroy(EnterSpotObj);
		}

		Scene::Update();
	}

	void BossOneScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void BossOneScene::Render()
	{
		Scene::Render();
	}

	void BossOneScene::OnEnter()
	{
		// Scene::OnEnter();
	}
	void BossOneScene::OnExit()
	{
		// Scene::OnExit();
	}
}