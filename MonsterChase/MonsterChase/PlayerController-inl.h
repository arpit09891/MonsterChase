#pragma once

inline void PlayerController::UpdateGameObject() {
	if (m_pObject)
	{
		Vector3 Direction = GetMovementDirectionFromUserInput();
		m_pObject->SetPosition(m_pObject->GetPosition() + Direction);
		Vector3 tempPosition = m_pObject->GetPosition();
		//printf("\n The present position of player is :  %f , %f", tempPosition.getX(), tempPosition.getY());
	}
}