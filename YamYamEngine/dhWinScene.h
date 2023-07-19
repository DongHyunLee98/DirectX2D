#pragma once
//#include "yaScene.h"
#include "..\Engine_SOURCE\dhScene.h"

namespace dh
{
	class WinScene : public Scene
	{
	public:
		WinScene();
		~WinScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}