#include <stdio.h>
#include <stdint.h>
#include <Windows.h>
#include"Engine.h"
#include"Game.h"
#include"StringPoolTest.h"
#include"LuaTestClass.h"
#include<vector>

//#if defined _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include"GameLoop.h"
#include"ProcessFile.h"
#include"GameObject.h"
//#endif // _DEBUG



int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	//changed filters
	#if defined _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	
	if (Engine::StartUp())
	{
		std::vector<SmartPtr<GameObject>> Enemies;
		Enemies.reserve(10);
		for (int i = 0; i < 18;i++) {
			Enemies.push_back(SmartPtr<GameObject>(new GameObject()));
		}
		SmartPtr<GameObject> Player(new GameObject());
		SmartPtr<GameObject> Player2(new GameObject());
		if (Game::StartUp(i_hInstance, i_hPrevInstance, i_lpCmdLine, i_nCmdShow, Player, Player2, Enemies)) {
			//StringPoolTest();
			Engine::JobSystem::CreateQueue("Default", 2);
			ProcessFile * pProcessFile = new ProcessFile("data\\Player.Lua");
			Engine::JobSystem::RunJob(*pProcessFile, "Default");
			GameLoop * gL = new GameLoop(Player,Player2, Enemies);
			//Engine::JobSystem::RunJob(*gL, "Default");
			gL->Run();
			
		}
		Game::ShutDown();
		Engine::ShutDown();
	}	
}

