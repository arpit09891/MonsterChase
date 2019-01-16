#pragma once

#include"Engine.h"
#include"JobSystem.h"
#include"IJob.h"

class ProcessFile : public Engine::JobSystem::IJob {
public:
	ProcessFile(const char * i_pFilename) :
		IJob("ProcessFile"),
		m_pFilename(i_pFilename)
	{
		assert(m_pFilename);
	}
	static uint8_t * LoadFile(const char * i_pFilename, size_t & o_sizeFile);
	void Run();

private:
	const char *		m_pFilename;
};
