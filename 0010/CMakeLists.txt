cmake_minimum_required(VERSION 3.10)
project(app.elf VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR src)
set(INCLUDE_DIR include)

file(GLOB_RECURSE SOURCE_FILES ${SRC_DIR}/*.cpp)

include_directories(${INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} 
    SDL2_image
    SDL2
    GL
    GLEW
)
target_compile_options(${PROJECT_NAME} PRIVATE -pedantic)
