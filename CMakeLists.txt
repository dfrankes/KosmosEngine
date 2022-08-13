cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project("Game")

include(CTest)
enable_testing()

include(CPack)
include(FetchContent)

add_subdirectory("Projects/Kosmos")
add_subdirectory("Projects/Kosmos.Game")