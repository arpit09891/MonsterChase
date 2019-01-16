#pragma once
#include"Vector3.h"
#include"SmartPtr.h"
#include"WeakPointer.h"
//class Point2D;
class GameObject;

class Physics {
public:
	Physics(SmartPtr<GameObject> & Player)
	{		
		m_pObject = Player;
		//Player.setCounter(0);
	}

	void Update(Vector3 & i_Force, float & i_dt);
	Vector3 FinalPosition(float i_dt);

	Vector3	 initVelocity;
	Vector3	finalVelocity;
	Vector3 initPosition;
	Vector3 finalPosition;
	Vector3 finalForce;
	Vector3 dF;
	Vector3 acc;

	WeakPointer<GameObject> m_pObject;
	int counter = 0;

};
