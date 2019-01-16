#include"ProcessFile.h"
#include"ProcessFile_Process.h"

void ProcessFile::Run() {

	if (m_pFilename)
	{
		size_t sizeFileContents = 0;
		uint8_t * pFileContents = LoadFile(m_pFilename, sizeFileContents);

		if (pFileContents && sizeFileContents)
		{
			IJob * pProcessJob = new ProcessFile_Process(pFileContents, sizeFileContents);
			assert(pProcessJob);

			Engine::JobSystem::RunJob(*pProcessJob, "Default");
		}
	}
}

uint8_t * ProcessFile::LoadFile(const char * i_pFilename, size_t & o_sizeFile)
{
	assert(i_pFilename != NULL);

	FILE *				pFile = NULL;

	errno_t fopenError = fopen_s(&pFile, i_pFilename, "rb");
	if (fopenError != 0)
		return NULL;

	assert(pFile != NULL);

	int FileIOError = fseek(pFile, 0, SEEK_END);
	assert(FileIOError == 0);

	long FileSize = ftell(pFile);
	assert(FileSize >= 0);

	FileIOError = fseek(pFile, 0, SEEK_SET);
	assert(FileIOError == 0);

	uint8_t * pBuffer = new uint8_t[FileSize];
	assert(pBuffer);

	size_t FileRead = fread(pBuffer, 1, FileSize, pFile);
	assert(FileRead == FileSize);

	fclose(pFile);

	o_sizeFile = FileSize;

	return pBuffer;
}