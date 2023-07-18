#include "dhCharaScene.h"
#include "yaTransform.h"
#include "yaMeshRenderer.h"
#include "yaResources.h"
#include "yaMesh.h"
#include "yaCameraScript.h"
#include "yaCamera.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "Object.h"

namespace ya
{
	CharaScene::CharaScene()
	{
	}
	CharaScene::~CharaScene()
	{
	}
	void CharaScene::Initialize()
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
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Camera, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::BackGround, false);
			cameraComp->TurnLayerMask(eLayerType::Player, false);
			cameraComp->TurnLayerMask(eLayerType::Monster, false);
			//camera->AddComponent<CameraScript>();
		}

		// Title BG

		GameObject* titleBG
			= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 2.0f), eLayerType::BackGround);
		MeshRenderer* titleMr = titleBG->AddComponent<MeshRenderer>();
		// titleBG->SetName(L"TitleBG");
		// AddGameObject(eLayerType::Player, player); Instatiate를 이용해 구현
		titleMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		titleMr->SetMaterial(Resources::Find<Material>(L"TitleBGMaterial"));

		// Transform* titleTr = titleBG->GetComponent<Transform>();
		// titleTr->SetPosition(Vector3(1.0f, 0.95f, 5.0f));
		// titleTr->SetScale(Vector3(8.0f, 4.5f, 1.0f));
		titleBG->GetComponent<Transform>()->SetScale(Vector3(8.0f, 4.5f, 1.0f));
		//titleTr->SetScale(Vector3(1600.0f, 900.0f, 1.0f));

		// SpritePS 에서 anisotropicSampler를 포인트샘플러로 변경 

	// Continue
		{
			GameObject* continueBar
				= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0001f), eLayerType::BackGround);
			continueBar->SetName(L"ContinueBar");
			// AddGameObject(eLayerType::Player, player); Instatiate를 이용해 구현
			MeshRenderer* continueMr = continueBar->AddComponent<MeshRenderer>();
			continueMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			continueMr->SetMaterial(Resources::Find<Material>(L"ContinueMaterial"));

			Transform* continueTr = continueBar->GetComponent<Transform>();
			continueTr->SetPosition(Vector3(0.08f, -1.7f, 0.9f));
			continueTr->SetScale(Vector3(3.0f, 0.25f, 1.0f));
			//titleTr->SetScale(Vector3(1600.0f, 900.0f, 1.0f));

			// SpritePS 에서 anisotropicSampler를 포인트샘플러로 변경 (이방성사용안함)
		}
	}

	void CharaScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			// SceneManager::LoadScene(L"PlayScene");
		}
		Scene::Update();
	}

	void CharaScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void CharaScene::Render()
	{
		Scene::Render();
	}
}