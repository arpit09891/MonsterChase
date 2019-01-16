#pragma once
#include<stdint.h>

class StringPool
{
public:
	inline static StringPool * Create(size_t i_bytesInPool);
	~StringPool();

	// find string in pool - adding it if it's not there
	const char * add(const char * i_pString);
	// find string in pool - don't add if it's not there
	const char * find(const char * i_pString);

private:
	void * startOfPool;
	size_t lengthOfPool;
	void * startOfAvailablePool;
	StringPool(size_t i_sizePool);
	
};


#include"StringPool-int.h"