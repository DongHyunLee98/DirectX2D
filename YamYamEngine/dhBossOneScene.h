#pragma once
//#include "yaScene.h"
#include "..\Engine_SOURCE\dhScene.h"

namespace dh
{
	class BossOneScene : public Scene
	{
	public:
		BossOneScene();
		~BossOneScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		GameObject* EnterSpotObj;
		float EnterCheckTime;
		bool EnterCheck;
		bool ReadWallopSwitch;
		float ReadWallopTime;
	};
}
