#include "dhEndScene.h"
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
	EndScene::EndScene()
	{
	}
	EndScene::~EndScene()
	{
	}
	void EndScene::Initialize()
	{

		GameObject* endBG
			= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 2.0f), eLayerType::BackGround);
		MeshRenderer* endMr = endBG->AddComponent<MeshRenderer>();
		endMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		endMr->SetMaterial(Resources::Find<Material>(L"End_Material"));
		endBG->GetComponent<Transform>()->SetScale(Vector3(8.2f, 4.5f, 1.0f));

		//Main Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Camera, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
		}

		// Transform* titleTr = titleBG->GetComponent<Transform>();
		// titleTr->SetPosition(Vector3(1.0f, 0.95f, 5.0f));
		// titleTr->SetScale(Vector3(8.0f, 4.5f, 1.0f));
		// titleTr->SetScale(Vector3(1600.0f, 900.0f, 1.0f));

	}

	void EndScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			// SceneManager::LoadScene(L"StartScene");
		}
		Scene::Update();
	}

	void EndScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void EndScene::Render()
	{
		Scene::Render();
	}
}