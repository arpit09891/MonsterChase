#include"Monster.h"
#include<vector>
void CheckConstructorsTestCase() {


	int numMon = 10;
	int regMon = 5;
	Monster sample;
	printf_s("\n Expected: Calling regular constructor.\n");
	sample.initMonster();
	// testing copy constructor, works fine.
	Monster temp(sample);
	printf_s("Expected: Calling copy constructor.\n");

	printf_s("Expected: Sample: %s; Actual: %s\n",sample.getName(), temp.getName());
	
	// testing copy assignment operator, works fine.
	Monster temp2;
	
	temp2 = sample;
	printf_s("Expected: Calling copy assignment operator.\n");
	printf_s("Expected: Sample: %s ; Actual: %s\n", sample.getName(), temp2.getName());

	Monster sample2;
	printf_s("Expected: Calling move constructor.\n");
	sample2.initMonster();

	// testing move constructor, works fine.
	Monster moveMon(std::move(sample2));
	printf_s("Expected: Calling move constructor.\n");
	printf_s("Expected: MoveSample: %s; Actual: %s\n", sample2.getName(), moveMon.getName());

	Monster sample3;
	printf_s("Expected: move assignment operator.\n");
	sample3.initMonster();

	// testing move assignment operator, works fine.
	Monster moveAss;
	moveAss = std::move(sample3);
	printf_s("Expected: Calling move assignment operator.\n");
	printf_s("Expected: MoveSampleAssignment: %s; Actual: %s\n",sample3.getName(), moveAss.getName());

	// testing copy constructor and move constructor in vector, works fine.
	std::vector<Monster> mons;
	mons.reserve(numMon);
	for (int i = 0; i < regMon; i++)
	{
		mons.push_back(sample);
		printf_s("Expected: Calling copy constructor.\n");
	}
	for (int i = regMon; i < numMon; i++)
	{
		mons.push_back(std::move(sample));
		printf_s("Expected: Calling move constructor.\n");
	}
}
