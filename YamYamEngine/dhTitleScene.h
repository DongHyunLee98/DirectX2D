#pragma once
//#include "dhScene.h"
#include "..\Engine_SOURCE\dhScene.h"

namespace dh
{
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		~TitleScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}
