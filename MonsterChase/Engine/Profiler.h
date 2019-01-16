#pragma once
#include<map>
#include"Accumulator.h"

class Profiler
{
	std::map<const char *, const Accumulator *> m_AllAccumulators;

public:
	Profiler() {
		m_AllAccumulators = std::map<const char *,const Accumulator *>();
	}

	void RegisterAccumulator(const char * i_pName, const Accumulator & i_Accumulator)
	{
		m_AllAccumulators.insert(std::pair<const char *, const Accumulator *>(i_pName, &i_Accumulator));
	}

};
