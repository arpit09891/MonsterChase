#include"BlockAllocator.h"
#include<stdio.h>
#include<conio.h>
#include"Debug.h"
#include<vector>
#include<algorithm>
#include<stddef.h>
#include"FSA.h"
extern void BitArray_UnitTest();

using namespace FSAManager;

bool HeapManager::create(size_t i_sizeMemory, size_t i_numDescriptors)
{
	startOfMemory = _aligned_malloc(i_sizeMemory, 4);
	numberOfAvailDescriptors = i_numDescriptors;
	size_t descriptorMemory = (sizeof(BlockDescriptor)*i_numDescriptors);
	void * tempBDstartpoint = static_cast<int8_t*>(startOfMemory) + (i_sizeMemory - descriptorMemory);
	
	endOfMemory = tempBDstartpoint;
	BlockDescriptor *blockDescriptor = static_cast<BlockDescriptor*>(tempBDstartpoint);
	pFreeDescriptorList = blockDescriptor;
		
	for (size_t i = 0; i < i_numDescriptors - 1; i++) {
		blockDescriptor = blockDescriptor + 1;
		
		blockDescriptor->m_pBlockBase = nullptr;
		blockDescriptor->m_sizeBlock = 0;
		blockDescriptor->m_pNext = nullptr;
	#ifdef _DEBUG
		blockDescriptor->m_id = i + 1;
	#endif//DEBUG
		
		
		pFreeDescriptorList->m_pNext = blockDescriptor;
		pFreeDescriptorList = pFreeDescriptorList->m_pNext;
	}	
	pFreeDescriptorList->m_pNext = nullptr;

	pFreeMemoryList = static_cast<BlockDescriptor*>(tempBDstartpoint);
	pFreeMemoryList->m_pBlockBase = startOfMemory;

	pFreeMemoryList->m_sizeBlock = i_sizeMemory - descriptorMemory;
	
#ifdef _DEBUG
	pFreeMemoryList->m_id = 0;
#endif//DEBUG
	pFreeMemoryList->m_pNext = nullptr;

	pOutstandingAllocationList = nullptr;

	pFreeDescriptorList = static_cast<BlockDescriptor*>(tempBDstartpoint);
	pFreeDescriptorList++;
	numberOfAvailDescriptors--;

	CreateHeaps(pDefaultHeap);
	if (pFreeDescriptorList)
		return true;
	else
		return false;

}

