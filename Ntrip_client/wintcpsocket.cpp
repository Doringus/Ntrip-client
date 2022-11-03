#include "wintcpsocket.h"

#include <WS2tcpip.h>

#include <stdexcept>
#include <iostream>

WinTcpSocket::WinTcpSocket(std::function<void(const char* data, int size)> readCallback, std::function<void()> connectionAbortedCallback)
	: TcpSocket(std::move(readCallback), std::move(connectionAbortedCallback))
{
	m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(m_Socket == INVALID_SOCKET) {
		throw std::runtime_error("Socket error: " + std::to_string(WSAGetLastError()));
	}
}

WinTcpSocket::~WinTcpSocket() {
	closesocket(m_Socket);
}

bool WinTcpSocket::connect(const std::string& ip, unsigned short port) const noexcept {
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	inet_pton(AF_INET, ip.c_str(), &clientService.sin_addr.s_addr);
	clientService.sin_port = htons(port);
	int status = ::connect(m_Socket, reinterpret_cast<SOCKADDR*>(&clientService), sizeof(clientService));
	if(status != 0) {
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
	beginReceive();
	return true;
}

void WinTcpSocket::beginReceive() const noexcept {
	char buf[2048];
	int r;
	do
	{
		r = recv(m_Socket, buf, 2048, 0);
		if (r > 0) {
			m_ReadCallback(buf, r);
			//for (int i = 0; i < r; ++i) {
			//	printf("%02X ", static_cast<uint8_t>(buf[i]));
			//}
			//printf("\n");
		} else if (r == 0) {
			std::cout << "connection ended" << std::endl;
		} else {
			std::cout << "error" << WSAGetLastError() << std::endl;
			m_ConnectionAbortedCallback();
		}
			
	} while (r > 0);

}
