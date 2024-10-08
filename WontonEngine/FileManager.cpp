#include "include/WontonEngine/FileManager.h"
#include <fstream>

void won::FileManager::ReadFile(const std::string& path, std::vector<unsigned char>& out)
{
	std::ifstream stream{ path, std::ios::in | std::ios::binary };

	out.clear();
	
	std::istreambuf_iterator<char> start{stream}, end;
	out = std::vector<unsigned char>{ start, end };
}

void won::FileManager::WriteFile(const std::string& path, const std::vector<unsigned char>& data, bool append)
{
	std::ofstream stream;

	stream.open(path, std::ios::binary | (append ? std::ios::app : (std::ios::openmode)0));

	for (unsigned char c : data)
	{
		stream << c;
	}
}
