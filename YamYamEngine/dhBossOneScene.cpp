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

#include "dhPaintShader.h"
#include "dhConstantBuffer.h"

namespace dh
{
	BossOneScene::BossOneScene()
	{
	}
	BossOneScene::~BossOneScene()
	{
	}
	void BossOneScene::Initialize()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);

		std::shared_ptr<PaintShader> paintShader = Resources::Find<PaintShader>(L"PaintShader");
		std::shared_ptr<Texture> paintTexture = Resources::Find<Texture>(L"PaintTexuture");
		paintShader->SetTarget(paintTexture);
		paintShader->OnExcute();

		// 변경된 Smile(페인트텍스쳐)
		{
			GameObject* paint = new GameObject();
			paint->SetName(L"paint");
			AddGameObject(eLayerType::Monster, paint);
			MeshRenderer* paintMr = paint->AddComponent<MeshRenderer>();
			paintMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			paintMr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial02"));
			paint->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 1.0f, 1.0f));
			Collider2D* cd = paint->AddComponent<Collider2D>();
		}			

		// Player
		{
			GameObject* player
				= object::Instantiate<GameObject>(Vector3(-2.0f, -0.9f, 1.0001f), eLayerType::Player);
			player->SetName(L"Player_Boss");
			MeshRenderer* playerMr = player->AddComponent<MeshRenderer>();
			playerMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			playerMr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
			
			Animator* at = player->AddComponent<Animator>();
			player->AddComponent<PlayerBossScript>();

			Transform* playerTr = player->GetComponent<Transform>();

			playerTr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
			// playerTr->SetPosition(Vector3(0.0f, 1.0f, 1.0f));

			Collider2D* cd = player->AddComponent<Collider2D>();
			cd->SetSize(Vector2(0.4f, 0.5f));
			cd->SetCenter(Vector2(0.0f, -0.1f));
		}

		// Ground
		{
			GameObject* ground
				= object::Instantiate<GameObject>(Vector3(0.0f, -1.5f, 1.0001f), eLayerType::Ground);
			ground->SetName(L"Ground");
			Transform* groundTr = ground->GetComponent<Transform>();
			groundTr->SetScale(Vector3(7.0f, 0.5f, 1.0f));
			Collider2D* cd = ground->AddComponent<Collider2D>();
			cd->SetSize(Vector2(1.0f, 1.0f));
		}
		// Boss
		{
			GameObject* boss
				= object::Instantiate<GameObject>(Vector3(2.0f, 0.0f, 1.0001f), eLayerType::Monster);
			boss->SetName(L"FlowerBoss");

			MeshRenderer* mr = boss->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"FlowerBoss_Material"));

			boss->GetComponent<Transform>()->SetScale(Vector3(3.0f, 3.0f, 1.0f));

			Collider2D* cd = boss->AddComponent<Collider2D>();
			cd->SetSize(Vector2(0.3f, 1.0f));
			cd->SetCenter(Vector2(0.2f, 0.25f));
			//boss->AddComponent<Boss1Script>();
		}

		// HP
		{
			GameObject* hpBar
				= object::Instantiate<GameObject>(Vector3(-3.2f, -1.8f, 2.0f), eLayerType::BackGround);
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
				= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 2.0f), eLayerType::BackGround);
			MeshRenderer* BossOneMr = BossOneBG->AddComponent<MeshRenderer>();
			BossOneMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			BossOneMr->SetMaterial(Resources::Find<Material>(L"BossStage1_Material"));
			BossOneBG->GetComponent<Transform>()->SetScale(Vector3(8.2f, 4.5f, 1.0f));
		}
		//Main Camera
		Camera* cameraComp = nullptr;
		{
			// GameObject* camera = new GameObject();
			GameObject* camera = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, -10.0f), eLayerType::Camera);
			// AddGameObject(eLayerType::Camera, camera);
			// camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			// camera->AddComponent<CameraScript>();
			renderer::cameras.push_back(cameraComp);
			renderer::mainCamera = cameraComp;
		}

		//UI Camera
		{
			// GameObject* camera = new GameObject();
			// AddGameObject(eLayerType::Camera, camera);
			GameObject* camera = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, -10.0f), eLayerType::Camera);
			// camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::Player, false);
			cameraComp->TurnLayerMask(eLayerType::Monster, false);
			cameraComp->TurnLayerMask(eLayerType::NotMonster, false);
			cameraComp->TurnLayerMask(eLayerType::BackGround, false);
			//camera->AddComponent<CameraScript>();
		}

		// Light (test), Direct
		{
			GameObject* light = new GameObject();
			light->SetName(L"Smile");
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
		Scene::OnEnter();
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
	}
	void BossOneScene::OnExit()
	{
		Scene::OnExit();
	}
}