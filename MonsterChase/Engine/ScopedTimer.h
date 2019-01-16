#pragma once
#include"Timer.h"
#include"Accumulator.h"

class ScopedTimer {

	long long	m_Start;
	Accumulator *	m_pAccumulator;
	const char *	m_pScopeName;

public:
	ScopedTimer(Accumulator & i_MyAccumulator) :
		m_Start(Timer::GetCounter()),
		m_pAccumulator(&i_MyAccumulator)
	{}

	~ScopedTimer()
	{
		*m_pAccumulator += Timer::GetTimeDiff_ms(Timer::GetCounter());
	}

};