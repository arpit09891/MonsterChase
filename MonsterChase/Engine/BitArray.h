#pragma once
//#include"BlockAllocator.h"
#include <inttypes.h>


#ifdef _WIN64
typedef uint64_t type_t;
#define mask 0xFFFFFFFFFFFFFFFF
#define bitsPerContainer 64
#else
typedef uint32_t type_t;
#define mask 0xFFFFFFFF
#define bitsPerContainer 32
#endif

class BitArray {

	 
	

public:

	BitArray * Create(size_t i_numBits, bool i_startClear = true);
	void ClearAll(void);
	void SetAll(void);

	bool AreAllClear(void) const;
	bool AreAllSet(void) const;

	inline bool IsBitSet(size_t i_bitNumber) const
	{
		size_t byteNumber = i_bitNumber / bitsPerContainer;
		if (m_pBits[byteNumber] & (1i64 << (i_bitNumber - byteNumber * bitsPerContainer))) {
			return true;
		}
		return false;
	}
	inline bool IsBitClear(size_t i_bitNumber) const
	{
		return !IsBitSet(i_bitNumber);
	}

	void SetBit(size_t i_bitNumber);
	void ClearBit(size_t i_bitNumber);

	bool GetFirstClearBit(size_t & o_bit) const;
	bool GetFirstSetBit(size_t & o_bit) const;
	int fullBytes;

	//bool operator[](size_t i_index) const;
	~BitArray();

private:
	type_t *m_pBits;
	//const static size_t bitsPerContainer = 32;
	size_t m_numBits;
	size_t totalBits;
};