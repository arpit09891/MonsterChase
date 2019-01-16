#pragma once
#include"lua.hpp"
#include"Point2D.h"
#include<stdint.h>

class LuaTestClass {
	
public:
	void PlayerProcess();

	void LuaTest(uint8_t * pFileContents, size_t sizeFile);

	int GetLuaTableEntries(lua_State * i_pState, int i_index);

	size_t ReadIntArray(lua_State * i_pState, int i_index, int * o_pInts, size_t i_numInts);

	size_t ReadFloatArray(lua_State * i_pState, int i_index, float * o_pFloats, size_t i_numFloats);

	size_t GetFloatArray(lua_State * i_pState, int i_indexTable, const char * i_pArrayKey, float * o_pFloats, size_t i_numFloats);

	Point2D GetVector3(lua_State * i_pState, int i_index);

	

};