#pragma once
#include "CommonInclude.h"
#include "YamYamEngine.h"
#include "guiWidget.h"
#include "guiEditorObject.h"
#include "guiDebugOjbect.h"
#include "yaGraphics.h"

namespace gui
{
	class Editor
	{
	public:
		static void Initialize();
		static void Run();

		static void Update();
		static void LateUpdate();
		static void Render();
		static void Release();

		static void DebugRender(const ya::graphics::DebugMesh& mesh);

	private:
		static std::vector<Widget*> mWidgets;
		static std::vector<EditorObject*> mEditorObjects;
		static std::vector<DebugOjbect*> mDebugOjbects;
	};
}
