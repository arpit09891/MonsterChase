#include"Monster.h"
#include<iostream>

#include<string.h>
#include<conio.h>
#include"Player.h"

int monsterNumber = 0;

Monster::Monster(){
}

Monster::Monster(const Monster & i_other) : movement(i_other.movement) , name(_strdup(i_other.name)), monsterController(i_other.monsterController)
{
	
}

Monster::Monster(Monster && i_other) : movement(i_other.movement), name(i_other.name), monsterController(i_other.monsterController)
{	
	i_other.name = NULL;
}

void Monster::initMonster() {
	/*movement = *(new GameObject());
	monsterController = *(new MonsterController());*/
	printf("\n do you want to name the monsters, press y for yes and n for no");
	char nameChoice;
	nameChoice = _getch();
	char tempName[10];
	char tempName2[10];
	name = new char[100];
	if (nameChoice == 'y')
	{
		printf_s("\n Enter the name of the monster");
		scanf_s("%s", name, 100);
	}
	else
	{
		_itoa_s(nameIncrementer + 1, tempName, 10);
		strcpy_s(tempName2, "m");
		strcat_s(tempName2, tempName);
		int i = 0;
		while (tempName2[i] != '\0') {
			name[i] = tempName2[i];
			i++;
		}
		name[i] = '\0';
		//name = (tempName2);		
	}
	/*else
	{

		_itoa_s(nameIncrementer + 1, tempName, 10);
		strcpy_s(tempName2, "m");
		strcat_s(tempName2, tempName);
		name = _strdup(tempName2);		
	}*/
	nameIncrementer++;
	
	movement.SetPosition(Vector3(rand(),rand(),0));
	
}


void const Monster::monsterMovement(const Player* player)
{
	monsterController.SetGameObject(&movement);
	monsterController.SetFocusObject(&(player->getMovement()));
	monsterController.UpdateGameObject();
	
	if (monsterNumber > 20)
	{
		while (monsterNumber > 20)
		{
			destroyMonster();
		}
	}	
	
	//printf("\n Monster name %s and its position ( %f , %f )", name, movement.getX(), movement.getY());
}

//Monster::~Monster() {
//	
//	delete name;
//}

Monster& Monster:: operator= (const Monster & i_other )
{
	if (name !=NULL)
	{
		delete[] name;
	}
	name = _strdup(i_other.name);	
	movement = i_other.movement;
	monsterController = i_other.monsterController;

	return *this;
}

Monster& Monster:: operator= (Monster && i_other)
{
	std::swap(name, i_other.name);
	std::swap(movement, i_other.movement);
	std::swap(monsterController, i_other.monsterController);

	return *this;
}