#pragma once

#include <string>
#include <functional>
#include <string_view>

class TcpSocket {
public:
	TcpSocket(std::function<void(std::string_view data)> readCallback, std::function<void()> connectionAbortedCallback)
		: m_ReadCallback(std::move(readCallback)), m_ConnectionAbortedCallback(std::move(connectionAbortedCallback)) { }

	virtual ~TcpSocket() = default;

	virtual bool connect(const std::string& ip, unsigned short port, int timeoutSec) noexcept = 0;
	virtual bool send(const char* data, int length) const noexcept = 0;
	virtual void beginReceive() const noexcept = 0;

protected:
	std::function<void(std::string_view data)> m_ReadCallback;
	std::function<void()> m_ConnectionAbortedCallback;
};