#pragma once

#include <memory>
#include <string>

class TcpSocket;

struct ntripClientConfig_t {
	std::string ip;
	std::string login;
	std::string password;
	unsigned short port;
};

class NtripClient {
public:
	NtripClient(ntripClientConfig_t config);

	void start() noexcept;
private:
	ntripClientConfig_t m_Config;
	std::unique_ptr<TcpSocket> m_SocketImpl;
};