#pragma once
#include"Engine.h"
#include"IJob.h"
#include"JobSystem.h"

class ProcessFile_Process : public Engine::JobSystem::IJob
{

public:
	ProcessFile_Process(uint8_t * i_pFileContents, size_t i_sizeFileContents) :
		IJob("ProcessFile_Process"),
		m_pFileContents(i_pFileContents),
		m_sizeFileContents(i_sizeFileContents)
	{}

	void Run();
private:
	uint8_t *		m_pFileContents;
	size_t			m_sizeFileContents;
};