void * HeapManager::_alloc(const size_t i_size, size_t alignSize)
{

	//checking Memory Logic --> Start
	
	if (numberOfAvailDescriptors == 0)
	{
		printf("not enough descriptors");
		return nullptr;
	}
	//GaurdBanding and Alignment
	size_t extraSize;
	if (i_size % 4 != 0)
	{
		extraSize = 8 + 4 - (i_size % 4);
	}
	else
	{
		extraSize = 8;
	}
	

	extraSize += i_size;

	if (extraSize == 0 )
	{
		printf("requested memory size is not adequate.");
		return nullptr;
	}
	uint8_t counter = 0;
	BlockDescriptor* pTempFreeMemoryList = pFreeMemoryList;
	
	//Block from memory list 
	BlockDescriptor* pSelectedAllocator;
	BlockDescriptor* pTempPrev;
	BlockDescriptor* pAllocatedDescriptor;
	
	// checking memory availability in deallocated descriptors and selecting suitable descriptor
	
	while (pTempFreeMemoryList != NULL)
	{
		if (extraSize == pTempFreeMemoryList->m_sizeBlock)
		{
			pSelectedAllocator = pTempFreeMemoryList;
			counter++;
			break;
		}
		if (extraSize < pTempFreeMemoryList->m_sizeBlock)					
		{
			if(counter==0)
				pSelectedAllocator = pTempFreeMemoryList;

			else if (pSelectedAllocator->m_sizeBlock > pTempFreeMemoryList->m_sizeBlock ) {
				if(pTempFreeMemoryList->m_sizeBlock > (extraSize+10))
					pSelectedAllocator = pTempFreeMemoryList;
			}
			counter++;
		}		
		pTempFreeMemoryList = pTempFreeMemoryList->m_pNext;
	}

	pTempFreeMemoryList = pFreeMemoryList;	
	
	//No Memory Available
	if (counter == 0)
	{
		printf_s("Not enough memory to allocate");
		return nullptr;
	}
	//obtaining address of previous node SelectedAllocator
	else
	{
		while (pTempFreeMemoryList != pSelectedAllocator) {
			pTempPrev = pTempFreeMemoryList;
			pTempFreeMemoryList = pTempFreeMemoryList->m_pNext;
		}
	}

	BlockDescriptor * pTempOutStanding = nullptr;

	// Checking Memory Logic --> End
//-----------------------------------------------------------------------------------------------------------------


	//Allocating Logic

	//Breaking the block if block size is more than greater by 10 for required size.
	
	if (pSelectedAllocator->m_sizeBlock >= extraSize + 10)
	{
		pSelectedAllocator->m_sizeBlock -= extraSize;

		pFreeDescriptorList->m_sizeBlock = extraSize;
		pFreeDescriptorList->m_pBlockBase = static_cast<int8_t*>(pSelectedAllocator->m_pBlockBase) + pSelectedAllocator->m_sizeBlock;

		//Adding required info in available BD from free descriptor list
		
		pAllocatedDescriptor = pFreeDescriptorList;
		pFreeDescriptorList = pFreeDescriptorList->m_pNext;
		pAllocatedDescriptor->m_pNext = nullptr;
		numberOfAvailDescriptors--;
	}
	else
	{
		pTempPrev->m_pNext = pSelectedAllocator->m_pNext;
		pAllocatedDescriptor = pSelectedAllocator;
		pAllocatedDescriptor->m_pNext = nullptr;

	}
	
	//Moving BD from free Discriptor List to Outstanding List
	
	if(pOutstandingAllocationList != nullptr){
		pTempOutStanding = pOutstandingAllocationList;
		while (pTempOutStanding->m_pNext != nullptr)
		{
			pTempOutStanding = pTempOutStanding->m_pNext;
		}

		pTempOutStanding->m_pNext = pAllocatedDescriptor;
		pTempOutStanding = pTempOutStanding->m_pNext;
	}	
		//when outstanding list is null
		else {
			pOutstandingAllocationList = pAllocatedDescriptor;
			pTempOutStanding = pAllocatedDescriptor;
		}
	
	
	//GaurdBanding and Aligning
	int8_t* pGaurdBand = static_cast<int8_t*>(pAllocatedDescriptor->m_pBlockBase);
	for (int8_t i = 0; i < 4; i++)
	{
		*pGaurdBand = 'G';
		pGaurdBand++;
	}
	pGaurdBand += i_size;
	for (int8_t i = 0; i < 4; i++)
	{
		*pGaurdBand = 'G'; //71
		pGaurdBand++;
	}
	void* newTemp;
	newTemp = static_cast<int8_t*>(pTempOutStanding->m_pBlockBase) + 4;
	//PrintBlockDescriptors();
	return newTemp;

}

const void HeapManager::PrintBlockDescriptors()
{
		BlockDescriptor* tempFreeDL = pFreeDescriptorList;
		BlockDescriptor* freeMemory = pFreeMemoryList;
		BlockDescriptor* tempOutstandingL = pOutstandingAllocationList;
		
		size_t FreeDescriptors, freeMemoryList, UsedDescriptors, MemoryDiscriptors;
		FreeDescriptors = 0;
		UsedDescriptors = 0;
		MemoryDiscriptors = 0;
		
	/*	while (tempFreeDL->m_pNext != nullptr)
		{
			FreeDescriptors++;
			printf("\n Free Discriptor Id : %d Size %d Memory Adress %p",tempFreeDL->m_id, tempFreeDL->m_sizeBlock, tempFreeDL->m_pBlockBase );
			tempFreeDL = tempFreeDL->m_pNext;			
		}
		printf("\n Free Descriptors : %d", FreeDescriptors);
*/
		while (tempOutstandingL != NULL)
		{
			UsedDescriptors++;
#ifdef _DEBUG
			printf_s("\n Used Discriptor Id : %d", tempOutstandingL->m_id);
#endif//DEBUG
			printf(" \n Size %d Memory Adress %p", tempOutstandingL->m_sizeBlock, tempOutstandingL->m_pBlockBase);
			tempOutstandingL = tempOutstandingL->m_pNext;
		}
		printf("\n Used Descriptors : %d", UsedDescriptors);
		printf("\n Memory Available : %d", freeMemory->m_sizeBlock);


		while (freeMemory != NULL)
		{
			MemoryDiscriptors++;
	#ifdef _DEBUG
			printf_s("\n  Memory Discriptor Id : %d", freeMemory->m_id);
	#endif//DEBUG
			printf_s(" \n Size %d  Memory Adress %p", freeMemory->m_sizeBlock, freeMemory->m_pBlockBase);
			freeMemory = freeMemory->m_pNext;
		}
}

