#pragma once
//#include "yaScene.h"
#include "..\Engine_SOURCE\dhScene.h"

namespace dh
{
	class MapScene : public Scene
	{
	public:
		MapScene();
		virtual ~MapScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}
