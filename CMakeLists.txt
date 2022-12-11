cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project("Game")

include(CTest)
enable_testing()

include(CPack)
include(FetchContent)
set(FETCHCONTENT_BASE_DIR ${PROJECT_SOURCE_DIR}/dependencies CACHE PATH "Missing description." FORCE)

set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}../bin")

# Library's
set(LIB_DIR "${PROJECT_SOURCE_DIR}/dependencies")
set(INCLUDES_DIR_PUBLIC "${PROJECT_SOURCE_DIR}/includes")
set(INCLUDES_DIR_PRIVATE "${PROJECT_SOURCE_DIR}/src")

aux_source_directory(${SOURCE_DIR} SUB_SOURCES)
FILE(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.hpp")
add_executable(Game ${SOURCE_FILES})

set_target_properties(Game PROPERTIES LINKER_LANGUAGE CXX)

add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/src/resources
    ${PROJECT_SOURCE_DIR}/bin/Debug/resources
    COMMENT "Copying resources into binary directory")

add_dependencies(Game copy_resources)

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
target_include_directories("glad" PUBLIC "${GLAD_DIR}/include")
target_include_directories(${PROJECT_NAME} PUBLIC "${GLAD_DIR}/include")
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

# assimp
FetchContent_Declare(assimp
    GIT_REPOSITORY https://github.com/assimp/assimp.git
    GIT_TAG master)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INJECT_DEBUG_POSTFIX OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(assimp)

set(BUILD_SHARED_LIBS ON)

# find_package(assimp CONFIG REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE dependencies/assimp-src/include)
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json glm assimp)
add_subdirectory(${LIB_DIR}/glm)