#pragma once
//#include "yaScene.h"
#include "..\Engine_SOURCE\dhScene.h"

namespace dh
{
	class StartScene : public Scene
	{
	public:
		StartScene();
		~StartScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}
