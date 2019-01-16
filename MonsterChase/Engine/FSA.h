#pragma once

class HeapManager;
class BitArray;

class FSA
{
public:
	FSA(size_t sizeBlock, int numBlocks, HeapManager * heapManager);
	~FSA();

	void* alloc();
	void free(void * i_address);
	void SetBitArray(size_t, int, HeapManager *);
	BitArray* GetBitArray();
	void *pMemoryPointer;
	size_t blockSize;
	size_t numOfBlocks;
private:
	BitArray *bitArray;

};