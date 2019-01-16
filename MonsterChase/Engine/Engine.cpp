#include"Engine.h"
#include"BlockAllocator.h"
#include"Timer.h"
#include"JobSystem.h"
#include"MessagingSystem.h"

namespace Engine {
	HeapManager hp = HeapManager();
	MessagingSystem * gMessaging;
	float dt;
}
bool Engine::StartUp()
{
	makeDefaultHeap(&hp);
	bool success = hp.create(5012*5012, 10000);
	
	if (success)
	{		
		JobSystem::StartUp();
		MessagingSystem * message = MessagingSystem::Create();
		gMessaging = message;
		return true;
	}
	else
		return false;

}

uint8_t * Engine::LoadFile(const char * i_pFilename, size_t & o_sizeFile) {
	//assert(i_pFilename != NULL, "Filename is null");

	FILE * pFile = NULL;

	errno_t fopenError = fopen_s(&pFile, i_pFilename, "rb");
	if (fopenError != 0)
		return NULL;

	//assert(pFile != NULL, "pFile is null");

	int FileIOError = fseek(pFile, 0, SEEK_END);
	//assert(FileIOError == 0, "There is FileIOError");

	long FileSize = ftell(pFile);
	//assert(FileSize >= 0, "FileSize is in negative");

	FileIOError = fseek(pFile, 0, SEEK_SET);
	//assert(FileIOError == 0, "There is FileIOError");

	uint8_t * pBuffer = new uint8_t[FileSize];
	//assert(pBuffer, "pBuffer has problem");

	size_t FileRead = fread(pBuffer, 1, FileSize, pFile);
	//assert(FileRead == FileSize, "FileRead is not equal to FileSize");

	fclose(pFile);

	o_sizeFile = FileSize;

	return pBuffer;
}

void Engine::ShutDown() {

	//delete pDefaultHeap;
	
}

