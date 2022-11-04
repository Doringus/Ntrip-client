#include "ntripclient.h"

#include <iostream>
#include <ios>
#include <bitset>

#include "wintcpsocket.h"
#include "logger.h"

NtripClient::NtripClient(ntripConnectionConfig_t connectionConfig, ntripSocketSettings_t socketSettings, std::unique_ptr<Logger> logger)
	: m_ConnectionConfig(std::move(connectionConfig)), m_SocketSettings(socketSettings), m_Logger(std::move(logger))
{

	auto readCallback = [this](std::string_view data) {
		if(data.find("ICY 200 OK") == std::string_view::npos) {
			m_Logger->log(data);
		}
	};

	auto connectionAbortedCallback = [this]() {
		std::cout << "[Warning]: Connection lost. Attempting to reconnect...\n";
		if(!connectToCaster()) {
			std::cout << "[Error]: Cannot reconnect to caster\n";
			return;
		}
		std::cout << "[Info]: Reconnected to caster.Starting session...\n";
		beginSession();
	};

	m_SocketImpl = std::make_unique<WinTcpSocket>(std::move(readCallback), std::move(connectionAbortedCallback));
}

void NtripClient::start() noexcept {
	if(!connectToCaster()) {
		std::cout << "[Error]: Cannot establish connection with caster\n";
		return;
	}
	beginSession();
}

bool NtripClient::connectToCaster() const noexcept {
	std::cout << "[Info]: Connecting to caster...\n";
	bool connected = false;
	for (size_t i = 0; i < m_SocketSettings.numberOfReconnects; ++i) {
		if (!m_SocketImpl->connect(m_ConnectionConfig.ip, m_ConnectionConfig.port, m_SocketSettings.timeout)) {
			std::cout << "[Warning]: Connection failed. Attempts left: " + std::to_string(m_SocketSettings.numberOfReconnects - i - 1) + "\n";
		} else {
			connected = true;
			break;
		}
	}
	return connected;
}

void NtripClient::beginSession() const noexcept {
	const std::string connectionQuery =
		"GET /" + m_ConnectionConfig.mountPoint + " HTTP/1.0\r\n"
		"User-Agent: NTRIP TestClient/0.1\r\n"
		"Authorization: Basic " + m_ConnectionConfig.base64Password;
	m_SocketImpl->send(connectionQuery.c_str(), connectionQuery.length());
	m_SocketImpl->beginReceive();
}
