#include "logger.h"

#include <iostream>

void CmdLogger::log(std::string_view data) {
	std::cout << data << "\n";
}

FileLogger::FileLogger(std::string filepath) : m_Filepath(std::move(filepath)) {
	std::ofstream(m_Filepath, std::ios_base::binary);
}

void FileLogger::log(std::string_view data) {
	std::ofstream(m_Filepath, std::ios_base::binary | std::ios_base::app).write(data.data(), data.size());
}
