#include "MemoryTracker.h"

#ifdef GUEEPO2D_DEBUG
#include <vector>
#include "core/Log.h"

struct AllocationMetrics {
	uint32_t TotalAllocated = 0;
	uint32_t TotalFreed = 0;

	uint32_t CurrentUsage() { return TotalAllocated - TotalFreed; }
};

static AllocationMetrics s_AllocationMetrics;

struct AllocationInfo {
	const char* file;
	int line;
	size_t size;
	void* pointer;
};

static std::vector<AllocationInfo> allocationInfoVec;

void MemoryTracker_TrackMemory(void* pointer, size_t size, const char* file, int line) {
	s_AllocationMetrics.TotalAllocated += static_cast<uint32_t>(size);
	allocationInfoVec.push_back({ file, line, size, pointer });
}

void MemoryTracker_RemoveTracking(void* pointer, size_t size) {
	s_AllocationMetrics.TotalFreed += static_cast<uint32_t>(size);

	int indexToRemove = -1;
	for (int i = 0; i < allocationInfoVec.size(); i++) {
		if (allocationInfoVec[i].pointer == pointer) {
			indexToRemove = i;
			break;
		}
	}

	if (indexToRemove != -1) {
		allocationInfoVec.erase(allocationInfoVec.begin() + indexToRemove);
	}
}

void MemoryTracker_LogMemoryUsage() {
	LOG_INFO("Memory Tracker");
	LOG_INFO("Current Memory Usage: {0}", s_AllocationMetrics.CurrentUsage());
	LOG_INFO("Allocations being tracked: {0}", allocationInfoVec.size());
}

void MemoryTracker_CheckForLeaks() {
	for (int i = 0; i < allocationInfoVec.size(); i++) {
		LOG_WARN("MEMORY LEAK DETECTED: FILE:{0} LINE:{1}", allocationInfoVec[i].file, allocationInfoVec[i].line);
	}

	// g2dassert(allocationInfoVec.size() == 0, "there are memory leaks!");
}

#else
void MemoryTracker_TrackMemory(void* pointer, size_t size, const char* file, int line) { unreferenced(pointer, size, file, line); }
void MemoryTracker_RemoveTracking(void* pointer, size_t size) { unreferenced(pointer, size); }
void MemoryTracker_LogMemoryUsage() {}
void MemoryTracker_CheckForLeaks() {}
#endif