cmake_minimum_required(VERSION 3.10)
project(SocketTest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(Threads REQUIRED)

# Create server executable
add_executable(server server.cpp)
target_link_libraries(server Threads::Threads)

# Create client executable
add_executable(client client.cpp)
target_link_libraries(client Threads::Threads)

# Set compiler flags for better performance
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall")

