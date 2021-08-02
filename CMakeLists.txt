cmake_minimum_required(VERSION 3.19)

PROJECT(FilES LANGUAGES CXX)

set(PROJECT_NAME FilES)
set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} src/FES.hpp src/util/util.cpp src/main.cpp src/aes/AES.cpp src/util/FileUtils.cpp src/aes/AESManager.cpp src/otp/OTP.cpp src/ui/ui.hpp src/ui/ui.cpp)

find_package(OpenGL REQUIRED)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-network sfml-graphics sfml-window OpenGL::GL)

find_package(cryptopp CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE cryptopp-static)

find_package(FLTK CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE fltk fltk_gl fltk_forms fltk_images)
#
#find_package(CUDA CONFIG REQUIRED)
#target_link_libraries(${PROJECT_NAME} PRIVATE CUDA)