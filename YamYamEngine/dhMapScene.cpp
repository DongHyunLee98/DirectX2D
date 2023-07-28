#include "dhMapScene.h"
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
#include "dhCollisionManager.h"

#include "dhPlayerWorldScript.h"
#include "dhLight.h"
#include "dhComputeShader.h"

namespace dh
{
	MapScene::MapScene()
	{
	}
	MapScene::~MapScene()
	{
	}
	void MapScene::Initialize()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::NotMonster, true);

		// ComputeShader* cs = new ComputeShader();
		// cs->Create(L"PaintCS.hlsl", "main");
		/*
		{
		{
			GameObject* player = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 0.0f), eLayerType::Player);
			player->SetName(L"Player");

			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
			Animator* at = player->AddComponent<Animator>();

			player->AddComponent<PlayerScript>();

			Collider2D* cd = player->AddComponent<Collider2D>();
			cd->SetSize(Vector2(1.0f, 1.0f));
		}
		}
		*/
		{
			GameObject* mainBG
				= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.9999f), eLayerType::BackGround);
			mainBG->SetName(L"world1_large_island_main");
			// AddGameObject(eLayerType::Player, player); Instatiate를 이용해 구현
			MeshRenderer* mainBGMr = mainBG->AddComponent<MeshRenderer>();
			mainBGMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mainBGMr->SetMaterial(Resources::Find<Material>(L"world1_large_island_main_Material"));

			Transform* mainBGTr = mainBG->GetComponent<Transform>();
			//titleTr->SetPosition(Vector3(1.0f, 0.95f, 5.0f));
			mainBGTr->SetScale(Vector3(25.0f, 15.5f, 1.0f));
			//titleTr->SetScale(Vector3(1600.0f, 900.0f, 1.0f));
		}

		// Player
		{
			// GameObject* player = new GameObject(); Instatiate를 이용해 구현
			GameObject* player
				= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0001f), eLayerType::Player);
			player->SetName(L"Cuphead_Overload");

			MeshRenderer* playerMr = player->AddComponent<MeshRenderer>();
			playerMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			// playerMr->SetMaterial(Resources::Find<Material>(L"Cuphead_Overload_Material"));
			playerMr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

			Animator* at = player->AddComponent<Animator>();
			player->AddComponent<PlayerWorldScript>();

			Transform* playerTr = player->GetComponent<Transform>();

			playerTr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
			// playerTr->SetPosition(Vector3(0.0f, 1.0f, 1.0f));

			Collider2D* cd = player->AddComponent<Collider2D>();
			cd->SetSize(Vector2(0.5f, 0.5f));
			// player->GetComponent<Transform>()->SetPosition(Vector3(-2.0f, 0.0f, 1.00001f));
			// AddGameObject(eLayerType::Player, player); Instatiate를 이용해 구현

			// player->AddComponent<Collider2D>();

			//cd = player->AddComponent<Collider2D>();
			////cd->SetCenter(Vector2(0.f, 0.0f));

			//std::vector<Collider2D*> comps
			//	= player->GetComponents<Collider2D>();
			//cd->SetCenter(Vector2(0.5f, 0.0f));
			// Instatiate를 이용해 구현
			//player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.0001f));
			// player->AddComponent<CameraScript>();

			// GameObject* player2 = new GameObject();
			// player2->SetName(L"ZeldaChild");
			// AddGameObject(eLayerType::Player, player2);
			// MeshRenderer* mr2 = player2->AddComponent<MeshRenderer>();
			// mr2->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			// mr2->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
			// player2->GetComponent<Transform>()->SetPosition(Vector3(2.0f, 0.0f, 1.0001f));
			//
			// player2->GetComponent<Transform>()->SetParent(player->GetComponent<Transform>());
			//
			// player->AddComponent<CameraScript>();

			// const float pi = 3.141592f;
			// float degree = pi / 8.0f;
			//
			// // 7/13일 Rotate체크, 충돌콜라이더 회전한걸 확인
			// player->GetComponent<Transform>()->SetPosition(Vector3(-2.0f, 0.0f, 1.0001f));
			// player->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, degree));
		}

		// 7/12 Collider 작업확인 주석처리
		//{
		//	GameObject* player = new GameObject();
		//	player->SetName(L"Smile");
		//	AddGameObject(eLayerType::UI, player);
		//	MeshRenderer* mr = player->AddComponent<MeshRenderer>();
		//	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//	mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial02"));
		//	player->GetComponent<Transform>()->SetPosition(Vector3(0.2f, 0.0f, 0.0f));
		//	//player->AddComponent<CameraScript>();
		//}

		// shop
		{
			GameObject* shop
				= object::Instantiate<GameObject>(Vector3(2.0f, 0.5f, 1.0001f), eLayerType::NotMonster);
			shop->SetName(L"shop");

			MeshRenderer* mr = shop->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"Shop_Material"));

			Collider2D* cd = shop->AddComponent<Collider2D>();
			cd->SetSize(Vector2(1.1f, 1.1f));

		}

		// flag
		{
			GameObject* flag
				= object::Instantiate<GameObject>(Vector3(0.3f, 0.3f, 1.0001f), eLayerType::NotMonster);
			flag->SetName(L"flag");

			MeshRenderer* mr = flag->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"Flag1_Material"));

			Transform* flagTr = flag->GetComponent<Transform>();

			flagTr->SetScale(Vector3(0.5f, 0.5f, 1.0f));
			//flagTr->SetPosition(Vector3(0.0f, 0.0f, 1.0f));

			Collider2D* cd = flag->AddComponent<Collider2D>();
			cd->SetSize(Vector2(1.1f, 1.1f));

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
		// Light Point
		//{
		//	GameObject* light = new GameObject();
		//	light->SetName(L"Smile");
		//	AddGameObject(eLayerType::Light, light);
		//	Light* lightComp = light->AddComponent<Light>();
		//	lightComp->SetType(eLightType::Point);
		//	lightComp->SetColor(Vector4(0.0f, 0.0f, 1.0f, 1.0f));
		//	lightComp->SetRadius(3.0f);
		//}
		//Main Camera
		Camera* cameraComp = nullptr;
		{
			// GameObject* camera = new GameObject();
			GameObject* camera = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, -10.0f), eLayerType::Camera);
			// AddGameObject(eLayerType::Camera, camera);
			// camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
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


		//{
		//	GameObject* grid = new GameObject();
		//	grid->SetName(L"Grid");
		//	AddGameObject(eLayerType::Grid, grid);
		//	MeshRenderer* mr = grid->AddComponent<MeshRenderer>();
		//	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//	mr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));
		//	GridScript* gridSc = grid->AddComponent<GridScript>();
		//	gridSc->SetCamera(cameraComp);
		//}


		//GameObject* player2 = new GameObject();
		//AddGameObject(eLayerType::Player, player2);
		//player2->AddComponent<MeshRenderer>();

		//Transform* tr = player->GetComponent<Transform>();
		//tr->SetPosition(Vector3(0.5f, 0.5f, 0.0f));
	}

	void MapScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(L"BossOneScene");
		}
		Scene::Update();
	}

	void MapScene::LateUpdate()
	{
		// // 마우스 좌표계
		// Vector3 pos(800, 450, 0.0f);
		// Vector3 pos2(800, 450, 1000.0f);
		// Viewport viewport;
		// viewport.width = 1600.0f;
		// viewport.height = 900.0f;
		// viewport.x = 0;
		// viewport.y = 0;
		// viewport.minDepth = 0.0f;
		// viewport.maxDepth = 1.0f;
		// 
		// // 콜라이더 충돌체 렌더링할때 카메라에 만든 GetSet GPU프로젝션매트릭스 사용
		// pos = viewport.Unproject(pos, Camera::GetGpuProjectionMatrix(), Camera::GetGpuViewMatrix(), Matrix::Identity);
		// pos2 = viewport.Unproject(pos2, Camera::GetGpuProjectionMatrix(), Camera::GetGpuViewMatrix(), Matrix::Identity);

		Scene::LateUpdate();
	}

	void MapScene::Render()
	{
		Scene::Render();
	}
}