cmake_minimum_required(VERSION 3.20)
project(OpenGLProject LANGUAGES C CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


file(GLOB_RECURSE SOURCES
    src/*.cpp
    src/*.c
)

file(GLOB_RECURSE HEADERS
    include/*.h
    include/*.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# vcpkg
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)


target_include_directories(${PROJECT_NAME} PRIVATE
    "${PROJECT_SOURCE_DIR}/include"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    glad::glad
    glm::glm
    imgui::imgui
    assimp::assimp
)


if (WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)
endif()

message(STATUS "Configuration avec dossier include/ OK ✓")
