#pragma once
#include <nethost/ErrorCodes.h>

#include <string>
#include <functional>

namespace nethost::err
{
	using LogCallback = std::function<void(std::string_view err, err::StatusCode status)>;

	void setLogCallback(const LogCallback& callback);
	void logln(std::string err, err::StatusCode code);
	void log(std::string err, err::StatusCode code);
} // namespace nethost