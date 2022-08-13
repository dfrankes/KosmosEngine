cmake_minimum_required(VERSION 3.0.0)
project("Game")

include(CTest)
enable_testing()

include(CPack)
include(FetchContent)

add_subdirectory("Projects/Kosmos")
add_subdirectory("Projects/Kosmos.Game")