
#include"FSAManager.h"
#include"FSA.h"
#include"BlockAllocator.h"


namespace FSAManager {
	FSA * CreateFSA(size_t sizeBlock, int numBlocks, HeapManager* pDefaultHeap) {
		FSA *fsa = reinterpret_cast<FSA *>(pDefaultHeap->_alloc((sizeBlock * numBlocks) + sizeof(FSA), 4));;
		fsa->pMemoryPointer = reinterpret_cast<uint8_t *>(fsa) + sizeof(FSA);
		fsa->SetBitArray(sizeBlock, numBlocks, pDefaultHeap);
		return fsa;
	}

	void CreateHeaps(HeapManager* pDefaultHeap)
	{
		pDefaultHeap->FSASizes[0].sizeBlock = 8;
		pDefaultHeap->FSASizes[0].numBlocks = 24;

		pDefaultHeap->FSASizes[1].sizeBlock = 16;
		pDefaultHeap->FSASizes[1].numBlocks = 24;

		pDefaultHeap->FSASizes[2].sizeBlock = 32;
		pDefaultHeap->FSASizes[2].numBlocks = 24;
		for(size_t i = 0; i<3; i++ )
		{
			allocatedFS[i] = CreateFSA(pDefaultHeap->FSASizes[i].sizeBlock, pDefaultHeap->FSASizes[i].numBlocks, pDefaultHeap);
		}
	}

	FSA * FindFSA(size_t i_size)
	{
		if (i_size <= 8)
			return allocatedFS[0];
		else if (i_size>8 && i_size <= 16)
			return allocatedFS[1];
		else if (i_size>16 && i_size <= 32)
			return allocatedFS[2];
		else
			return nullptr;
	}

	FSA * FindFSA(void * i_ptr)
	{
		for (int i = 0; i < 3; i++) {
			if (i_ptr == allocatedFS[i]->pMemoryPointer) {
				return allocatedFS[i];
			}
		}
		return nullptr;
	}

	void DestroyFSA() {
		for (size_t i = 0; i < 3; i++)
		{
			delete allocatedFS[i];
		}
	}

}