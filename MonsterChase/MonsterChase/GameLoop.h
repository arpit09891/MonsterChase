#pragma once
#include"Engine.h"
#include"JobSystem.h"
#include"IJob.h"
#include"SmartPtr.h"
#include"GameObject.h"
#include"Vector3.h"
#include<vector>

class GameLoop : public Engine::JobSystem::IJob{
public:
	GameLoop(SmartPtr<GameObject> i_Player, SmartPtr<GameObject> i_Player2, std::vector<SmartPtr<GameObject>> & i_Enemies):
		IJob("GameLoop"),
		Player(i_Player),
		Player2(i_Player2),
		Enemies(i_Enemies){
	}
	

	void Run();
private:
	Vector3 *Force;
	SmartPtr<GameObject> Player;
	SmartPtr<GameObject> Player2;
	std::vector<SmartPtr<GameObject>> Enemies;
};