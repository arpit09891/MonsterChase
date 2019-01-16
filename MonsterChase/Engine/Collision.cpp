#include"Collision.h"
#include"Matrix.h"
#include"Vector3.h"
#include"CheckFloat-inl.h"
#include<Windows.h>
#include"MacroProfiler.h"

bool Collision::CheckCollision(SmartPtr<GameObject> Player1, SmartPtr<GameObject> Player2, float dt)
{
	//PROFILE_UNSCOPED("CheckCollision");
	CollisionPair collisionPair;
	float o_CollisionTime;
	Vector3 o_CollisionNormal;

	bool SeparationP1toP2 = SearchSeperation(Player1, Player2,dt,o_CollisionTime, o_CollisionNormal);
		
	if (SeparationP1toP2)
	{
		return false;
	}
	else {
		collisionPair.m_CollisionNormal = o_CollisionNormal;
		collisionPair.m_CollisionTime = o_CollisionTime;
		collisionPair.m_CollisionObjects[0] = Player1;
		collisionPair.m_CollisionObjects[1] = Player2;		
	}

	bool SeparationP2toP1 = SearchSeperation(Player2, Player1, dt, o_CollisionTime, o_CollisionNormal);

	if (SeparationP2toP1)
	{
		return false;
	}
	else {
		collisionPair.m_CollisionNormal = o_CollisionNormal;
		collisionPair.m_CollisionTime = o_CollisionTime;
		collisionPair.m_CollisionObjects[0] = Player2;
		collisionPair.m_CollisionObjects[1] = Player1;
	}
	AfterCollision(collisionPair);
	return true;

}

bool Collision::SearchSeperation(SmartPtr<GameObject> Player1, SmartPtr<GameObject> Player2, float dt, float & o_CollisionTime, Vector3 & o_CollisionNormal)
{
	//for player 1
	Matrix mRot1 = mRot1.CreateZRotation(0);
	Matrix mTrans1 = mTrans1.CreateTransaltion(Player1->GetPosition());
	Matrix mP1toWorld = mTrans1*mRot1;

	//for player2
	Matrix mRot2 = mRot2.CreateZRotation(0);
	Matrix mTrans2 = mTrans2.CreateTransaltion(Player2->GetPosition());
	Matrix mP2toWorld = mTrans2*mRot2;
	Matrix mWorldtoP2 = mP2toWorld.GetInverse();

	//P1 to P2
	Matrix mP1ToP2 = mWorldtoP2*mP1toWorld;
		
	//Checking Seperation in Player2 

	Vector4 P1CenterInP2 = mP1ToP2 * Vector4(Player1->GetBB().Center, 1.0f);
	Vector4 P1ExtendsXinP2 = mP1ToP2 * Vector4(Player1->GetBB().Extends.GetX(), 0.0f, 0.0f, 0.0f);
	Vector4 P1ExtendsYinP2 = mP1ToP2 * Vector4(0.0f, Player1->GetBB().Extends.GetY(), 0.0f, 0.0f);
	
	//Relative Velocity
	Vector3 VelP1RelToP2 = Player1->GetVelocity() - Player2->GetVelocity();
	Vector4 VelP1InP2 = mWorldtoP2 * Vector4(VelP1RelToP2, 0.0f);
		
	//for x axis
	float P1ProjectionOntoP2_X = fabs(P1ExtendsXinP2.GetX()) + fabs(P1ExtendsYinP2.GetX());
	float P2ExtentsX = Player2->GetBB().Extends.GetX() + P1ProjectionOntoP2_X;
	float P2LeftX = Player2->GetBB().Center.GetX() - P2ExtentsX;
	float P2RightX = Player2->GetBB().Center.GetX() + P2ExtentsX;

	float DCloseX = P2LeftX - P1CenterInP2.GetX();
	float DOpenX = P2RightX - P1CenterInP2.GetX();

	float tCloseX = DCloseX / VelP1InP2.GetX();
	float tOpenX = DOpenX / VelP1InP2.GetX();
	int flagZeroVelocityX = 0;
	
	bool SeperatedX = false;

	if (IsZero(VelP1InP2.GetX())) {
		flagZeroVelocityX = 1;
		if (P2LeftX <= P1CenterInP2.GetX() && P2RightX >= P1CenterInP2.GetX())
		{
			//there is overlap in axis but still need to check seperation in other axis
		}
		else{
			//there is never gonna be collision in either axis
			//return true;
		}			
			
	}
	//tOpen and tClose logic for X axis

	if (flagZeroVelocityX == 0) {
		if (tOpenX < tCloseX) {
			float tempTime;
			tempTime = tOpenX;
			tOpenX = tCloseX;
			tCloseX = tempTime;
			//swap topen and tclose
		}
		if (tOpenX < 0) {
			SeperatedX = true;
			//Collision occured in past and there is not collision for entire frame
		}

		if (tCloseX > dt) // Seperation will close after this frame so THERE IS no collision in this frame
		{
			SeperatedX = true;
		}
	}
	//bool SeperatedY = false; //= fabs(P1CenterInP2.GetX() - Player2->GetBB().Center.GetX()) > (Player2->GetBB().Extends.GetX() + P1ProjectionOntoP2_X );
	
	//for y axis on to P2
	float P1ProjectionOntoP2_Y = fabs(P1ExtendsXinP2.GetY()) + fabs(P1ExtendsYinP2.GetY());
	
	float P2ExtentsInY = Player2->GetBB().Extends.GetY() + P1ProjectionOntoP2_Y;

	float P2LeftY = Player2->GetBB().Center.GetY() - P2ExtentsInY;
	float P2RightY = Player2->GetBB().Center.GetY() + P2ExtentsInY;

	float DCloseY = P2LeftY - P1CenterInP2.GetY();
	float DOpenY = P2RightY - P1CenterInP2.GetY();

	float tCloseY = DCloseY / VelP1InP2.GetY();
	float tOpenY = DOpenY / VelP1InP2.GetY();
	int flagZeroVelocityY = 0;

	//for Y axis
	bool SeperatedY = false;

	if (IsZero(VelP1InP2.GetY())) {
		flagZeroVelocityY = 1;
		if (P2LeftY <= P1CenterInP2.GetY() && P2RightY >= P1CenterInP2.GetY())
		{
			//there is overlap in axis but still need to check seperation in other axis
		}
		else {
			//there is never gonna be collision in either axis
			//return true;
		}

	}
	//tOpen and tClose logic for Y axis

	if (flagZeroVelocityY == 0) {
		if (tOpenY < tCloseY) {
			float tempTime;
			tempTime = tOpenY;
			tOpenY = tCloseY;
			tCloseY = tempTime;
			//swap topen and tclose
		}
		if (tOpenY < 0) {
			SeperatedY = true;
			//Collision occured in past and there is not collision for entire frame
		}

		if (tCloseY > dt) // Seperation will close after this frame so THERE IS no collision in this frame
		{
			SeperatedY = true;
		}
	}	
	if (SeperatedX || SeperatedY)
	{
		return true;
	}
	float tOpen;
	float tClose;
	Vector4 normalVector = Vector4();
	//calculating earliest topen
	if (tOpenX < tOpenY) {
		tOpen = tOpenX;
	}
	else {
		tOpen = tOpenY;
	}
	//Calculating latest tclose
	if (tCloseX > tCloseY) {
		tClose = tCloseX;
		normalVector = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
	}
	else {
		tClose = tCloseY;
		normalVector = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
	}
	if (tOpen > tClose) {
		//there is collision
		o_CollisionTime = tClose;
		normalVector = normalVector * mP2toWorld;
		o_CollisionNormal = Vector3(normalVector.GetX(), normalVector.GetY(), normalVector.GetZ());
		return false;
	}
	else {
		
		return true;
	}
}

