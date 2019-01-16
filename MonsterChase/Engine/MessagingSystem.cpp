#include"MessagingSystem.h"
#include<vector>

Engine::MessagingSystem * Engine::MessagingSystem::messagingSystem = NULL;

Engine::MessagingSystem::MessagingSystem() {
	PlayerHit.reserve(5);
	/*messagingSystem = new MessagingSystem();*/
}
void Engine::MessagingSystem::RegisterMessageHandler(const char * i_Message, std::function<void(const char*i_Message)> i_Handler)
{
	if (i_Message == "PlayerHit")
	{
		//PlayerHit.reserve(5);
		PlayerHit.push_back(i_Handler);
	}
}

void Engine::MessagingSystem::SendMessageHandler(const char * i_Message)
{
	if (i_Message == "PlayerHit") {
		
		for (int i = 0;i < PlayerHit.size();i++)
		{
			PlayerHit[i]("TestHit!!");
		}
	}
}

Engine::MessagingSystem * Engine::MessagingSystem::Create() {
	if (messagingSystem == NULL)
	{
		messagingSystem = new MessagingSystem();
	
		return messagingSystem;

	}
	else
		return GetInstance();
}

Engine::MessagingSystem * Engine::MessagingSystem::GetInstance() {
	return messagingSystem;
}