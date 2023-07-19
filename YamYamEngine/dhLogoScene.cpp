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

		// Logo BG
		{
			GameObject* LogoBG
				= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0f), eLayerType::BackGround);
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