void Collision::AfterCollision(CollisionPair & collisionPair)
{
	//Calculate Momentum
	Vector3 postCollisionVel1;
	Vector3 postCollisionVel2;
	Vector3 normalObject1;
	Vector3 normalObject2;

	float massDifference = (collisionPair.m_CollisionObjects[0]->GetMass() - collisionPair.m_CollisionObjects[1]->GetMass());
	float totalMass = (collisionPair.m_CollisionObjects[0]->GetMass() + collisionPair.m_CollisionObjects[1]->GetMass());

	postCollisionVel1 = ((massDifference / totalMass) * collisionPair.m_CollisionObjects[0]->GetVelocity()) +
		(((2 * collisionPair.m_CollisionObjects[1]->GetMass()) / totalMass) * collisionPair.m_CollisionObjects[1]->GetVelocity());
	collisionPair.m_CollisionObjects[0];

	postCollisionVel2 = (((-1 * massDifference) / totalMass) * collisionPair.m_CollisionObjects[1]->GetVelocity()) +
		((2 * collisionPair.m_CollisionObjects[0]->GetMass() / totalMass) * collisionPair.m_CollisionObjects[0]->GetVelocity());
	collisionPair.m_CollisionObjects[0];

	normalObject1 = collisionPair.m_CollisionNormal;
	normalObject2 = -1 * normalObject1;

	postCollisionVel1 = -2 * (postCollisionVel1*normalObject1) * normalObject1 + postCollisionVel1;
	postCollisionVel2 = -2 * (postCollisionVel2*normalObject2) * normalObject2 + postCollisionVel2;

	collisionPair.m_CollisionObjects[0]->SetVelocity(postCollisionVel1);
	collisionPair.m_CollisionObjects[1]->SetVelocity(postCollisionVel2);
}

void Collision::PlayerHit(const char * i_pMessage)
{
	OutputDebugStringA(i_pMessage);
}

//Page36
//part 5 26:48
