cmake_minimum_required(VERSION 3.19)
project(FilES)

set(CMAKE_CXX_STANDARD 20)


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
include_directories(backends)


find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})
add_executable(FilES src/crypto.hpp src/util.cpp src/main.cpp src/AES.cpp src/FileUtils.cpp)

target_link_libraries(FilES ${CONAN_LIBS})
target_link_libraries(FilES ${wxWidgets_LIBRARIES})