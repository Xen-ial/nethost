#pragma once
#include <functional>

#if defined(_WIN32)
#define NETHOST_DELEGATE_CALLTYPE __stdcall
#ifdef _WCHAR_T_DEFINED
using NetHostChar = wchar_t;
#else
using NetHostChar = unsigned short;
#endif
#else
#define NETHOST_DELEGATE_CALLTYPE
using NetHostChar = char;
#endif

#if defined(_MSC_VER)
#define NETHOST_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#if defined(__i386__)
#define NETHOST_CDECL __attribute__((cdecl))
#else
#define NETHOST_CDECL
#endif
#else
#define NETHOST_CDECL
#endif

namespace nethost
{
	using Func        = int(NETHOST_DELEGATE_CALLTYPE*)(void*, int);
	using HostContext = void*;

	template <class T>
	using BorrowedRef = std::reference_wrapper<T>;

	void* loadLibrary(const char* path);
	void* getExport(void* handle, const char* name);
} // namespace nethost