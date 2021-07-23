cmake_minimum_required(VERSION 3.19)
project(FilES)

set(CMAKE_CXX_STANDARD 20)


set(EXECUTABLE_NAME FilES)
set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/SFML/cmake-modules/")

#include_directories(${SFML_INCLUDE_DIR})


add_executable(FilES src/crypto.hpp src/util/util.cpp src/main.cpp src/aes/AES.cpp src/util/FileUtils.cpp src/aes/AESManager.cpp src/otp/OTP.cpp)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(FilES PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

find_package(cryptopp CONFIG REQUIRED)
target_link_libraries(FilES PRIVATE cryptopp-static)