bool HeapManager::_deAlloc(const void* addr)
{
	BlockDescriptor* temp = pOutstandingAllocationList;
	BlockDescriptor* tempOutstandingL = pOutstandingAllocationList;
	BlockDescriptor* tempFreeMemory = pFreeMemoryList;
	void* checker;
	
	while (tempFreeMemory->m_pNext != NULL)
	{
		tempFreeMemory = tempFreeMemory->m_pNext;
	}

	if (pOutstandingAllocationList == NULL)
	{
		printf_s("Memory is Free, nothing to free.");
		return false;
	}
	// Last element of oustanding list
	else if (pOutstandingAllocationList->m_pNext == nullptr)
	{
		if (addr >= tempOutstandingL->m_pBlockBase && addr < reinterpret_cast<int8_t *>(tempOutstandingL->m_pBlockBase) + tempOutstandingL->m_sizeBlock) {
			tempFreeMemory->m_pNext = tempOutstandingL;
			tempFreeMemory = tempFreeMemory->m_pNext;
			pOutstandingAllocationList = nullptr;
			
			return true;
		}
		else {
			printf_s("Something is wrong");
			return false;
		}
	}
	
	else
	{		
		while (tempOutstandingL != NULL)
		{
			//checker = reinterpret_cast<char *>(tempOutstandingL->m_pBlockBase) + tempOutstandingL->m_sizeBlock;
			//printf_s("\n --------- address passed = %p and address stored in the list = %p and last = %p start of memory %p ------ \n", addr, tempOutstandingL->m_pBlockBase, checker, startOfMemory);
			if (addr >= tempOutstandingL->m_pBlockBase && addr < reinterpret_cast<int8_t *>(tempOutstandingL->m_pBlockBase) + tempOutstandingL->m_sizeBlock)
			{				
				
				tempFreeMemory->m_pNext = tempOutstandingL;

				//if elemt is head.
				if (tempOutstandingL == pOutstandingAllocationList) {
					pOutstandingAllocationList = pOutstandingAllocationList->m_pNext;
					tempFreeMemory = tempFreeMemory->m_pNext;
				}

				else if (tempOutstandingL->m_pNext != nullptr)
				{
					temp->m_pNext = tempOutstandingL->m_pNext; //recent changed		something wrong			
					tempFreeMemory = tempFreeMemory->m_pNext;
				}
				else
				{
					temp->m_pNext = nullptr;
					tempFreeMemory = tempFreeMemory->m_pNext;			
				}

				tempFreeMemory->m_pNext = nullptr;
			
				return true;
			}
			temp = tempOutstandingL;
			tempOutstandingL = tempOutstandingL->m_pNext;
			
		}
	}
	
	
}

void const HeapManager::_clearFreeMemoryList() {
	
	
	BlockDescriptor* temp1 = pFreeMemoryList;
	void* swapper;
	int tempSize;
	size_t counter = 1;

	BlockDescriptor* freeMemory = pFreeMemoryList;
	//sorting freeMemoryList
	while (counter != 0)
	{
		counter = 0;
		freeMemory = pFreeMemoryList;
		temp1 = pFreeMemoryList;
		while (temp1->m_pNext != nullptr)
		{			
			if (temp1->m_pBlockBase > temp1->m_pNext->m_pBlockBase)
			{
				swapper = temp1->m_pBlockBase;
				tempSize = temp1->m_sizeBlock;
				temp1->m_pBlockBase = temp1->m_pNext->m_pBlockBase;
				temp1->m_sizeBlock = temp1->m_pNext->m_sizeBlock;
				temp1->m_pNext->m_pBlockBase = swapper;
				temp1->m_pNext->m_sizeBlock = tempSize;
				counter++;
				//Checkng sorting

				/*while (freeMemory != NULL)
				{
					printf_s("\n Memory Discriptor Id : %d Size %d Memory Address : %p", freeMemory->m_id, freeMemory->m_sizeBlock, freeMemory->m_pBlockBase);
					freeMemory = freeMemory->m_pNext;
				}*/
			}
			else
				temp1 = temp1->m_pNext;
		}
	}


	temp1 = pFreeMemoryList;
	
	BlockDescriptor* container;

	//coalescing the memory blocks
	while (temp1->m_pNext != nullptr) {
		if (temp1->m_pNext->m_pBlockBase == static_cast<int8_t*>(temp1->m_pBlockBase) + temp1->m_sizeBlock)
		{
			temp1->m_sizeBlock = temp1->m_sizeBlock + temp1->m_pNext->m_sizeBlock;
			container = temp1->m_pNext;
			temp1->m_pNext = temp1->m_pNext->m_pNext;
			Free(container);

			//PrintBlockDescriptors();
			//_getch();
		}
		else
			temp1 = temp1->m_pNext;
	}

}

