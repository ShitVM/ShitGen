cmake_minimum_required(VERSION 3.9.0)
project(ShitGen)

include(CheckIPOSupported)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

include_directories("./include")
file(GLOB_RECURSE SOURCE_LIST "./src/*.cpp")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./lib")

add_library(${PROJECT_NAME} STATIC ${SOURCE_LIST})

if(CMAKE_BUILD_TYPE STREQUAL "Release")
	check_ipo_supported(RESULT isIPOSupported)
	if(isIPOSupported)
		set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
	endif()
endif()

install(DIRECTORY "./include/sgn" DESTINATION "include")
install(TARGETS ${PROJECT_NAME} DESTINATION "lib")