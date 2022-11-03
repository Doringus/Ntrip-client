#include <iostream>

#include "wintcpsocket.h"
#include "ntripclient.h"

int main(int argc, char** argv) {
    WSADATA wsaData;
   /*
    * Args:
    * -h - host ip:port
    * -mp - mountpoint
    * -o - output_file
    * -r - number of reconnects
    *
    */
    // Initialize Winsock
    WSAStartup(MAKEWORD(2, 2), &wsaData);

	/*WinTcpSocket socket;
    if(socket.connect("3.23.52.207", 2101)) {
        std::string query = "GET /ACACU HTTP/1.0\r\n"
    						 "User-Agent: NTRIP Test/0.1\r\n";
    	if(socket.send(query.c_str(), query.size())) {
            std::cout << "send successfully";
    	}
    }*/

    WSACleanup();

	return 0;
}