void const HeapManager::Free(BlockDescriptor* Victim) {

	BlockDescriptor* tempFreeDL = pFreeDescriptorList;
	BlockDescriptor* temp = pFreeDescriptorList;
	Victim->m_pBlockBase = nullptr;
	Victim->m_sizeBlock = NULL;
	Victim->m_pNext = nullptr;

	while (tempFreeDL->m_pNext != nullptr)
	{
		if (Victim->m_id < tempFreeDL->m_id)
		{
			if (temp == pFreeDescriptorList)
			{
				Victim->m_pNext = pFreeDescriptorList;
				pFreeDescriptorList = Victim;
				break;
			}
			else
			{
				Victim->m_pNext = tempFreeDL;
				temp->m_pNext = Victim;
				break;
			}
		}
		temp = tempFreeDL;
		tempFreeDL = tempFreeDL->m_pNext;
	}
	numberOfAvailDescriptors++;
}

bool HeapManager_UnitTest()
{
	//using namespace HeapManagerProxy;

	const size_t 		sizeHeap = 1024 * 1024;
	//const uint32_t 	numDescriptors = 2048;

	// Allocate memory for my test heap.
	//void * pHeapMemory = _aligned_malloc(sizeHeap, 4);
	//assert(pHeapMemory, "something wrong in pHeapMemory");
	HeapManager* hp = pDefaultHeap;

	// Create a heap manager for my test heap.
	/*HeapManager * pHeapManager = create(sizeHeap, numDescriptors);*/
	//makeDefaultHeap(&hp);
	//pDefaultHeap->create(sizeHeap, numDescriptors);
	


#ifdef TEST_SINGLE_LARGE_ALLOCATION
	// This is a test I wrote to check to see if using the whole block if it was almost consumed by 
	// an allocation worked. Also helped test my ShowFreeBlocks() and ShowOutstandingAllocations().
	{
		hp.PrintBlockDiscriptors();

		/*size_t largestBeforeAlloc = GetLargestFreeBlock(pHeapManager);
		void * pPtr = alloc(pHeapManager, largestBeforeAlloc - HeapManager::s_MinumumToLeave);*/

		{
			if (pPtr)
				ShowFreeBlocks(pHeapManager);
			printf("\n");
#ifdef __TRACK_ALLOCATIONS
			ShowOutstandingAllocations(pHeapManager);
#endif // __TRACK_ALLOCATIONS
			printf("\n");

			size_t largestAfterAlloc = GgetLargestFreeBlock(pHeapManager);
			free(pHeapManager, pPtr);

			ShowFreeBlocks(pHeapManager);
#ifdef __TRACK_ALLOCATIONS
			ShowOutstandingAllocations(pHeapManager);
#endif // __TRACK_ALLOCATIONS
			printf("\n");

			Collect(pHeapManager);

			ShowFreeBlocks(pHeapManager);
#ifdef __TRACK_ALLOCATIONS
			ShowOutstandingAllocations(pHeapManager);
#endif // __TRACK_ALLOCATIONS
			printf("\n");

			size_t largestAfterCollect = GetLargestFreeBlock(pHeapManager);
		}
	}
#endif

	std::vector<void *> AllocatedAddresses;

	long	numAllocs = 0;
	long	numFrees = 0;
	long	numCollects = 0;

	bool	done = false;

	// allocate memory of random sizes up to 1024 bytes from the heap manager
	// until it runs out of memory
	do
	{
		const size_t		maxTestAllocationSize = 1024;

		const unsigned int	alignments[] = { 4 };

		unsigned int	index = rand() % (sizeof(alignments) / sizeof(alignments[0]));

		unsigned int	alignment = alignments[0];

		size_t			sizeAlloc = 1 + (rand() & (maxTestAllocationSize - 1));

		void * pPtr = hp->_alloc(sizeAlloc,4);

		assert((reinterpret_cast<uintptr_t>(pPtr) & (alignment - 1)) == 0, " first case something wrong");

		if (pPtr == NULL)
		{
			hp->_clearFreeMemoryList();

			pPtr = hp->_alloc(sizeAlloc,4);

			if (pPtr == NULL)
			{
				done = true;
				break;
			}
		}

		AllocatedAddresses.push_back(pPtr);
		numAllocs++;

		const unsigned int freeAboutEvery = 10;
		const unsigned int garbageCollectAboutEvery = 40;

		if (!AllocatedAddresses.empty() && ((rand() % freeAboutEvery) == 0))
		{
			void * pPtr = AllocatedAddresses.back();
			AllocatedAddresses.pop_back();

			bool success = hp->_deAlloc(pPtr);
			assert(success, "something wrong");

			numFrees++;
		}

		if ((rand() % garbageCollectAboutEvery) == 0)
		{
			hp->_clearFreeMemoryList();

			numCollects++;
		}

	} while (1);

	printf("After exhausting allocations:\n");
	hp->PrintBlockDescriptors();

#ifdef __TRACK_ALLOCATIONS
	ShowOutstandingAllocations(pHeapManager);
#endif // __TRACK_ALLOCATIONS
	printf("\n");

	// now free those blocks in a random order
	if (!AllocatedAddresses.empty())
	{
		// randomize the addresses
		std::random_shuffle(AllocatedAddresses.begin(), AllocatedAddresses.end());

		// return them back to the heap manager
		while (!AllocatedAddresses.empty())
		{
			void * pPtr = AllocatedAddresses.back();
			AllocatedAddresses.pop_back();

			bool success = hp->_contains(pPtr);// need to create
			assert(success, "something wrong");

			success = hp->_isAllocated(pPtr); // need to create
			assert(success, "something wrong");

			success = hp->_deAlloc(pPtr); //de alloc = free
			assert(success, "something wrong");
		}

		printf("After freeing allocations:\n");

		hp->PrintBlockDescriptors();
#ifdef __TRACK_ALLOCATIONS
		ShowOutstandingAllocations(pHeapManager);
#endif // __TRACK_ALLOCATIONS

		// do garbage collection
		hp->_clearFreeMemoryList(); // coalescing = freememory
		// our heap should be one single block, all the memory it started with

		printf("After garbage collection:\n");

		hp->PrintBlockDescriptors();
#ifdef __TRACK_ALLOCATIONS
		ShowOutstandingAllocations(pHeapManager);
#endif // __TRACK_ALLOCATIONS

		printf("\n");		// do a large test allocation to see if garbage collection worked
		void * pPtr = hp->_alloc(sizeHeap / 2, 4);
		assert(pPtr, "something wrong");

		if (pPtr)
		{
			bool success = hp->_deAlloc(pPtr);
			assert(success, "something wrong");

		}
	}

	hp->CheckMemory(); // garbage collector
	hp->_clearFreeMemoryList();
	/*for (int i = 0;i < AllocatedAddresses.capacity;i++)
	{
		AllocatedAddresses
	}*/
	//AllocatedAddresses.at();
	DestroyFSA();
	printf_s("\n .........................................................................................................................HEre");
	hp->_clearFreeMemoryList();


	float *a = new float;
	float *b = new float;
	float *c = new float;
	printf("memory Address %p", c);
	delete c;
	float *d = new float;
	printf("memory Address %p", d);
	delete a;
	delete b;
	delete d;

	BitArray_UnitTest();
	hp->_clearFreeMemoryList();
	// we succeeded
	return true;
}

