#pragma once
#include"Vector3.h"

struct BoundingBox {

	Vector3 Center = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 Extends = Vector3(0.0, 0.0f, 0.0f);

};

class GameObject {
	
public:
	GameObject() {};
	GameObject(const GameObject & i_other) :
		m_Position(i_other.m_Position),m_Velocity(i_other.m_Velocity), mass(i_other.mass),drag(i_other.drag) {}
	inline Vector3 GetPosition() const;
	inline Vector3 GetVelocity() const;
	inline float GetMass() const;
	inline float GetDrag() const;
	inline int GetAlive() const;
	inline BoundingBox GetBB() const;
	
	inline void SetPosition(Vector3 & i_Position);
	inline void SetVelocity(Vector3 & i_Velocity);
	//inline void SetMass(float & i_mass);
	inline void SetDrag(float & i_mass);
	inline void SetBB(BoundingBox & i_BB);
	inline void SetAlive(int i_Alive);

private:
	
	Vector3 m_Position = Vector3(0.0f,0.0f,0.0f);
	Vector3 m_Velocity;
	float mass = 1.0f;
	float drag = 0.01f;
	int Alive = 0;
	BoundingBox bb;
};

#include"GameObject-int.h"
