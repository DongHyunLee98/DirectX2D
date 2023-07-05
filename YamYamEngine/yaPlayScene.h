#pragma once
//#include "yaScene.h"
#include "..\Engine_SOURCE\yaScene.h"

namespace ya
{
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		virtual ~PlayScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}
