#pragma once
// BlockAllocator.cpp : Defines the entry point for the console application.

#include<malloc.h>


#include"FSAManager.h"

//class FSA;

struct BlockDescriptor {

	void * m_pBlockBase;
	size_t m_sizeBlock;
	BlockDescriptor * m_pNext;
	size_t m_id = 0;
	
};

struct FSAInitData
{
	size_t sizeBlock;
	int numBlocks;
};

class HeapManager
{
	void* startOfMemory = NULL;
	void* endOfMemory = NULL;
	size_t numberOfAvailDescriptors;
	
public:
		FSAInitData FSASizes[3];

		const void _clearFreeMemoryList();
		bool create(const size_t i_sizeMemory, const size_t i_numDescriptors);
		void * _alloc(const size_t i_size, size_t align);
		bool _deAlloc(const void* addr);
		const void Free(BlockDescriptor* BD);
		const void PrintBlockDescriptors();
		inline const void CheckMemory();
		inline bool _contains(const void *pointer) const;
		inline bool _isAllocated(const void * pointer) const;
		
		~HeapManager();
	BlockDescriptor* pFreeMemoryList;
	BlockDescriptor* pOutstandingAllocationList;
	BlockDescriptor* pFreeDescriptorList;
};

static HeapManager * pDefaultHeap = NULL;

void makeDefaultHeap(HeapManager * pHeapManager);


#include "BlockAllocator-inl.h"
