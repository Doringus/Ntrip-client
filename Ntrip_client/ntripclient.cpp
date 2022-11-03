#include "ntripclient.h"

#include "wintcpsocket.h"

NtripClient::NtripClient(ntripClientConfig_t config) : m_Config(std::move(config)){
	auto readCallback = [](const char* data, int size) {

	};

	auto connectionAbortedCallback = []() {

	};

	m_SocketImpl = std::make_unique<WinTcpSocket>(readCallback, connectionAbortedCallback);
}

void NtripClient::start() noexcept {
	m_SocketImpl->connect(m_Config.ip, m_Config.port);

}
