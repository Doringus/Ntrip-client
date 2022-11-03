# CMakeList.txt: проект CMake для Ntrip_client; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("Ntrip_client")

set(SOURCES "main.cpp")

add_executable (Ntrip_client ${SOURCES})

