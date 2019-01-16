#pragma once
#include<stdint.h>
#include<stdio.h>

inline const void HeapManager::CheckMemory() {
	if (startOfMemory == pFreeMemoryList->m_pBlockBase)
		printf("Everything is fine");
	printf("\n \n %p", startOfMemory);
}

inline bool HeapManager::_contains(const void *pointer) const
{
	return(pointer >= startOfMemory && pointer <= endOfMemory);
}

inline bool HeapManager::_isAllocated(const void * pointer) const
{
	BlockDescriptor * temp = pOutstandingAllocationList;
	if (temp == NULL)
	{
		return false;
	}
	else {
		while (temp != NULL)
		{

			if (pointer >= temp->m_pBlockBase && pointer < reinterpret_cast< int8_t *>(temp->m_pBlockBase) + temp->m_sizeBlock)
			{
				return true;
			}
			temp = temp->m_pNext;
		}

		return false;
	}

}

