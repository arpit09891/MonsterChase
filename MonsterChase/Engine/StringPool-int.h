#pragma once
#include<malloc.h>


inline StringPool * StringPool::Create(size_t i_bytesInPool)
{
	return new StringPool(i_bytesInPool);
}