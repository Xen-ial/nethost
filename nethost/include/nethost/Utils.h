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

	/**
	 * @brief Shared reference, wrapped with (reference_wrapper)
	 * @tparam T Target reference type to wrap
	 */
	template <class T>
	using BorrowedRef = std::reference_wrapper<T>;

	/**
	 * @brief Load library into memory
	 * @param path Path to library
	 * @return void* Raw library bytes
	 */
	void* loadLibrary(const char* path);

	/**
	 * @brief Resolve the library exports
	 * @param handle Library handle
	 * @param name Target export name
	 * @return void* Raw function bytes
	 */
	void* getExport(void* handle, const char* name);
} // namespace nethost