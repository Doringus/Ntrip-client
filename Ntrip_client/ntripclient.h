#pragma once

#include <memory>
#include <string>
#include <fstream>

#ifdef _WIN32
#include "wintcpsocket.h"
#else
#include "unixtcpsocket.h"	
#endif

struct ntripConnectionConfig_t {
	std::string ip;
	std::string mountPoint;
	std::string base64Password;
	unsigned short port;
};

struct ntripSocketSettings_t {
	size_t numberOfReconnects;
	int timeout;
};

class Logger;

class NtripClient {
public:
	NtripClient(ntripConnectionConfig_t connectionConfig, ntripSocketSettings_t socketSettings, std::unique_ptr<Logger> logger);

	void start() noexcept;

private:
	bool connectToCaster() const noexcept;
	void beginSession() const noexcept;

private:
	ntripConnectionConfig_t m_ConnectionConfig;
	ntripSocketSettings_t m_SocketSettings;
	std::unique_ptr<TcpSocket> m_SocketImpl;
	std::unique_ptr<Logger> m_Logger;
};