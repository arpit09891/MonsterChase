#pragma once


#include"Player.h"
#include"MonsterController.h"

#include<stdio.h>
static int nameIncrementer = 0;
extern int monsterNumber;
static int loopCounter = 0;

class Point2D;
class Monster {

public: 
	//constructors
	Monster();	
	Monster(const Monster & i_other);
	Monster(Monster && i_other);
/*
	~Monster();*/
	//member functions
		
	void initMonster();
	inline void destroyMonster();
	const void monsterMovement(const Player* player);
	inline void displayMonster();
	GameObject getMovement() { return movement; };
	inline const char* getName() const { return name; };

	inline float const getMovementX();
	inline float const getMovementY();
	Monster& operator=(const Monster & i_other);
	Monster& operator=(Monster && i_other);


	//int getMonsterNumber();
	//void setMonsterNumber(int number);

private:
	char* name;
	GameObject movement;
	MonsterController monsterController;
	
};

#include"Monster-inl.h"