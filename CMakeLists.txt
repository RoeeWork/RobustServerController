cmake_minimum_required(VERSION 3.15)

project(MyProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add executable
add_executable(rsc 
				main.cpp 
				Commands.cpp 
				AddServers.cpp
				ControlWorker.cpp
				arp_utils.cpp 
				json_utils.cpp)

find_package(nlohmann_json 3.2.0 REQUIRED)
target_link_libraries(rsc PRIVATE nlohmann_json::nlohmann_json)
