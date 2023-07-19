#pragma once
#include "..\\Engine_SOURCE\\dhGameObject.h"


namespace gui
{
	class DebugOjbect : public dh::GameObject
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
