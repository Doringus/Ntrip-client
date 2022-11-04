#include "logger.h"

#include <iostream>

void CmdLogger::log(std::string_view data) {
	std::cout << data << "\n";
}

FileLogger::FileLogger(std::string_view filepath) : m_LogStream(filepath.data(), std::ios_base::binary | std::ios_base::app) { }

FileLogger::~FileLogger() {
	m_LogStream.close();
}

void FileLogger::log(std::string_view data) {
	m_LogStream.write(data.data(), data.size());
}
