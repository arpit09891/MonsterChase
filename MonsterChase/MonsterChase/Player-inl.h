#pragma once

inline void Player::continuingMovement(char choice) {

	//Added Controller here
	printf("\n Enter your choice");
	playerController.SetGameObject(&movement);
	playerController.UpdateGameObject();
	GameObject tempPosition = getMovement();
	
	//printf("\n The present position of %s is :  %f , %f", name, tempPosition.GetPosition().getX(), tempPosition.GetPosition().getY());

}


