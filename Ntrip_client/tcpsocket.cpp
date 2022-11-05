#include "tcpsocket.h"

#include <cstring>

bool TcpSocket::send(const char* data, int length) const noexcept {
	int totalBytesSend = 0;
	do {
		if (int result = ::send(m_Socket, data, length, 0); result != -1) {
			totalBytesSend += result;
		}
		else {
			return false;
		}

	} while (totalBytesSend < length);
	return true;
}

void TcpSocket::beginReceive() const noexcept {
	constexpr int bufSize = 2048;
	char buf[bufSize] = { 0 };
	int bytesReceived;
	do
	{
		bytesReceived = recv(m_Socket, buf, bufSize, 0);
		if (bytesReceived > 0) {
			std::string_view data(buf, bytesReceived);
			m_ReadCallback(data);
			std::memset(buf, 0, bufSize);
		}
		else if (bytesReceived == 0) {
			break;
		}
		else {
			m_ConnectionAbortedCallback();
			break;
		}

	} while (bytesReceived > 0);
}
