#pragma once


inline float const Monster::getMovementX() {
	Vector3 temp = movement.GetPosition();
	return temp.GetX();
}

inline float const Monster::getMovementY() {
	Vector3 temp = movement.GetPosition();
	return temp.GetY();
}

inline void Monster::destroyMonster()
{
	delete this;
	nameIncrementer--;
	monsterNumber--;
	
}

inline void Monster::displayMonster() {
	printf("\n Monster name %s and its position ( %f , %f )", name, movement.GetPosition().GetX(), movement.GetPosition().GetY());
}