#include"StringPool.h"
#include<malloc.h>
#include<string.h>


StringPool::StringPool(size_t i_sizePool) {
	lengthOfPool = i_sizePool;
	startOfPool = malloc(i_sizePool);
	startOfAvailablePool = startOfPool;	
}



//checking

const char * StringPool::add(const char * i_pString)
{
	const char * tempString = find(i_pString);
	int * stringLengthPool = reinterpret_cast<int*>(startOfAvailablePool);
	stringLengthPool++;
	char* tempPoolString = reinterpret_cast<char*>(stringLengthPool);
	//tempPoolString++;
	stringLengthPool = reinterpret_cast<int*>(startOfAvailablePool);
	if (tempString == nullptr)
	{
		*stringLengthPool = strlen(i_pString);
		while (*i_pString != '\0')
		{
			* tempPoolString = *i_pString;
			i_pString++;
			tempPoolString++;
		}
		*tempPoolString = '\0';
		stringLengthPool++;
		char* createdString = reinterpret_cast<char*>(stringLengthPool);
		return createdString;
	}
	return nullptr;
}

const char * StringPool::find(const char * i_pString)
{
	//return nullptr;
	size_t length =  strlen(i_pString);
	const char * tempI_pString = i_pString;
	char * start = reinterpret_cast<char*>(startOfPool);
	int * tempStartInt = reinterpret_cast<int *>(startOfPool);
	tempStartInt++;
	char * tempStartChar = reinterpret_cast<char *>(tempStartInt);
	
	//tempStartChar++;
	
	int counter = 0;
	int temp = *tempStartInt;
	//int poolLength = reinterpret_cast<int>(*tempStartInt);
	while (start != start + lengthOfPool )
	{
		tempStartInt = reinterpret_cast<int *>(start);
		counter = 0;
		if (*tempStartInt < 0)
		{
			startOfAvailablePool = reinterpret_cast<void*>(tempStartInt);
			return nullptr;
		}		
		else if (*tempStartInt == length)
		{
			while (*tempI_pString != '\0') {
				if (*tempI_pString == *tempStartChar)
				{
					counter++;
				}
				else {
					break;
				}
				tempI_pString++;
				tempStartChar++;
			}
			if (counter == length)
			{
				tempStartInt++;
				char *foundString = reinterpret_cast<char*>(tempStartInt);
				return foundString;
			}
		}
		//start = +4;
		start = start + *tempStartInt + 4;
		
	}
}


StringPool::~StringPool() {
	free(startOfPool);
}
