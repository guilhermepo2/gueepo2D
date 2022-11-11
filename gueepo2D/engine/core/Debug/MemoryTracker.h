#pragma once

#include <iostream>

extern void MemoryTracker_TrackMemory(void* pointer, size_t size, const char* file, int line);
extern void MemoryTracker_RemoveTracking(void* pointer, size_t size);
extern void MemoryTracker_LogMemoryUsage();
extern void MemoryTracker_CheckForLeaks();

#ifdef GUEEPO2D_DEBUG
inline void* __cdecl operator new(size_t size, const char* file, int line) {
	void* ptr = (void*)malloc(size);
	
	MemoryTracker_TrackMemory(ptr, size, file, line);

	return ptr;
}

inline void __cdecl operator delete(void* pointer, size_t size) {
	MemoryTracker_RemoveTracking(pointer, size);
	free(pointer);
}

#define DEBUG_NEW new(__FILE__, __LINE__)
#define new DEBUG_NEW
#endif