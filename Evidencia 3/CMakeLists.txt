cmake_minimum_required(VERSION 3.29)
project(Evidencia_3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Evidencia_3
    Bitacora.cpp
    Bitacora.h
    bitacora.txt
    main.cpp
        BinaryTree.h
        BinaryTree.cpp)
