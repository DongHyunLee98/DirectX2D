#pragma once
//#include "yaScene.h"
#include "..\Engine_SOURCE\dhScene.h"

namespace dh
{
	class EndScene : public Scene
	{
	public:
		EndScene();
		~EndScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}
