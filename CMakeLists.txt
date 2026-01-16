file(GLOB_RECURSE SCOPE_SOURCES src/*.cpp)

add_library(SCOPE STATIC ${SCOPE_SOURCES})

target_include_directories(SCOPE PUBLIC include)


find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)


target_link_libraries(SCOPE PUBLIC
    glfw
    glad::glad
    glm::glm
    imgui::imgui
    assimp::assimp
)
