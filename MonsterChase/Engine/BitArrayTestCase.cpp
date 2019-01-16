#include "BitArray.h"
#include"Debug.h"
#include<stdio.h>
#include<malloc.h>
#include"BlockAllocator.h"
void BitArray_UnitTest(void)
{
	
	const size_t bitCount = 1000;
	BitArray* pMyArray = new (BitArray);//static_cast<BitArray*>( malloc(sizeof(BitArray)));
	pMyArray->Create(bitCount);

	pMyArray->ClearBit(20);

	size_t firstSetBit = 0;
	size_t firstClearBit = 0;

	bool foundClearBit = pMyArray->GetFirstClearBit(firstClearBit);
	assert((firstClearBit == 20), "Something wrong");

	pMyArray->SetBit(20);
	bool foundSetBit = pMyArray->GetFirstSetBit(firstSetBit);
	assert(firstSetBit != 20, "Something wrong");

	/*for (size_t i = 0; i < 999;i++) {
		pMyArray->ClearBit(i);
	}
*/
	for (size_t i = 0; i < bitCount; i++)
	{
		assert(pMyArray->IsBitClear(i) == false, "Something wrong");
		assert(pMyArray->IsBitSet(i) == true, "Something wrong");

		size_t bit = 0;
		bool success;
		success = pMyArray->GetFirstSetBit(bit);
		assert(bit == i, "Something wrong");

		pMyArray->ClearBit(i);

		assert(pMyArray->IsBitClear(i) == true, "Something wrong");
		assert(pMyArray->IsBitSet(i) == false, "Something wrong");

		success = pMyArray->GetFirstSetBit(bit);
		
		
		assert(((i < (bitCount - 1)) && (bit == (i + 1))) || ((i == (bitCount - 1)) && !success),"Something is wrong");
		/*printf("\n Loop number %d", i);
		printf("\n bit = %d", bit);*/
		//assert(((i < (bitCount - 1)) && success && (bit == (i + 1))) || ((i == (bitCount - 1)) && !success), "Something wrong");
	}

	pMyArray->SetAll();
	bool test1 = (pMyArray->GetFirstClearBit(firstClearBit) == false);
	assert(test1,"Something wrong");


	pMyArray->ClearAll();
	//pMyArray->SetBit(1);
	assert(pMyArray->GetFirstSetBit(firstSetBit) == false, "Something wrong");


	delete pMyArray;
}