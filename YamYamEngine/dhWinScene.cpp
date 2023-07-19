#include "dhWinScene.h"
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
	WinScene::WinScene()
	{
	}
	WinScene::~WinScene()
	{
	}
	void WinScene::Initialize()
	{
		// 뒷배경
		{
			GameObject* winBG
				= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 2.0f), eLayerType::BackGround);
			MeshRenderer* winBGMr = winBG->AddComponent<MeshRenderer>();
			winBGMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			winBGMr->SetMaterial(Resources::Find<Material>(L"winscreen_bg_Material"));
			winBG->GetComponent<Transform>()->SetScale(Vector3(8.2f, 4.5f, 1.0f));
		}

		//보드
		{
			GameObject* winBoard
				= object::Instantiate<GameObject>(Vector3(1.5f, -0.6f, 1.9f), eLayerType::BackGround);
			MeshRenderer* winBoardMr = winBoard->AddComponent<MeshRenderer>();
			winBoardMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			winBoardMr->SetMaterial(Resources::Find<Material>(L"winscreen_board_Material"));
			winBoard->GetComponent<Transform>()->SetScale(Vector3(4.0f,	3.0f, 1.0f));
		}
		
		// 별
		{
			GameObject* winStar
				= object::Instantiate<GameObject>(Vector3(2.0f, -1.0f, 1.8f), eLayerType::UI);
			MeshRenderer* winStarMr = winStar->AddComponent<MeshRenderer>();
			winStarMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			winStarMr->SetMaterial(Resources::Find<Material>(L"winscreen_star_Material"));
			winStar->GetComponent<Transform>()->SetScale(Vector3(0.5f, 0.5f, 1.0f));
		}
		
		// 글자
		{
			GameObject* winString
				= object::Instantiate<GameObject>(Vector3(0.0f, 1.6f, 1.8f), eLayerType::UI);
			MeshRenderer* winStringMr = winString->AddComponent<MeshRenderer>();
			winStringMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			winStringMr->SetMaterial(Resources::Find<Material>(L"winscreen_results_title_Material"));
			winString->GetComponent<Transform>()->SetScale(Vector3(5.0f, 1.0f, 1.0f));
		}

		// 결과 캐릭터
		{
			GameObject* winChara
				= object::Instantiate<GameObject>(Vector3(-2.0f, -0.5f, 1.8f), eLayerType::UI);
			MeshRenderer* winCharaMr = winChara->AddComponent<MeshRenderer>();
			winCharaMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			winCharaMr->SetMaterial(Resources::Find<Material>(L"winscreen_ch_Material"));
			winChara->GetComponent<Transform>()->SetScale(Vector3(2.0f, 3.0f, 1.0f));
		}

		//Main Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Camera, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
		}

		// UI Camera
		{
			GameObject* camera = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, -10.0f), eLayerType::Camera);
			// camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::BackGround, false);
		}
	}

	void WinScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(L"EndScene");
		}
		Scene::Update();
	}

	void WinScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void WinScene::Render()
	{
		Scene::Render();
	}
}