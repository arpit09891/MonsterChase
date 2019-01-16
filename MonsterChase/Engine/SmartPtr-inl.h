#pragma once

template<class T>
SmartPtr<T>::SmartPtr(T * i_pObject = nullptr)
{
	if (i_pObject == nullptr)
	{
		m_pObject = nullptr;
	}
	else
	{
		m_pObject = i_pObject;
		counter = new Counter();
		counter->refCount++;
	}
}

template<class T>
SmartPtr<T>::SmartPtr(T* i_pObject, Counter* i_pCounter)
{
	if (i_pObject == nullptr)
	{
		m_pObject = nullptr;
	}
	else
	{
		m_pObject = i_pObject;
		counter = i_pCounter;
	}
}

template<class T>
SmartPtr<T>::SmartPtr(const SmartPtr & i_other) {
	if (i_other == nullptr) {
		m_pObject = nullptr;
	}
	else
	{
		m_pObject = i_other.m_pObject;
		counter = i_other.counter;
		counter->refCount++;
	}
}

template<class T>
T & SmartPtr<T>::operator*()
{
	return *m_pObject;
}



template<class T>
void SmartPtr<T>::AcquireNewReference(SmartPtr & i_other)
{
	if (i_other == nullptr)
	{
		this = i_other;
	}
	else {
		this = i_other;
		counter->refCount++;
	}
}

template<class T>
bool SmartPtr<T>::operator==(const SmartPtr & i_other) const
{
	if (m_pObject == i_other.m_pObject)
		return true;

	return false;
}

template<class T>
bool SmartPtr<T>::operator==(nullptr_t) const
{
	if (m_pObject == nullptr)
		return true;

	return false;
}
//template<class T>
//bool SmartPtr<T>::operator==(const WeakPointer & i_other)
//{
//	if (m_pObject == i_other.m_pObject)
//		return true;
//
//	return false;
//}

template<class T>
bool SmartPtr<T>::operator!=(const SmartPtr & i_other)
{
	return !(this == i_other);
}

template<class T>
void SmartPtr<T>::ReleaseCurrentReference()
{
	if (this == nullptr)
	{
		delete m_pObject;
		//delete counter;
	}
	else if (m_pObject == nullptr)
	{
		delete m_pObject;
	}
	else
	{
		if (counter->refCount <= 1)
		{
			delete m_pObject;

			//delete counter;
		}
		else
		{
			(counter->refCount)--;
			m_pObject = nullptr;
		}
	}
}
