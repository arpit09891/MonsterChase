#pragma once
#include"GameObject.h"
#include"Vector3.h"

inline Vector3 GameObject::GetPosition() const { return m_Position; }
inline Vector3 GameObject::GetVelocity() const { return m_Velocity; }
inline void GameObject::SetPosition(Vector3 & i_Position) { m_Position = i_Position; }
inline void GameObject::SetVelocity(Vector3 & i_Velocity) { m_Velocity = i_Velocity; }

inline float GameObject::GetMass() const { return mass; }
//inline void GameObject::SetMass(float & i_Mass) { mass = i_Mass; }

inline float GameObject::GetDrag() const { return drag; }
inline int GameObject::GetAlive() const
{
	return Alive;
}
inline BoundingBox GameObject::GetBB() const
{
	return bb;
}
inline void GameObject::SetDrag(float & i_drag) { drag = i_drag; }

inline void GameObject::SetBB(BoundingBox & i_BB) 
{
	bb.Center = i_BB.Center;
	bb.Extends = i_BB.Extends;
}

inline void GameObject::SetAlive(int i_Alive)
{
	Alive = i_Alive;
}

