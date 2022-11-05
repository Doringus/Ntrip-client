#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winSock2.h>

class WinsockInit {
public:
	WinsockInit() {
		WSADATA wsaData;
		WSAStartup(MAKEWORD(2, 2), &wsaData);
	}

	~WinsockInit() {
		WSACleanup();
	}
};