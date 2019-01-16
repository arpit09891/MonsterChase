#pragma once

//#include"FSA.h"

class HeapManager;
class FSA;

namespace FSAManager {
	static FSA *allocatedFS[3];
	FSA * CreateFSA(size_t sizeBlock, int numBlocks, HeapManager * hp);
	FSA * FindFSA(size_t i_size);
	FSA * FindFSA(void * i_ptr);
	void CreateHeaps(HeapManager*);
	void DestroyFSA();
	void AllocateFSA();
}