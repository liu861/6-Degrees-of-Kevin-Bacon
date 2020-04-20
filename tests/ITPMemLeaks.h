#pragma once
#include <unordered_map>
#include <vector>
#include <string>

class ITPMemLeaks
{
public:
	struct AllocInfo
	{
		size_t mSize = 0;
		const char* mFileName = nullptr;
		size_t mLineNum = 0;
		bool mIsArray = false;
	};

	static void AddAllocation(void* address, size_t size, const char* fileName, size_t lineNum, bool isArray);
	static void RemoveAllocation(void* address, bool isArray);

	// Returns true if everything was freed, false otherwise
	// Also clears out current maps
	static bool CheckIfMemoryFreed(bool clearAllocsAfterCheck = true);
private:
	static std::unordered_map<void*, AllocInfo> sAllocs;
	static std::vector<std::string> sMismatches;
};

void* operator new(size_t size, const char* fileName, size_t lineNum);
void* operator new[](size_t size, const char* fileName, size_t lineNum);
#define new new(__FILE__, __LINE__)
