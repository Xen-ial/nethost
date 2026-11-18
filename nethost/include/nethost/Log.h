#pragma once
#include <nethost/ErrorCodes.h>

#include <string>
#include <functional>

namespace nethost::err
{
	using LogCallback = std::function<void(std::string_view err, err::StatusCode status)>;

	/**
	 * @brief Set the Log Callback
	 * @param callback New log callback
	 */
	void setLogCallback(const LogCallback& callback);

	/**
	 * @brief Calls log callback func with a new line
	 * @param err Error to input
	 * @param code Status Code to input
	 */
	void logln(std::string err, err::StatusCode code);

	/**
	 * @brief Calls log callback without a new line
	 * @param err Error to input
	 * @param code Status Code to input
	 */
	void log(std::string err, err::StatusCode code);
} // namespace nethost::err