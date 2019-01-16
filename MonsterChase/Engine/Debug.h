#pragma once
#include<Windows.h>


#if defined(_MSC_VER)
#define BREAK_IN_DEBUGGER() __debugbreak()
#elif defined(__GNUC__)
#define BREAK_IN_DEBUGGER() builtin_trap()
#else
#error Provide a implementation of BREAK_IN_DEBUGGER
#endif

#if defined(_DEBUG)
#define EMIT_LOCATION() printf("File: %s Line: %d\n", __FILE__, __LINE__)
#define EMIT_STATEMENT_ERROR(error) printf("Assert: %s ", error)
#define DEBUG_PRINT(fmt,...) {printf(fmt, __VA_ARGS__); EMIT_LOCATION();}
#define assert(cmnd, errorCode) if((cmnd) == false) { EMIT_STATEMENT_ERROR(errorCode);EMIT_LOCATION();char message[500]; sprintf_s(message, "The file is %s and line is %d \n", __FILE__,__LINE__); OutputDebugStringA(message);}
//#define DEBUG_FUNCTION;
/*#define debug_console(){char message[500]; sprintf_s(message, "The function name is %p \n", __FUNCTION__); OutputDebugStringA(message);}*/
#else
#define assert(cmnd) void(0)
#define EMIT_LOCATION() void(0)
#define EMIT_STATEMENT_ERROR(error) void(0)
#endif // defined(_DEBUG)