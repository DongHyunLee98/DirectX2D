#include "dhLogoScene.h"
#include "dhTransform.h"
#include "dhMeshRenderer.h"
#include "dhResources.h"
#include "dhMesh.h"
#include "dhCameraScript.h"
#include "dhCamera.h"
#include "dhSceneManager.h"
#include "dhInput.h"
#include "dhObject.h"
#include "dhAnimator.h"

#include "dhPlayerScript.h"

namespace dh
{
	LogoScene::LogoScene()
	{
	}
	LogoScene::~LogoScene()
	{
	}
	void LogoScene::Initialize()
	{
		// GameObject* player = new GameObject();
		// player->SetName(L"Smile");
		// AddGameObject(eLayerType::Player, player);
		// MeshRenderer* mr = player->AddComponent<MeshRenderer>();
		// mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		// mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial02"));
		// player->GetComponent<Transform>()->SetPosition(Vector3(3.0f, 0.0f, 1.0f));

		//Main Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Camera, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
		}
		
		//UI Camera
		{
			// GameObject* camera = new GameObject();
			// AddGameObject(eLayerType::Camera, camera);
			// camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			// Camera* cameraComp = camera->AddComponent<Camera>();
			// cameraComp->TurnLayerMask(eLayerType::BackGround, false);
			// cameraComp->TurnLayerMask(eLayerType::Player, false);
			// cameraComp->TurnLayerMask(eLayerType::Monster, false);
			// // camera->AddComponent<CameraScript>();
		}
		
		/*
		// Logo BG
		{
			GameObject* LogoBG
				= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.9f), eLayerType::BackGround);
			MeshRenderer* LogoMr = LogoBG->AddComponent<MeshRenderer>();
			// titleBG->SetName(L"TitleBG");
			// AddGameObject(eLayerType::Player, player); Instatiate를 이용해 구현
			LogoMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			LogoMr->SetMaterial(Resources::Find<Material>(L"Logo_Material"));

			// Transform* titleTr = titleBG->GetComponent<Transform>();
			// titleTr->SetPosition(Vector3(1.0f, 0.95f, 5.0f));
			// titleTr->SetScale(Vector3(8.0f, 4.5f, 1.0f));
			LogoBG->GetComponent<Transform>()->SetScale(Vector3(8.2f, 4.5f, 1.0f));
			//titleTr->SetScale(Vector3(1600.0f, 900.0f, 1.0f));

		}
		*/
	
		//// 애니메이션 테스트용 젤다
		//{
		//	GameObject* player 
		//		= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0001f), eLayerType::Player);

		//	player->SetName(L"Zelda");

		//	Collider2D* cd = player->AddComponent<Collider2D>();
		//	cd->SetSize(Vector2(1.2f, 1.2f));

		//	MeshRenderer* mr = player->AddComponent<MeshRenderer>();
		//	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//	mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		//	const float pi = 3.141592f;
		//	float degree = pi / 8.0f;

		//	player->GetComponent<Transform>()->SetPosition(Vector3(-2.0f, 0.0f, 1.0001f));
		//	//player->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, degree));

		//	std::shared_ptr<Texture> atlas
		//		= Resources::Load<Texture>(L"LinkSprite", L"..\\Resources\\Texture\\linkSprites.png");

		//	Animator* at = player->AddComponent<Animator>();
		//	at->Create(L"Idle", atlas, Vector2(0.0f, 0.0f), Vector2(120.0f, 130.0f), 3);

		//	//at->CompleteEvent(L"Idle") = std::bind();

		//	at->PlayAnimation(L"Idle", true);
		//	player->AddComponent<PlayerScript>();
		//}

		//{
		//	GameObject* player = new GameObject();
		//	player->SetName(L"Smile");
		//	AddGameObject(eLayerType::Monster, player);
		//	MeshRenderer* mr = player->AddComponent<MeshRenderer>();
		//	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//	mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial02"));
		//	player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.0f));
		//	Collider2D* cd = player->AddComponent<Collider2D>();
		//	//cd->SetSize(Vector2(1.2f, 1.2f));
		//	//player->AddComponent<PlayerScript>();
		//}
		
	}

	void LogoScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(L"StartScene");
		}
		Scene::Update();
	}

	void LogoScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void LogoScene::Render()
	{
		Scene::Render();
	}
}