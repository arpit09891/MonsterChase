#pragma once

template<class T>
WeakPointer<T>::WeakPointer(T * i_ptr)
{
	m_pObject = i_ptr;
}

template<class T>
WeakPointer<T>::WeakPointer(const WeakPointer & i_other)
{
	if (i_other == nullptr) {
		m_pObject = nullptr;
	}
	else
	{
		m_pObject = i_other.m_pObject;
		counter = i_other.counter;
		counter->weakCount++;
	}
}

template<class T>
bool WeakPointer<T>::operator==(const WeakPointer<T> & i_other) const
{
	if (m_pObject == i_other.m_pObject)
		return true;

	return false;
}

template<class T>
bool WeakPointer<T>::operator==(nullptr_t) const
{
	if (m_pObject == nullptr)
		return true;

	return false;
}

template<class T>
WeakPointer<T>::WeakPointer(SmartPtr<T> & i_other)
{
	if (i_other == nullptr) {
		m_pObject = nullptr;
	}
	else
	{
		m_pObject = i_other.getObject();
		counter = i_other.getCounter();
		counter->weakCount++;
	}
}

template<class T>
T & WeakPointer<T>::operator*()
{
	return *m_pObject;
}

template<class T>
SmartPtr<T> WeakPointer<T>::Acquire() const
{
	if (counter->refCount > 0)
	{
		return SmartPtr<T>(m_pObject, counter);
	}
	else
	{
		return SmartPtr<T>(nullptr);
	}

}

