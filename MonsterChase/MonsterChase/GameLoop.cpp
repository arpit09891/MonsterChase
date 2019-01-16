#include"GameLoop.h"
#include"Game.h"
#include"Vector3.h"
#include"SmartPtr.h"
#include"GameObject.h"
#include"Physics.h"
#include"Collision.h"
#include"Timer.h"
void GameLoop::Run() {
	
	long long Time = Timer::GetCounter();
	bool bQuit = false;
	Force = new Vector3(0, 0, 0);
	Physics physics = Physics(Player);
	Collision collision = Collision();
	bool ContinueGame = false;
	
	do
	{

		long long Difference = Timer::GetCounter() - Time			;
		float DifferentFloat = static_cast<float>(Difference);
		DifferentFloat /= 1000000;
		
		const int MESSAGE_BUFFER_SIZE = 100;
		char msgbuff[MESSAGE_BUFFER_SIZE];
		sprintf_s(msgbuff, "\nExecuting function %f", DifferentFloat);
		OutputDebugStringA(msgbuff);

		ContinueGame = false;
		GLib::Service(bQuit);
		if (!bQuit) {
			Game::Run(*(Force), Player, physics, Player2,collision, Enemies);
		}
		
		for (int i = 0; i < 8;i++)
		{
			if (Enemies[i]->GetAlive() == 1)
			{
				ContinueGame = true;
			}
		}
		if (DifferentFloat >= 50)
		{
			ContinueGame = false;
		}
	} while (bQuit == false && !ShutdownRequested() && ContinueGame);
}