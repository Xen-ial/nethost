#include <nethost/Utils.h>

#include <cassert>

#ifdef __unix__
#include <dlfcn.h>

#elif defined(_WIN32) || defined(WIN32)

#endif

namespace nethost
{
#ifdef __unix__
	void* loadLibrary(const char* path)
	{
		void* handle = dlopen(path, RTLD_LAZY | RTLD_LOCAL);
		assert(handle != nullptr);
		return handle;
	}

	void* getExport(void* handle, const char* name)
	{
		void* address = dlsym(handle, name);
		assert(address != nullptr);
		return address;
	}
#elif defined(_WIN32) || defined(WIN32)

#endif
} // namespace nethost