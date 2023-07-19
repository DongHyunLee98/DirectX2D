#pragma once
#include "..\\Engine_SOURCE\\CommonInclude.h"
#include "..\\Engine_SOURCE\\YamYamEngine.h"
#include "..\\Engine_SOURCE\\dhGraphics.h"

#include "guiWidget.h"
#include "guiEditorObject.h"
#include "guiDebugOjbect.h"

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

		static void DebugRender(const dh::graphics::DebugMesh& mesh);

	private:
		static std::vector<Widget*> mWidgets;
		static std::vector<EditorObject*> mEditorObjects;
		static std::vector<DebugOjbect*> mDebugObjects;
	};
}
