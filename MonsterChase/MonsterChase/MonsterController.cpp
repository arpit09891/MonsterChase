#include"Monster.h"
#include"IGameObjectController.h"


void MonsterController::UpdateGameObject() {

	Vector3 Direction;
	
	if (CheckFocusObject())
	{
		Direction = m_pFocus->GetPosition() - m_pObject->GetPosition();
		//Direction.Normalize();
	}
	else
	{
		Direction = GetWanderDirection();
	}
	m_pObject->SetPosition(m_pObject->GetPosition() + Direction);
	//printf("\n Monster Position After : %f %f", m_pObject->GetPosition().getX(), m_pObject->GetPosition().getY());
}
//
const Vector3 MonsterController::GetWanderDirection()
{
	if (loopCounter % 5 == 0)
	{
		if (movementHelper == 0)
			movementHelper = 1;
		else
			movementHelper = 0;
	}
	if (movementHelper == 0)
		return (Vector3(1,1,0));
	else
		return (Vector3(-1, -1,0));
}


