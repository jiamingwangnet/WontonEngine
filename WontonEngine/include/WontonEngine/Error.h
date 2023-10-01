#pragma once

#include <string>
#include <ostream>

namespace won
{
	class Error
	{
	public:
		static void ThrowError(const std::string& message, std::ostream& output, int line, const char* file);
	};
}