#pragma once
#include"SmartPtr.h"

template<class T>
class WeakPointer
{
public:
	WeakPointer(T * i_ptr = NULL);

	WeakPointer(const WeakPointer & i_other);

	T * operator->()
	{
		return m_pObject;
	}
	// indirection operator
	T & operator*();


	WeakPointer &operator=(const WeakPointer<T> & i_other) 
	{
		if (i_other == nullptr) {
			return WeakPointer(nullptr);
		}
		else if (this == &i_other) {
			return *this;
		}
		else if (i_other.counter->refCount > 0) {
			if (m_pObject != nullptr)
				counter->weakCount--;
			
			m_pObject = i_other.m_pObject;
			counter = i_other.counter;
			counter->weakCount++;
			return *this;
		}
		else
			return WeakPointer(nullptr);
	}

	WeakPointer(SmartPtr<T> & i_other);
	SmartPtr<T> Acquire() const;
	bool operator==(const WeakPointer<T> & i_other) const;
	bool operator==(nullptr_t) const;

private:
	T * m_pObject;
	Counter * counter;
};

#include"WeakPointer-inl.h"
