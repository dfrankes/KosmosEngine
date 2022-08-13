cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project("Game")

include(CTest)
enable_testing()

include(CPack)
include(FetchContent)

set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}../bin")

# Library's
set(LIB_DIR "${PROJECT_SOURCE_DIR}/dependencies")
set(INCLUDES_DIR_PUBLIC "${PROJECT_SOURCE_DIR}/includes")
set(INCLUDES_DIR_PRIVATE "${PROJECT_SOURCE_DIR}/src")

set(ENGINE_DIR "${PROJECT_SOURCE_DIR}/src/Engine")

list(APPEND SOURCE_FILES
    "${ENGINE_DIR}/Kosmos.cpp"
    "${ENGINE_DIR}/Kosmos.hpp"

    "${ENGINE_DIR}/Helpers/Debug.cpp"
    "${ENGINE_DIR}/Helpers/Debug.h"

    "${ENGINE_DIR}/Core/Window.cpp"
    "${ENGINE_DIR}/Core/Window.hpp"

    "${ENGINE_DIR}/Helpers/shader_s.h"

    "${PROJECT_SOURCE_DIR}/src/Game.cpp"
)

add_executable(Game ${SOURCE_FILES})

# add_library(Engine SHARED ${SOURCE_FILES})
set_target_properties(Game PROPERTIES LINKER_LANGUAGE CXX)

# Copy everything from res into the output folder (hardcoded debug folder for now)
message("${PROJECT_SOURCE_DIR}/res -> ${PROJECT_BINARY_DIR}/bin/Debug")
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/${PROJECT_NAME})

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(${PROJECT_NAME} glfw)
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)

# glad
set(GLAD_DIR "${LIB_DIR}/glad")
add_library("glad" "${GLAD_DIR}/src/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}/include")
target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")

# json parser
FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.11.2)

FetchContent_GetProperties(json)

if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)

add_subdirectory(${LIB_DIR}/glm EXCLUDE_FROM_ALL)
target_link_libraries(${PROJECT_NAME} glm)