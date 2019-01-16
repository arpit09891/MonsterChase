#include"ProcessFile_Process.h"
#include"LuaTestClass.h"

void ProcessFile_Process::Run(){

	if (m_sizeFileContents  && m_pFileContents)
	{
		LuaTestClass LTC = LuaTestClass();
		LTC.LuaTest(m_pFileContents, m_sizeFileContents);

	}
}