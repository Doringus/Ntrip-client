#pragma once

#include <string>
#include <functional>

class TcpSocket {
public:
	TcpSocket(std::function<void(const char* data, int size)> readCallback, std::function<void()> connectionAbortedCallback)
		: m_ReadCallback(std::move(readCallback)), m_ConnectionAbortedCallback(std::move(connectionAbortedCallback)) { }

	virtual ~TcpSocket() = default;

	virtual bool connect(const std::string& ip, unsigned short port) const noexcept = 0;
	virtual bool send(const char* data, int length) const noexcept = 0;
	virtual void beginReceive() const noexcept = 0;

protected:
	std::function<void(const char* data, int size)> m_ReadCallback;
	std::function<void()> m_ConnectionAbortedCallback;
};