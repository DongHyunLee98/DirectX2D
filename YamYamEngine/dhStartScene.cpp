#include "dhStartScene.h"
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
	StartScene::StartScene()
	{
	}
	StartScene::~StartScene()
	{
	}
	void StartScene::Initialize()
	{
		
		 // Title BG
		 {
		 	GameObject* titleBG
		 		= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 2.0f), eLayerType::BackGround);
		 	MeshRenderer* titleMr = titleBG->AddComponent<MeshRenderer>();
		 	titleMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		 	titleMr->SetMaterial(Resources::Find<Material>(L"title1_Material"));
		 	titleBG->GetComponent<Transform>()->SetScale(Vector3(8.2f, 4.5f, 1.0f));
		 }
		 //Title Chara
		 {
		 	GameObject* titleCharaBG
		 		= object::Instantiate<GameObject>(Vector3(0.0f, -1.0f, 1.9f), eLayerType::BackGround);
		 	MeshRenderer* titleCharaMr = titleCharaBG->AddComponent<MeshRenderer>();
		 	titleCharaMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		 	titleCharaMr->SetMaterial(Resources::Find<Material>(L"title2_Material"));
		 	titleCharaBG->GetComponent<Transform>()->SetScale(Vector3(5.0f, 2.5f, 1.0f));
		 }

		GameObject* camera = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, -10.0f), eLayerType::Player);
		Camera* cameraComp = camera->AddComponent<Camera>();
		camera->AddComponent<CameraScript>();

		// 안되는이유 분석
		//Main Camera
		{
			// GameObject* camera = new GameObject();
			// AddGameObject(eLayerType::End, camera);
			// camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			// Camera* cameraComp = camera->AddComponent<Camera>();
			// cameraComp->TurnLayerMask(eLayerType::UI, false);
			// camera->AddComponent<CameraScript>();
		}// 
		
	}

	void StartScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(L"MapScene");
		}
		Scene::Update();
	}

	void StartScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void StartScene::Render()
	{
		Scene::Render();
	}
}