cmake_minimum_required (VERSION 3.8)

project ("Ntrip_client")

#CXX
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADERS "tcpsocket.h" "ntripclient.h" "logger.h")
set(SOURCES "main.cpp" "ntripclient.cpp" "logger.cpp" "tcpsocket.cpp")

if(WIN32) 
	set(HEADERS ${HEADERS} "wintcpsocket.h" "winsockinit.h")
	set(SOURCES ${SOURCES} "wintcpsocket.cpp")
endif()

if(UNIX)
	set(HEADERS ${HEADERS} "unixtcpsocket.h")
	set(SOURCES ${SOURCES} "unixtcpsocket.cpp")
endif()

add_executable (Ntrip_client ${SOURCES} ${HEADERS})

if(WIN32)
  target_link_libraries(Ntrip_client wsock32 ws2_32)
endif()