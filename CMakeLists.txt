cmake_minimum_required(VERSION 3.20)

project(Yfaverb CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(Yfaverb
    main.cpp
    ModeBank.cpp
    Mode.cpp
    ModalReverbEngine.cpp
)


