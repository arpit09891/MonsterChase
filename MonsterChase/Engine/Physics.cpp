
#include"Physics.h"
#include"Point2D.h"
#include"Timer.h"
#include"GameObject.h"
#include<math.h>
#include"Physics.h"
#include"SmartPtr.h"

//template<class T>
void Physics::Update(Vector3 & i_Force, float & i_dt) {
	if (m_pObject.Acquire().getObject() != nullptr) {
		//Player
		initPosition = m_pObject->GetPosition();
		finalForce = i_Force;
		initVelocity = m_pObject->GetVelocity();
		finalVelocity = m_pObject->GetVelocity() + (i_Force / m_pObject->GetMass())*i_dt;

		

		//drag force calculation
		if (fabs(dF.GetX()) == 0 && fabs(dF.GetY()) == 0) {
			dF = ((finalVelocity * finalVelocity) * (m_pObject->GetMass() * m_pObject->GetDrag()));
			if (finalForce.GetX() > 0)
			{
				dF.SetX(dF.GetX()*-1);
			}
			if (finalForce.GetY() > 0)
			{
				dF.SetY(dF.GetY()*-1);
			}
		}
		float test = fabs(dF.GetY());
		if (fabs(dF.GetX()) > 0 || fabs(dF.GetY()) > 0)
		{
			
		}

		acc = finalForce / m_pObject->GetMass();
		if (fabs(dF.GetX()) >= fabs(finalForce.GetX()))
		{
			finalForce.SetX(0);
			finalVelocity.SetX(0);
			//finalPosition.SetX(0);
			dF.SetX(0);
		}
		else
		{
			finalForce.SetX(finalForce.GetX() + dF.GetX());
			finalVelocity.SetX((0 + acc.GetX())*i_dt);
			//finalVelocity.SetX((initVelocity.GetX() + finalVelocity.GetX()) / 2);
		}

		if (fabs(dF.GetY()) >= fabs(finalForce.GetY())) {
			finalForce.SetY(0);
			finalVelocity.SetY(0);
			//finalPosition.SetY(0);
			dF.SetY(0);
		}
		else
		{
			finalForce.SetY(finalForce.GetY() + dF.GetY());
			finalVelocity.SetY((0 + acc.GetY())*i_dt);
			
		}
		i_Force = finalForce;
		m_pObject->SetVelocity(finalVelocity);
		if (finalVelocity.GetX() == 0 && finalVelocity.GetY() == 0) {
			finalPosition = Vector3(0, 0, 0);
			//m_pObject->SetPosition(finalPosition);
		}
		else
		{
			m_pObject->SetPosition(FinalPosition(i_dt));
		}
	}

}

Vector3 Physics::FinalPosition(float i_dt) {
	//MidPoint Method
		
	finalPosition = initPosition + (finalVelocity)* i_dt;
		
	return finalPosition;
}