#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winSock2.h>
#include <ws2tcpip.h>

#include "tcpsocket.h"

class WinTcpSocket : public TcpSocket {
public:
	WinTcpSocket(std::function<void(const char* data, int size)> readCallback, std::function<void()> connectionAbortedCallback);
	~WinTcpSocket();

	bool connect(const std::string& ip, unsigned short port) const noexcept override;
	bool send(const char* data, int length) const noexcept override;
	void beginReceive() const noexcept override;

private:
	SOCKET m_Socket;
};