#include "guiEditor.h"
#include "..\\Engine_SOURCE\\dhMesh.h"
#include "..\\Engine_SOURCE\\dhMesh.h"
#include "..\\Engine_SOURCE\\dhResources.h"
#include "..\\Engine_SOURCE\\dhTransform.h"
#include "..\\Engine_SOURCE\\dhMeshRenderer.h"
#include "..\\Engine_SOURCE\\dhMaterial.h"
#include "..\\Engine_SOURCE\\dhRenderer.h"


#include "dhGridScript.h"

namespace gui
{
	using namespace dh::enums;
	std::vector<Widget*> Editor::mWidgets = {};
	std::vector<EditorObject*> Editor::mEditorObjects = {};
	std::vector<DebugOjbect*> Editor::mDebugObjects = {};

	void Editor::Initialize()
	{
		mDebugObjects.resize((UINT)eColliderType::End);

		std::shared_ptr<dh::Mesh> mesh
			= dh::Resources::Find<dh::Mesh>(L"DebugRect");
		std::shared_ptr<dh::Material> material
			= dh::Resources::Find<dh::Material>(L"DebugMaterial");

		mDebugObjects[(UINT)eColliderType::Rect] = new DebugOjbect();
		mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<dh::Transform>();
		dh::MeshRenderer* mr
			= mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<dh::MeshRenderer>();
		mr->SetMaterial(material);
		mr->SetMesh(mesh);


		EditorObject* grid = new EditorObject();
		grid->SetName(L"Grid");

		mr = grid->AddComponent<dh::MeshRenderer>();
		mr->SetMesh(dh::Resources::Find<dh::Mesh>(L"RectMesh"));
		mr->SetMaterial(dh::Resources::Find<dh::Material>(L"GridMaterial"));
		dh::GridScript* gridSc = grid->AddComponent<dh::GridScript>();
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

		for (EditorObject* obj : mEditorObjects)
		{
			obj->Render();
		}

		for (const dh::graphics::DebugMesh& mesh 
			: renderer::debugMeshs)
		{
			DebugRender(mesh);
		}
		renderer::debugMeshs.clear();
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

		for (auto debugObj : mDebugObjects)
		{
			delete debugObj;
			debugObj = nullptr;
		}

	}

	void Editor::DebugRender(const dh::graphics::DebugMesh& mesh)
	{
		DebugOjbect* debugObj = mDebugObjects[(UINT)mesh.type];

		// 위치 크기 회전 정보를 받아와서
		// 해당 게임오브젝트위에 그려주면된다.
		dh::Transform* tr = debugObj->GetComponent<dh::Transform>();
		
		Vector3 pos = mesh.position;
		pos.z -= 0.01f;

		tr->SetPosition(pos);
		tr->SetScale(mesh.scale);
		tr->SetRotation(mesh.rotation);

		tr->LateUpdate();

		/*ya::MeshRenderer * mr 
			= debugObj->GetComponent<ya::MeshRenderer>();*/
		// main camera
		dh::Camera* mainCamara = renderer::mainCamera;

		dh::Camera::SetGpuViewMatrix(mainCamara->GetViewMatrix());
		dh::Camera::SetGpuProjectionMatrix(mainCamara->GetProjectionMatrix());

		debugObj->Render();
	}
}
