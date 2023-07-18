#pragma once
#include "..\Engine_SOURCE\yaSceneManager.h"
#include "dhTitleScene.h"
#include "dhCharaScene.h"
#include "yaPlayScene.h"
#include "dhBossScene.h"
#include "dhEndScene.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\YamYamEngine.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\YamYamEngine.lib")
#endif



//#include "..\YamYamEngine\\yaPlayScene.h"
//#include "yaSceneManager.h"
namespace ya
{
	void InitializeScenes()
	{
		//PlayScene* playScene = new PlayScene();
		// 
		SceneManager::CreateScene<EndScene>(L"EndScene");
		SceneManager::CreateScene<BossScene>(L"dhBossScene");
		SceneManager::CreateScene<PlayScene>(L"PlayScene"); 
		SceneManager::CreateScene<CharaScene>(L"dhCharaScene");
		SceneManager::CreateScene<TitleScene>(L"TitleScene");

		// SceneManager::LoadScene(L"TitleScene");
	}
}