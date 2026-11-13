#include <nethost/Log.h>
#include <nethost/ErrorCodes.h>

#include <format>
#include <chrono>
#include <print>
#include <string>

namespace
{
	std::string getTime()
	{
		auto now = std::chrono::system_clock::now();
		return std::move(std::format("[{:%H:%M:%S}] ", now));
	}

	constexpr std::string_view RED_COLOR    = "\033[31m";
	constexpr std::string_view GREEN_COLOR  = "\033[92m";
	constexpr std::string_view YELLOW_COLOR = "\033[33m";
	constexpr std::string_view CYAN_COLOR   = "\033[36m";
	constexpr std::string_view END_COLOR    = "\033[0m";

	nethost::err::LogCallback sLogCallback =
	    [](std::string_view err, nethost::err::StatusCode code)
	{
		auto time   = getTime();
		auto status = nethost::err::statusCodeToString(code);

		if (status.contains("SUCCESS"))
		{
			std::print("[{}] {}Success({}):{} {} ", time, GREEN_COLOR, status, END_COLOR, err);
			return;
		}

		std::print("[{}] {}Error({}):{} {} ", time, RED_COLOR, status, END_COLOR, err);
	};
} // namespace

namespace nethost::err
{
	void setLogCallback(const LogCallback& callback)
	{
		sLogCallback = callback;
	}

	void logln(std::string err, err::StatusCode code)
	{
		sLogCallback(std::format("{}\n", err), code);
	}

	void log(std::string err, err::StatusCode code)
	{
		sLogCallback(std::format("{}", err), code);
	}
} // namespace nethost::err