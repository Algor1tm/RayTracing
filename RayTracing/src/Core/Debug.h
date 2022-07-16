#include <stdio.h>


#define LOG(x, ...) printf(x, __VA_ARGS__) 


#if _DEBUG
	#define ASSERT(x, ...)	{ if(!(x)) { LOG(__VA_ARGS__); __debugbreak(); } }
#else 
	#define ASSERT(x, ...)
#endif
