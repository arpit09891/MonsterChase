#pragma once


struct Counter {
	long refCount;
	long weakCount;
};


template<class T>
class SmartPtr
{
public:
	//Standard Constructor
	//SmartPtr(T * i_pObject);
	explicit SmartPtr(T * i_pObject);

	// copy constructor
	SmartPtr(const SmartPtr & i_other);
	SmartPtr(T* i_pObject, Counter* i_pCounter);
	
	// member access operator
	T * operator->()
	{
		return m_pObject;
	}
	// indirection operator
	T & operator*();
	
	SmartPtr & operator=(const SmartPtr & i_other)
	{
		if (this == i_other || this == nullptr) {
			// 
		}
		else {
			ReleaseCurrentReference();
			AcquireNewReference(i_other);
		}
		return *this;

	}

	T* getObject() {
		return m_pObject;
	}

	//for test case
	void setCounter(int strongCount ) {
		counter->refCount = strongCount;
	}

	Counter * getCounter() {
		return counter;
	}
	
	void AcquireNewReference(SmartPtr & i_other);

	bool operator==(const SmartPtr & i_other) const ;
	//bool operator==(const WeakPointer & i_other);
	bool operator==(nullptr_t) const;
	bool operator!=(const SmartPtr & i_other);

	~SmartPtr()
	{
		ReleaseCurrentReference();
	}

	template<class U>
	SmartPtr(const SmartPtr<U> & i_other) :
		m_pObject(i_other.m_ptr),
		m_pRefCount(i_other.m_pRefCount)
	{
	}


private:
	void ReleaseCurrentReference();
	/*{
		if (--(*m_pRefCount) == 0)
		{
			delete m_pRefCount;
			delete m_pObject;
		}
	}
*/
	T *		m_pObject;
	Counter *	counter;
};


#include"SmartPtr-inl.h"
