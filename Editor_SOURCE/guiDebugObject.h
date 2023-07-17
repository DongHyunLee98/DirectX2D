#pragma once
#include "..\\Engine_SOURCE\\yaGameObject.h"


namespace gui
{
	class DebugObject : public ya::GameObject
	{
	public:
		DebugObject();
		~DebugObject();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
	};
}
