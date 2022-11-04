#pragma once

#include <string_view>
#include <fstream>

class Logger {
public:
	virtual ~Logger() = default;

	virtual void log(std::string_view data) = 0;
};

class CmdLogger : public Logger {
public:
	void log(std::string_view data) override;
};

class FileLogger : public Logger {
public:
	FileLogger(std::string_view filepath);
	~FileLogger();

	void log(std::string_view data) override;
private:
	std::ofstream m_LogStream;
};