#include "dhTitleScene.h"
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
	TitleScene::TitleScene()
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		// Title BG
		{
			GameObject* titleBG
				= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 2.0f), eLayerType::Camera);
			MeshRenderer* titleMr = titleBG->AddComponent<MeshRenderer>();
			titleMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			titleMr->SetMaterial(Resources::Find<Material>(L"title1_Material"));

			Transform* titleTr = titleBG->GetComponent<Transform>();
			// titleTr->SetPosition(Vector3(1.0f, 0.95f, 5.0f));
			// titleTr->SetScale(Vector3(8.0f, 4.5f, 1.0f));
			// titleBG->GetComponent<Transform>()->SetScale(Vector3(10.0f, 1.0f, 1.0f));
			titleTr->SetScale(Vector3(8.2f, 4.5f, 1.0f));
		}
		//Title Chara
		{
			GameObject* titleCharaBG
				= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.9f), eLayerType::Camera);
			MeshRenderer* titleCharaMr = titleCharaBG->AddComponent<MeshRenderer>();
			titleCharaMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			titleCharaMr->SetMaterial(Resources::Find<Material>(L"title2_Material"));

			Transform* titleCharaTr = titleCharaBG->GetComponent<Transform>();
			// titleCharaTr->SetPosition(Vector3(1.0f, 0.95f, 5.0f));
			// titleTr->SetScale(Vector3(8.0f, 4.5f, 1.0f));
			// titleBG->GetComponent<Transform>()->SetScale(Vector3(10.0f, 1.0f, 1.0f));
			titleCharaTr->SetScale(Vector3(8.2f, 4.5f, 1.0f));
		}
		//Main Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Camera, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
			// renderer::cameras.push_back(cameraComp);
			// renderer::mainCamera = cameraComp;
		}
	}

	void TitleScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(L"MapScene");
		}
		Scene::Update();
	}

	void TitleScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void TitleScene::Render()
	{
		Scene::Render();
	}
}