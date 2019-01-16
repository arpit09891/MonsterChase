#include "FSA.h"
#include"Debug.h"
#include "BitArray.h"
#include<stdio.h>
#include"BlockAllocator.h"
void * FSA::alloc()
{
	size_t firstAvailableBit;
	bool success = bitArray->GetFirstClearBit(firstAvailableBit);
	if (success)
	{
		bitArray->ClearBit(firstAvailableBit);
		return (void*)((uintptr_t)pMemoryPointer + (firstAvailableBit*blockSize));
	}
	else {
		assert(true, "Something is wrong in FSA alloc");
		return nullptr;
	}
}

void FSA::free(void * i_address) {
	size_t targetBit;
	targetBit = size_t((reinterpret_cast<uint8_t *>(i_address) - reinterpret_cast<uint8_t *>(pMemoryPointer)) / blockSize);
	if (bitArray->IsBitSet(targetBit))
	{
		assert(true, "Bit is already free");
	}
	else
		bitArray->SetBit(targetBit);  
}

void FSA::SetBitArray(size_t i_sizeBlock, int i_numBlocks, HeapManager* pDefaultHeap) {

	blockSize = i_sizeBlock;
	numOfBlocks = i_numBlocks;
	bitArray = reinterpret_cast<BitArray *>(pDefaultHeap->_alloc(i_numBlocks, 4));// new BitArray(numBlocks, i_pManager);
	bitArray->Create(i_numBlocks, true);
}

BitArray * FSA::GetBitArray()
{
	return bitArray;
}

FSA::~FSA()
{
	size_t bit = 0;
	assert(bitArray->GetFirstClearBit(bit) == false,"There are memory leaks, free memory");
	delete bitArray;
}