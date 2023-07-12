#include "guiEditor.h"
#include "..\\Engine_SOURCE\\yaMesh.h"
#include "..\\Engine_SOURCE\\yaMesh.h"
#include "..\\Engine_SOURCE\\yaResources.h"
#include "..\\Engine_SOURCE\\yaTransform.h"
#include "..\\Engine_SOURCE\\yaMeshRenderer.h"
#include "..\\Engine_SOURCE\\yaMaterial.h"
#include "..\\Engine_SOURCE\\yaRenderer.h"

#include "dhGridScript.h"

namespace gui
{
	using namespace ya::enums;
	std::vector<Widget*> Editor::mWidgets = {};
	std::vector<EditorObject*> Editor::mEditorObjects = {};
	std::vector<DebugOjbect*> Editor::mDebugOjbects = {};

	void Editor::Initialize()
	{
		mDebugOjbects.resize((UINT)eColliderType::End);

		std::shared_ptr<ya::Mesh> mesh
			= ya::Resources::Find<ya::Mesh>(L"DebugRect");
		std::shared_ptr<ya::Material> material
			= ya::Resources::Find<ya::Material>(L"DebugMaterial");

		mDebugOjbects[(UINT)eColliderType::Rect] = new DebugOjbect();
		mDebugOjbects[(UINT)eColliderType::Rect]->AddComponent<ya::Transform>();
		ya::MeshRenderer* mr
			= mDebugOjbects[(UINT)eColliderType::Rect]->AddComponent<ya::MeshRenderer>();
		mr->SetMaterial(material);
		mr->SetMesh(mesh);


		EditorObject* grid = new EditorObject();
		grid->SetName(L"Grid");

		mr = grid->AddComponent<ya::MeshRenderer>();
		mr->SetMesh(ya::Resources::Find<ya::Mesh>(L"RectMesh"));
		mr->SetMaterial(ya::Resources::Find<ya::Material>(L"GridMaterial"));
		ya::GridScript* gridSc = grid->AddComponent<ya::GridScript>();
		gridSc->SetCamera(renderer::cameras[0]);

		mEditorObjects.push_back(grid);

	}
	void Editor::Run()
	{
		Update();
		LateUpdate();
		Render();
	}
	void Editor::Update()
	{


		for (EditorObject* obj : mEditorObjects)
		{
			obj->Update();
		}
	}
	void Editor::LateUpdate()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->LateUpdate();
		}
	}
	void Editor::Render()
	{
		//Microsoft::WRL::ComPtr<ID3D11DepthStencilState> ds
		//	= renderer::depthStencilStates[(UINT)ya::graphics::eDSType::Less];
		//ya::graphics::GetDevice()->BindDepthStencilState(ds.Get());

		for (EditorObject* obj : mEditorObjects)
		{
			obj->Render();
		}

		for (const ya::graphics::DebugMesh& mesh 
			: renderer::debugMeshs)
		{
			DebugRender(mesh);
		}
	}
	void Editor::Release()
	{
		for (auto widget : mWidgets)
		{
			delete widget;
			widget = nullptr;
		}

		for (auto editorObj : mEditorObjects)
		{
			delete editorObj;
			editorObj = nullptr;
		}

		for (auto debugObj : mDebugOjbects)
		{
			delete debugObj;
			debugObj = nullptr;
		}

	}

	void Editor::DebugRender(const ya::graphics::DebugMesh& mesh)
	{
		DebugOjbect* debugObj = mDebugOjbects[(UINT)mesh.type];

		// 위치 크기 회전 정보를 받아와서
		// 해당 게임오브젝트위에 그려주면된다.

		ya::Transform* tr = debugObj->GetComponent<ya::Transform>();

		Vector3 pos = mesh.position;
		pos.z -= 0.01f;

		tr->SetPosition(pos);
		tr->SetScale(mesh.scale);
		tr->SetRotation(mesh.rotation);

		tr->LateUpdate();

		/*ya::MeshRenderer * mr
			= debugObj->GetComponent<ya::MeshRenderer>();*/
			// main camera
		ya::Camera* mainCamara = renderer::mainCamera;

		ya::Camera::SetGpuViewMatrix(mainCamara->GetViewMatrix());
		ya::Camera::SetGpuProjectionMatrix(mainCamara->GetProjectionMatrix());

		debugObj->Render();
	}
}
