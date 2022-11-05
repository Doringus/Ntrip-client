#pragma once

#include <string>
#include <functional>
#include <string_view>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winSock2.h>
#include <WS2tcpip.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#endif

class TcpSocket {
public:
	TcpSocket(std::function<void(std::string_view data)> readCallback, std::function<void()> connectionAbortedCallback)
		: m_ReadCallback(std::move(readCallback)), m_ConnectionAbortedCallback(std::move(connectionAbortedCallback)) { }

	virtual ~TcpSocket() = default;

	virtual bool connect(const std::string& ip, unsigned short port, int timeoutSec) noexcept = 0;
	virtual bool send(const char* data, int length) const noexcept;
	virtual void beginReceive() const noexcept;

protected:
	std::function<void(std::string_view data)> m_ReadCallback;
	std::function<void()> m_ConnectionAbortedCallback;
#ifdef _WIN32
	SOCKET m_Socket;
#else
	int m_Socket;
#endif

};