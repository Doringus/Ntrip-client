#include "wintcpsocket.h"

#include <WS2tcpip.h>

#include <stdexcept>
#include <iostream>

WinTcpSocket::WinTcpSocket(std::function<void(std::string_view data)> readCallback, std::function<void()> connectionAbortedCallback)
	: TcpSocket(std::move(readCallback), std::move(connectionAbortedCallback))
{ }

WinTcpSocket::~WinTcpSocket() {
	if(m_IsSocketCreated) {
		shutdown(m_Socket, 2);
		closesocket(m_Socket);
	}
}

bool WinTcpSocket::connect(const std::string& ip, unsigned short port, int timeoutSec) noexcept {
	m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_Socket == INVALID_SOCKET) {
		return false;
	}
	m_IsSocketCreated = true;

	TIMEVAL timeout {timeoutSec, 0};

	sockaddr_in clientService {AF_INET, htons(port)};
	inet_pton(AF_INET, ip.c_str(), &clientService.sin_addr.s_addr);

	/// Switch socket to non-blocking mode
	unsigned long socketMode = 1;
	int status = ioctlsocket(m_Socket, FIONBIO, &socketMode);
	if(status != NO_ERROR) {
		return false;
	}

	if(::connect(m_Socket, reinterpret_cast<SOCKADDR*>(&clientService), sizeof(clientService)) == false) {
		return false;
	}

	/// Restore socket mode
	socketMode = 0;
	status = ioctlsocket(m_Socket, FIONBIO, &socketMode);
	if(status != NO_ERROR) {
		return false;
	}

	fd_set write;
	FD_ZERO(&write);
	FD_SET(m_Socket, &write);
	status = select(0, nullptr, &write, nullptr, &timeout);
	if(!FD_ISSET(m_Socket, &write) || status == SOCKET_ERROR) {
		return false;
	}

	return true;
}

bool WinTcpSocket::send(const char* data, int length) const noexcept {
	int totalBytesSend = 0;
	do {
		if (int result = ::send(m_Socket, data, length, 0); result != SOCKET_ERROR) {
			totalBytesSend += result;
		} else {
			return false;
		}

	} while (totalBytesSend < length);
	return true;
}

void WinTcpSocket::beginReceive() const noexcept {
	constexpr int bufSize = 2048;
	char buf[bufSize] = {0};
	int bytesReceived;
	do
	{
		bytesReceived = recv(m_Socket, buf, bufSize, 0);
		if (bytesReceived > 0) {
			std::string_view data(buf, bytesReceived);
			m_ReadCallback(data);
			memset(buf, 0, bufSize);
			//for (int i = 0; i < r; ++i) {
			//	printf("%02X ", static_cast<uint8_t>(buf[i]));
			//}
			//printf("\n");
		} else {
			m_ConnectionAbortedCallback();
			break;
		}
			
	} while (bytesReceived > 0);

}
