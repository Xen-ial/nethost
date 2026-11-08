#pragma once

#include <memory>
#include <utility>
#include <functional>

namespace nethost
{
	template <class T>
	using Ref = std::shared_ptr<T>;

	template <class T>
	using Scope = std::unique_ptr<T>;

	template <class T>
	using WeakRef = std::weak_ptr<T>;

	template <class T>
	using BorrowedRef = std::reference_wrapper<T>;

	template <class T, class... Args>
	[[nodiscard]] inline Ref<T> makeRef(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template <class T, class... Args>
	[[nodiscard]] inline Scope<T> makeScope(Args&&... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	void* loadLibrary(const char* path);
	void* getExport(void* handle, const char* name);
} // namespace cat