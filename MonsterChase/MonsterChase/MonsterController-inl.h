#pragma once

inline bool MonsterController::CheckFocusObject()
{
	/*if (m_pObject->GetPosition().getX() - m_pFocus->GetPosition().getX()< 100 || m_pObject->GetPosition().getY() - m_pFocus->GetPosition().getY() < 100)
	{
		return true;
	}
	else*/
		return false;

}

inline void MonsterController::SetFocusObject(GameObject *i_pObject) {
	m_pFocus = i_pObject;
	//printf("\n Focus Position : %f %f", m_pFocus->GetPosition().getX(), m_pFocus->GetPosition().getY());
	//printf("\n Monster Position Before : %f %f", m_pObject->GetPosition().getX(), m_pObject->GetPosition().getY());
}