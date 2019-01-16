#pragma once
#include"Engine.h"
//#include"HashedString.h"
#include<vector>
#include<functional>
namespace Engine {
	class MessagingSystem
	{

	public:

		//typedef void(*MessageHandler_t)(const Engine::HashedString & i_Message);
		void RegisterMessageHandler(const char * i_Message, std::function<void(const char*i_Message)> i_Handler);
		void SendMessageHandler(const char * i_Message);
		static MessagingSystem * Create();
		static MessagingSystem * GetInstance();

	private:
		static MessagingSystem * messagingSystem;
		MessagingSystem();
		std::vector< std::function<void(const char*)>>PlayerHit;

	};
}