#pragma once
#include "..\\Engine_SOURCE\\yaGameObject.h"


namespace gui
{
	class DebugOjbect : public ya::GameObject
	{
	public:
		DebugOjbect();
		~DebugOjbect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
	};
}
