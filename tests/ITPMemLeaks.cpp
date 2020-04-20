#include "ITPMemLeaks.h"
#undef new
#include <cstring>
#include <iostream>

std::unordered_map<void*, ITPMemLeaks::AllocInfo> ITPMemLeaks::sAllocs;
std::vector<std::string> ITPMemLeaks::sMismatches;

void ITPMemLeaks::AddAllocation(void* address, size_t size, const char* fileName, size_t lineNum, bool isArray)
{
	sAllocs[address].mSize = size;
	sAllocs[address].mFileName = fileName;
	sAllocs[address].mLineNum = lineNum;
	sAllocs[address].mIsArray = isArray;
}

void ITPMemLeaks::RemoveAllocation(void* address, bool isArray)
{
	if (sAllocs.empty())
	{
		return;
	}

	auto iter = sAllocs.find(address);
	if (iter != sAllocs.end())
	{
		if (isArray != iter->second.mIsArray)
		{
			sMismatches.emplace_back("Allocation at ");
			sMismatches.back() += iter->second.mFileName;
			sMismatches.back() += ", Line ";
			sMismatches.back() += std::to_string(iter->second.mLineNum);
			sMismatches.back() += " used ";
			if (isArray)
			{
				sMismatches.back() += "new but deallocated with delete[].";
			}
			else
			{
				sMismatches.back() += "new[] but deallocated with delete.";
			}
		}
		sAllocs.erase(iter);
	}
}

bool ITPMemLeaks::CheckIfMemoryFreed(bool clearAllocsAfterCheck)
{
	bool retVal = sAllocs.empty() && sMismatches.empty();
	if (!retVal)
	{
		if (!sAllocs.empty())
		{
			std::cerr << "MEMORY LEAKS DETECTED:" << std::endl;
			for (auto& i : sAllocs)
			{
				std::cerr << "***" << i.second.mSize << " bytes allocated at " << i.second.mFileName << ", Line " << i.second.mLineNum << std::endl;
			}
		}
		if (!sMismatches.empty())
		{
			std::cerr << "MISMATCHES DETECTED:" << std::endl;
			for (auto& i : sMismatches)
			{
				std::cerr << "***" << i << std::endl;
			}
		}
	}

	if (clearAllocsAfterCheck)
	{
		sAllocs.clear();
		sMismatches.clear();
	}

	return retVal;
}

void* operator new(size_t size, const char* fileName, size_t lineNum)
{
	void* address = std::malloc(size);
	ITPMemLeaks::AddAllocation(address, size, fileName, lineNum, false);
	return address;
}

void* operator new[](size_t size, const char* fileName, size_t lineNum)
{
	void* address = std::malloc(size);
	ITPMemLeaks::AddAllocation(address, size, fileName, lineNum, true);
	return address;
}

void operator delete(void* address) noexcept
{
	ITPMemLeaks::RemoveAllocation(address, false);
	std::free(address);
}

void operator delete[](void* address) noexcept
{
	ITPMemLeaks::RemoveAllocation(address, true);
	std::free(address);
}
