cmake_minimum_required(VERSION 3.28)
project(chat_redes)

set(CMAKE_CXX_STANDARD 17)

add_executable(chat_redes main.cpp
        server.cpp
        server.h
        client.cpp
        client.h)
