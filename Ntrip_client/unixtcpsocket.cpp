#include "unixtcpsocket.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <iostream>


UnixTcpSocket::UnixTcpSocket(std::function<void(std::string_view data)> readCallback, std::function<void()> connectionAbortedCallback)
	: TcpSocket(std::move(readCallback), std::move(connectionAbortedCallback))
{ }

UnixTcpSocket::~UnixTcpSocket() {
	if (m_IsSocketCreated) {
		close(m_Socket);
	}
}

bool UnixTcpSocket::connect(const std::string& ip, unsigned short port, int timeoutSec) noexcept {
	m_Socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_Socket < 0) {
		return false;
	}

	m_IsSocketCreated = true;

	sockaddr_in clientService{ AF_INET, htons(port) };
	inet_pton(AF_INET, ip.c_str(), &clientService.sin_addr.s_addr);

	timeval timeout{ timeoutSec, 0 };

	int status = setsockopt(m_Socket, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
	if(status < 0) {
		return false;
	}
	int res = ::connect(m_Socket, reinterpret_cast<sockaddr*>(&clientService), sizeof(clientService));
	std::cout << "In socket class " << m_Socket << "\n";
	std::cout <<  "in unix socket "<< &m_Socket << "\n";
	return res == 0 ? true : false;
}