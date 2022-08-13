cmake_minimum_required(VERSION 3.8)
set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/Projects/Kosmos.Game/src")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}../bin")

message("${SOURCE_DIR}/Game.cpp")

list(APPEND SOURCE_FILES
    "${SOURCE_DIR}/Game.cpp"
)

add_executable(Game ${SOURCE_FILES})

target_link_libraries(Game Engine)

# target_link_libraries(Game ${CHEETAH_LIB})