#pragma once

#include <sstream>	

namespace Logger
{
	void Write(const std::ostringstream& stream)
	{
		OutputDebugStringA("[Log] ");
		OutputDebugStringA(stream.str().c_str());
		OutputDebugStringA("\n");
	}

	template <typename T>
	void Log(const T& value)
	{
		std::ostringstream stream;
		stream << value;

		Write(stream);
	}

	template <typename T>
	void Log(const std::string& msg, const T& value)
	{
		std::ostringstream stream;
		stream << msg << value;

		Write(stream);
	}
}
