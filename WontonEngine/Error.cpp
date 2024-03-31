#include "include/WontonEngine/Error.h"

#include <stdexcept>
#include <sstream>

void won::Error::ThrowError(const std::string& message, std::ostream& output, int line, const char* file)
{
	std::stringstream finalMsgstream;

	finalMsgstream << "ERROR AT LINE " << line << " IN " << file << ":\n\t" << message;

	std::string finalMsg = finalMsgstream.str();
	output << finalMsg << std::endl;

	throw std::runtime_error{ finalMsg.c_str() };
}