HeapManager::~HeapManager() {
	_clearFreeMemoryList();
	PrintBlockDescriptors();
	_aligned_free(startOfMemory);
}

void makeDefaultHeap(HeapManager * pHeapManager)
{
	if (pHeapManager != NULL)
	{
		pDefaultHeap = pHeapManager;
	}
}


#if defined( ENABLE_PROFILING )

void * operator new(size_t i_size)
{
	void * pReturn = nullptr;
	/*FSA *pFSA = FindFSA(i_size);
	if (pFSA)
		pReturn = pFSA->alloc();

	if (pReturn == nullptr)*/
		pReturn = pDefaultHeap->_alloc(i_size, 16);

	return pReturn;

}

void operator delete(void* i_ptr)
{
	/*FSA * pFSA = FindFSA(i_ptr);
	if (pFSA == nullptr && i_ptr)*/
		pDefaultHeap->_deAlloc(i_ptr);

	/*else if (pFSA && i_ptr) {
		pFSA->free(i_ptr);
	}*/
}

void * operator new[](size_t i_size)
{
	void * pReturn = nullptr;
	/*FSA *pFSA = FindFSA(i_size);
	if (pFSA)
		pReturn = pFSA->alloc();

	if (pReturn == nullptr)*/
		pReturn = pDefaultHeap->_alloc(i_size, 16);

	return pReturn;
}

