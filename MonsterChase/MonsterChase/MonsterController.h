#pragma once

//#include "IGameObjectController.h"
class IGameObjectController;
class GameObject;

class MonsterController : public IGameObjectController
{
public:
	inline void SetGameObject(GameObject *i_pObject) override { m_pObject = i_pObject; }
	inline void SetFocusObject(GameObject *i_pObject);
	inline bool CheckFocusObject();
	void UpdateGameObject() override;
	const Vector3 GetWanderDirection();
	
private:
	GameObject *m_pObject;
	GameObject *m_pFocus;
	int movementHelper = 0;
};

#include"MonsterController-inl.h"