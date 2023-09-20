#pragma once

#include <string>
#include <vector>

namespace won
{
	class FileManager
	{
	public:
		static void ReadFile(const std::string& path, std::vector<unsigned char>& out);
		static void WriteFile(const std::string& path, const std::vector<unsigned char>& data, bool append = false);
	};
}