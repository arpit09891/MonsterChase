#pragma once

#include"PlayerController.h"


class Player
{
public:

	Player();
	//~Player();
	
	void initPlayer();
	inline void continuingMovement(char choice);
	inline const char* getName() const { return  name; }
	inline GameObject getMovement() const { return movement; } ;
	

private:
	char name[20];
	GameObject movement;
	PlayerController playerController;
};


#include"Player-inl.h"