void operator delete[](void* i_ptr)
{
	pDefaultHeap->_deAlloc(i_ptr);
	/*FSA * pFSA = FindFSA(i_ptr);
	if (pFSA == nullptr && i_ptr)
		pDefaultHeap->_deAlloc(i_ptr);

	else if (pFSA && i_ptr) {
		pFSA->free(i_ptr);
	}*/
}

#else

void * operator new(size_t i_size, size_t i_align)
{
	void * pReturn = nullptr;
	FSA *pFSA = FindFSA(i_size);
	if (pFSA)
		pReturn = pFSA->alloc();

	if(pReturn ==nullptr)
		pReturn = pDefaultHeap->_alloc(i_size, i_align);

	return pReturn;
}

void operator delete(void* i_ptr, size_t i_align)
{
	FSA * pFSA = FindFSA(i_ptr);
	if (pFSA == nullptr && i_ptr)
		pDefaultHeap->_deAlloc(i_ptr);

	else if (pFSA && i_ptr) {
		pFSA->free(i_ptr);
	}
}

void * operator new(size_t i_size)
{
	void * pReturn = nullptr;
	FSA *pFSA = FindFSA(i_size);
	if (pFSA)
		pReturn = pFSA->alloc();

	if (pReturn == nullptr)
		pReturn = pDefaultHeap->_alloc(i_size, 4);

	return pReturn;
	
}

void operator delete(void* i_ptr)
{
	FSA * pFSA = FindFSA(i_ptr);
	if (pFSA == nullptr && i_ptr)
		pDefaultHeap->_deAlloc(i_ptr);

	else if (pFSA && i_ptr) {
		pFSA->free(i_ptr);
	}	
}

void * operator new[](size_t i_size, size_t i_align)
{
	void * pReturn = nullptr;
	FSA *pFSA = FindFSA(i_size);
	if (pFSA)
		pReturn = pFSA->alloc();

	if (pReturn == nullptr)
		pReturn = pDefaultHeap->_alloc(i_size, i_align);

	return pReturn;
}

void operator delete[](void* i_ptr, size_t i_align)
{
	pDefaultHeap->_deAlloc(i_ptr);
	FSA * pFSA = FindFSA(i_ptr);
	if (pFSA == nullptr && i_ptr)
		pDefaultHeap->_deAlloc(i_ptr);

	else if (pFSA && i_ptr) {
		pFSA->free(i_ptr);
	}
}

void * operator new[](size_t i_size)
{
	void * pReturn = nullptr;
	FSA *pFSA = FindFSA(i_size);
	if (pFSA)
		pReturn = pFSA->alloc();

	if (pReturn == nullptr)
		pReturn = pDefaultHeap->_alloc(i_size, 4);

	return pReturn;
}

void operator delete[](void* i_ptr)
{
	pDefaultHeap->_deAlloc(i_ptr);
	FSA * pFSA = FindFSA(i_ptr);
	if (pFSA == nullptr && i_ptr)
		pDefaultHeap->_deAlloc(i_ptr);

	else if (pFSA && i_ptr) {
		pFSA->free(i_ptr);
	}
}

#endif