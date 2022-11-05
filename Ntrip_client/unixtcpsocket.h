#pragma once

#include "tcpsocket.h"

class UnixTcpSocket : public TcpSocket {
public:
	UnixTcpSocket(std::function<void(std::string_view data)> readCallback, std::function<void()> connectionAbortedCallback);
	~UnixTcpSocket();

	bool connect(const std::string& ip, unsigned short port, int timeoutSec) noexcept override;

private:
	bool m_IsSocketCreated = false;
};