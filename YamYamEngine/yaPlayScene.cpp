#include "yaPlayScene.h"
#include "yaTransform.h"
#include "yaMeshRenderer.h"
#include "yaResources.h"
#include "yaMesh.h"
#include "yaCameraScript.h"
#include "yaCamera.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "dhGridScript.h"
#include "Object.h"
#include "yaRenderer.h"
#include "dhCollider2D.h"

namespace ya
{
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		{
			// GameObject* player = new GameObject(); Instatiate를 이용해 구현
			GameObject* player
				= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0001f), eLayerType::Player);

			player->SetName(L"Zelda");
			// AddGameObject(eLayerType::Player, player); Instatiate를 이용해 구현

			// player->AddComponent<Collider2D>();
			Collider2D* cd = player->AddComponent<Collider2D>();
			//cd->SetCenter(Vector2(0.5f, 0.0f));

			//cd = player->AddComponent<Collider2D>();
			////cd->SetCenter(Vector2(0.f, 0.0f));

			//std::vector<Collider2D*> comps 
			//	= player->GetComponents<Collider2D>();

			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));

			// Instatiate를 이용해 구현
			// player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.0001f));
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

			const float pi = 3.141592f;
			float degree = pi / 8.0f;

			// 7/13일 Rotate체크, 충돌콜라이더 회전한걸 확인
			player->GetComponent<Transform>()->SetPosition(Vector3(-2.0f, 0.0f, 1.0001f));
			player->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, degree));
		}

		{
			GameObject* player = new GameObject();
			player->SetName(L"Smile");
			AddGameObject(eLayerType::Player, player);
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial02"));
			player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.0f));
			//player->AddComponent<CameraScript>();
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

		//Main Camera
		Camera* cameraComp = nullptr;
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Camera, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>(); 
			renderer::cameras.push_back(cameraComp);
			renderer::mainCamera = cameraComp;
		}
		
		//UI Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Camera, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::BackGround, false);
			cameraComp->TurnLayerMask(eLayerType::Player, false);
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
		{
			GameObject* TestBG
				= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0001f), eLayerType::BackGround);
			TestBG->SetName(L"TestFloor");
			// AddGameObject(eLayerType::Player, player); Instatiate를 이용해 구현
			MeshRenderer* TestBGMr = TestBG->AddComponent<MeshRenderer>();
			TestBGMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			TestBGMr->SetMaterial(Resources::Find<Material>(L"TestFloor"));

			Transform* TestBGTr = TestBG->GetComponent<Transform>();
			//titleTr->SetPosition(Vector3(1.0f, 0.95f, 5.0f));
			TestBGTr->SetScale(Vector3(8.0f, 4.5f, 1.0f));
			//titleTr->SetScale(Vector3(1600.0f, 900.0f, 1.0f));
		}

		//GameObject* player2 = new GameObject();
		//AddGameObject(eLayerType::Player, player2);
		//player2->AddComponent<MeshRenderer>();

		//Transform* tr = player->GetComponent<Transform>();
		//tr->SetPosition(Vector3(0.5f, 0.5f, 0.0f));
	}

	void PlayScene::Update()
	{
		Scene::Update();
	}

	void PlayScene::LateUpdate()
	{
		// 마우스 좌표계
		Vector3 pos(800, 450, 0.0f);
		Vector3 pos2(800, 450, 1000.0f);
		Viewport viewport;
		viewport.width = 1600.0f;
		viewport.height = 900.0f;
		viewport.x = 0;
		viewport.y = 0;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		// 콜라이더 충돌체 렌더링할때 카메라에 만든 GetSet GPU프로젝션매트릭스 사용
		pos = viewport.Unproject(pos, Camera::GetGpuProjectionMatrix(), Camera::GetGpuViewMatrix(), Matrix::Identity);
		pos2 = viewport.Unproject(pos2, Camera::GetGpuProjectionMatrix(), Camera::GetGpuViewMatrix(), Matrix::Identity);

		Scene::LateUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}
}