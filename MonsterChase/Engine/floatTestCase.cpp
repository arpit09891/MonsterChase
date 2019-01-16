#include"CheckFloat-inl.h"
#include"Debug.h"
#include<stdio.h>

void unitTestcase()
{
	//Check for valid float
	bool test = IsNaN(nanf(""));
	assert(test, "This is not a number");
	//Check for NaN
	bool test2 = IsNaN(1.0f);
	assert(test2, "This is not a number");
	//Check with epsilon
	bool test3 = AreAboutEqual(5.0f, 5.0f);
	assert(test3, "These numbers are not equal");
	//Check with epsilon second test
	bool test4 = AreAboutEqual(5.0f, 3.0f);
	assert(test4, "These numbers are not equal");
}