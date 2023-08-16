#pragma once
#include "..\Engine_SOURCE\dhSceneManager.h"
#include "dhLogoScene.h"
#include "dhStartScene.h"
// #include "dhTitleScene.h"
// #include "dhTutorialScene.h"
#include "dhMapScene.h"
#include "dhBossOneScene.h"
#include "dhWinScene.h"
// #include "dhBossOneScene.h"
#include "dhEndScene.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\YamYamEngine.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\YamYamEngine.lib")
#endif



//#include "..\YamYamEngine\\yaPlayScene.h"
//#include "yaSceneManager.h"
namespace dh
{
	void InitializeScenes()
	{

		//PlayScene* playScene = new PlayScene();
		
		SceneManager::CreateScene<EndScene>(L"EndScene");
		// SceneManager::CreateScene<BossTwoScene>(L"BossTwoScene");
		SceneManager::CreateScene<WinScene>(L"WinScene");
		// SceneManager::CreateScene<TutorialScene>(L"TutorialScene");
		// SceneManager::CreateScene<TitleScene>(L"TitleScene");
		SceneManager::CreateScene<StartScene>(L"StartScene");
		SceneManager::CreateScene<LogoScene>(L"LogoScene");
		
		SceneManager::CreateScene<MapScene>(L"MapScene"); 
		SceneManager::CreateScene<BossOneScene>(L"BossOneScene");

		//SceneManager::CreateScene<LogoScene>(L"LogoScene");
	}
}