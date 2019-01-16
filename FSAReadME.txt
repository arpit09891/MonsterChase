													FSA READ ME 
My Heap Manager is represented by BlockAllocator.h and BlockAllocator.cpp.

I have put my final display of all the descriptors and descriptor’s list in the destructor of Heap Manager before freeing the heap manager memory. I did this to show that all the object which have been created by new of std functions is also got deallocated by overridden delete function. Moreover, it shows that Heap Manager is again a one single chunk of memory before getting freed.
There is break point in my destructor of Heap Manager to highlight this.
My Heap Manager is synced with FSA.
FSA is responsible for allocating a memory block to the user. It also creates and link the bit array with my Fix size Heap.
FSAManager is responsible for creating FSA and finding appropriate FSA.
I have implemented 32 and 64-bit container difference for BitArray in BitArray.h and BitArray.cpp.


Bit Array - It handle the bit array and its relative functions.

1. Creating a Bit Array.
2. Setting Bit (void SetBit(size_t))
3. Clearing a Bit (void ClearBit(size_t))
4. Getting the first clear bit(bool GetFirstClearBit(size_T & o_bit))
5. Setting the first clear bit(bool GetFirstSetBit(size_T & o_bit))
6. Checking if a passed bit is set(inline bool IsBitSet(size_t i_bitNumber))
7. Checking if a passed bit is clear(inline bool IsBitClear(size_t i_bitNumber))
8. Checking if all the bits in the bit are clear(bool AreAllClear(void) ).
9. Checking if all the bits in the bit are set(bool AreAllSet(void) ).
10. Creates the bit array and set all thie bits to 1(BitArray * Create(size_t i_numBits, bool i_startClear = true)).
11. Cleares all the bit (ClearAll(void)).
12. Set all the bit(SetAll(void)).

FSA is responsible for allocating a memory block to the user. It also creates and link the bit array with my Fix size Heap.
FSAManager is responsible for creating FSA and finding appropriate FSA.

My Heap Manager is synced with FSA.
Different kinds of FSA have been allocated in the end of create function of heap Manager. Function used for creating FSA are part of namespace FSAMAnager. (createHeaps)
I have implemented 32 and 64 bit container difference for BitArray in BitArray.h and BitArray.cpp.
