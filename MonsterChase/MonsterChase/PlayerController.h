#pragma once
#include"IGameObjectController.h"
#include<stdio.h>
#include<conio.h>
#include"Vector3.h"

class PlayerController : public IGameObjectController
{
public:
	inline void SetGameObject(GameObject *i_pObject) override { m_pObject = i_pObject; }

	inline void UpdateGameObject() override;
	Vector3 GetMovementDirectionFromUserInput();
	

private:
	GameObject *m_pObject;
};

#include "PlayerController-inl.h"