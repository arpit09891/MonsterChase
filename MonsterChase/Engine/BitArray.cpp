#include"BitArray.h"
#include"Debug.h"
#include<stdio.h>
#include<string.h>

#pragma intrinsic(_BitScanForward)


BitArray * BitArray::Create(size_t i_numBits, bool i_startClear) {

	totalBits = i_numBits;
	fullBytes = (i_numBits / bitsPerContainer);
	
	if (i_numBits % bitsPerContainer > 0)
		fullBytes++;

	m_pBits = new type_t[fullBytes];
	assert(m_pBits, "Something wrong in BitArray with bits");
	m_numBits = i_numBits;
	size_t noOfBytes = (fullBytes * bitsPerContainer) / 8;
			

	memset(m_pBits, i_startClear ? ~0 : 0, noOfBytes);
	size_t remainingBits = bitsPerContainer - (i_numBits % bitsPerContainer);
	size_t bit = i_numBits;

	for (int i = 0; i < remainingBits; i++)
	{		
		ClearBit(bit);
		bit++;
	}
	return (BitArray*)m_pBits;

}
void BitArray::ClearAll(void) {
	size_t noOfBytes = (fullBytes * bitsPerContainer) / 8;
	memset(m_pBits, 0, noOfBytes);	
}

void BitArray::SetAll(void)
{
	size_t noOfBytes = (fullBytes * bitsPerContainer) / 8;
	memset(m_pBits, ~0, noOfBytes);
	size_t remainingBits = bitsPerContainer - (totalBits % bitsPerContainer);
	size_t bit = totalBits;

	for (int i = 0; i < remainingBits; i++)
	{
		ClearBit(bit);
		bit++;
	}

}

bool BitArray::AreAllClear(void) const
{
	int index = 0;
	size_t m_numBytes = fullBytes;

	while ((m_pBits[index] == 0x00) && (index <= m_numBytes))
	{
		index++;
	}
	if (index == m_numBytes) {
		return true;
	}
	return false;
}

bool BitArray::AreAllSet(void) const {
	int index = 0;
	size_t m_numBytes = fullBytes;

	while ((m_pBits[index] == mask) && (index <= m_numBytes))
	{
		index++;
	}
	size_t usedBits = totalBits % bitsPerContainer;
	size_t bit = (totalBits - (totalBits % bitsPerContainer))-1;
	size_t counter = 0;
	for (int i = 0; i < bitsPerContainer; i++)
	{
		if (IsBitClear(bit))
		{
			counter++;
		}
		bit++;
	}
	if (counter == bit );
		index++;

	if (index == m_numBytes) {
		return true;
	}
	return false;
}

void BitArray::SetBit(size_t bitNumber) {
	
	size_t byteNumber = bitNumber / bitsPerContainer;
	/*if (bitNumber % bitsPerBytes > 0)
		byteNumber++;*/
	m_pBits[byteNumber] |= 1i64 <<(bitNumber - (byteNumber * bitsPerContainer));
}

void BitArray::ClearBit(size_t bitNumber) {
	size_t byteNumber = bitNumber / bitsPerContainer;
	m_pBits[byteNumber] &= ~(1i64 << (bitNumber - (byteNumber * bitsPerContainer)));
}

bool BitArray::GetFirstSetBit(size_t & o_bit) const {
	size_t index = 0;
	size_t m_numBytes = fullBytes;
	
	while ((m_pBits[index] == 0x00)&& (index <= m_numBytes))
	{		
			index++;
	}
	if (index == m_numBytes) {
		return false;
	}
	else {
	
		unsigned long temp = index;
		uintptr_t byte = m_pBits[index];
		//unsigned long bit;
		size_t bitset;
#if _WIN64
		unsigned char isNonzero = _BitScanForward64(&temp, m_pBits[index]);
#else
		unsigned char isNonzero = _BitScanForward(&temp, m_pBits[index]);
#endif 
		//unsigned char isNonzero = _BitScanForward(&temp, m_pBits[index]);
		//bool bitset = _BitScanForward(&temp, m_pBits[index]);
		if (isNonzero) {
			bitset = index * bitsPerContainer + temp;
		}
		o_bit = bitset;
		return true;
	}

}

BitArray::~BitArray()
{
	delete m_pBits;
}

bool BitArray::GetFirstClearBit(size_t & o_bit) const
{
	size_t index = 0;
	size_t m_numBytes = fullBytes;
	while ((m_pBits[index] == mask) && index <= m_numBytes) {
		index++;
	}
	if (index== m_numBytes) {
		return false;
	}
	else
	{
		uintptr_t byte = m_pBits[index];
		unsigned long bit;

		//int mask = 0xffffffff;
		size_t bitset;
#if _WIN64
		unsigned char isNonzero = _BitScanForward64(&bit, byte ^ mask);
#else
		unsigned char isNonzero = _BitScanForward(&bit, byte ^ mask);
#endif
		//unsigned char isNonzero = _BitScanForward(&bit, (unsigned long)byte ^ mask);
		if (isNonzero)
		{
			bitset = index * bitsPerContainer + bit;
		}
		if (bitset >= totalBits)
			return false;
		else {
			o_bit = bitset;
			return true;
		}
	}
}
