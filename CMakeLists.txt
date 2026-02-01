cmake_minimum_required(VERSION 3.10)
project(QuantLOB)

# 設定 C++ 標準 (建議使用 C++17 或更高)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 告訴 CMake 標頭檔在 src 目錄中
include_directories(src)

# 建立執行檔，來源是 src/main.cpp
add_executable(QuantLOB src/main.cpp)