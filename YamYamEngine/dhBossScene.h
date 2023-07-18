#pragma once
//#include "yaScene.h"
#include "..\Engine_SOURCE\yaScene.h"

namespace ya
{
	class BossScene : public Scene
	{
	public:
		BossScene();
		~BossScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}
