#include<Vector3.h>
#include<stdio.h>
#include"Player.h"
#include<conio.h>


Player::Player() {}


void Player::initPlayer()
{
	printf("\n Enter the name of your player");
	scanf_s("%s", name, 10);
	
	movement.SetPosition((Vector3()));
	
	
	/*playerController = *(new PlayerController());*/
}

