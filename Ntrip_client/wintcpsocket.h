#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winSock2.h>
#include <ws2tcpip.h>

#include "tcpsocket.h"

class WinTcpSocket : public TcpSocket {
public:
	WinTcpSocket(std::function<void(std::string_view data)> readCallback, std::function<void()> connectionAbortedCallback);
	~WinTcpSocket();

	bool connect(const std::string& ip, unsigned short port, int timeoutSec) noexcept override;

private:
	bool m_IsSocketCreated = false;
};