#pragma once
#include <functional>

namespace nethost
{
	template <class T>
	using BorrowedRef = std::reference_wrapper<T>;

	void* loadLibrary(const char* path);
	void* getExport(void* handle, const char* name);
} // namespace nethost