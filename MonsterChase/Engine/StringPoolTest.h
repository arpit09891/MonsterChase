#pragma once
#include"StringPool.h"


void StringPoolTest() {
	StringPool * stringPool;
	StringPool * temp = temp->Create(1024*1024);
	const char * zombie = temp->add("Zombie");
	const char * zombie2 = temp->add("Zombie");
	const char * monster = temp->add("Monster");
	temp->~StringPool();
}