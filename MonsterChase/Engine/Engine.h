#pragma once
#include<stdint.h>
namespace Engine {

	bool StartUp();
	uint8_t * LoadFile(const char * i_pFilename, size_t & o_sizeFile);
	void ShutDown();

};