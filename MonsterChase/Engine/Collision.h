#pragma once
#include"Vector3.h"
#include"SmartPtr.h"
#include"GameObject.h"
#include"WeakPointer.h"
#include"MessagingSystem.h"
#include<functional>

using namespace std;

struct CollisionPair {
	float m_CollisionTime;
	Vector3 m_CollisionNormal;	
	WeakPointer<GameObject> m_CollisionObjects[2];
};

class Collision {
	

public:
	Collision() {
		gMessaging = gMessaging->GetInstance();
		gMessaging->RegisterMessageHandler("PlayerHit", std::bind(&Collision::PlayerHit, this, std::placeholders::_1));
	}
	bool CheckCollision(SmartPtr<GameObject> Player1, SmartPtr<GameObject> Player2, float dt);
	bool SearchSeperation(SmartPtr<GameObject> Player1, SmartPtr<GameObject> Player2, float dt, float & o_CollisionTime, Vector3 & o_CollisionNormal);
	
	void AfterCollision(CollisionPair & collisionPair);
	void PlayerHit(const char* i_pMessage);

	
private:
		Engine::MessagingSystem *gMessaging;
};