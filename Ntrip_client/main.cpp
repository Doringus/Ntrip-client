#include <iostream>
#include <charconv>

#include "wintcpsocket.h"
#include "ntripclient.h"
#include "logger.h"

/*
       * Args:
       * -i - host ip:port
       * -mp - mountpoint
       * -o - output_file
       * -r - number of reconnects
       * -p - password
       *
   */

int main(int argc, char** argv) {
    std::vector<std::string_view> args(argv + 1, argv + argc);

    ntripConnectionConfig_t connectionConfig;
    ntripSocketSettings_t socketSettings {5, 5};
    std::string logFilepath;
	
    for(size_t i = 0; i < args.size(); ++i) {
        if (args[i].find("-i") != std::string_view::npos) {
            if (auto pos = args[i + 1].find(":"); pos != std::string_view::npos) {
                connectionConfig.ip = args[i + 1].substr(0, pos);
                std::from_chars(args[i + 1].data() + pos + 1, args[i + 1].data() + args[i + 1].length(), connectionConfig.port);
            } else {
                std::cout << "Invalid ip format!\n";
                return -1;
            }
        } else if (args[i].find("-mp") != std::string_view::npos) {
            connectionConfig.mountPoint = args[i + 1];
        } else if (args[i].find("-o") != std::string_view::npos) {
            logFilepath = args[i + 1];
        } else if (args[i].find("-r") != std::string_view::npos) {
            std::from_chars(args[i + 1].data(), args[i + 1].data() + args[i + 1].length(), socketSettings.numberOfReconnects);
        } else if (args[i].find("-p") != std::string_view::npos) {
            connectionConfig.base64Password = args[i + 1];
        }
    }
    


	WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);


    std::unique_ptr<Logger> logger;
    if(logFilepath.empty()) {
        logger = std::make_unique<CmdLogger>();
    } else {
        logger = std::make_unique<FileLogger>(logFilepath);
    }
	NtripClient client(connectionConfig, socketSettings, std::move(logger));
	client.start();
  //  NtripClient client({ "3.23.52.207" , "ACACU", "", 2101 }, {5, 15}, std::make_unique<FileLogger>("log.dat"));



    WSACleanup();

	return 0;
}