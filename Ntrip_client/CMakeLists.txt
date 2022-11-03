cmake_minimum_required (VERSION 3.8)

project ("Ntrip_client")

#CXX
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADERS "wintcpsocket.h"  "tcpsocket.h" "ntripclient.h")
set(SOURCES "main.cpp" "wintcpsocket.cpp" "ntripclient.cpp")

add_executable (Ntrip_client ${SOURCES} ${HEADERS})

if(WIN32)
  target_link_libraries(Ntrip_client wsock32 ws2_32)
endif()