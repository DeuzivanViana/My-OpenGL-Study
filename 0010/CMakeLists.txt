cmake_minimum_required(VERSION 3.10)

# Nome do projeto
project(MyApp)

# Defina o compilador como g++
set(CMAKE_CXX_COMPILER g++)

# Diretórios
set(SRC_DIR src)
set(INCLUDE_DIR include)
set(BIN_DIR ${CMAKE_BINARY_DIR}/bin)

# Arquivos-fonte
file(GLOB_RECURSE SOURCE_FILES ${SRC_DIR}/*.cpp)

# Configuração do diretório de saída
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

# Flags de compilação
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
include_directories(${INCLUDE_DIR})
execute_process(COMMAND sdl2-config --cflags OUTPUT_VARIABLE SDL2_CFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SDL2_CFLAGS}")

# Bibliotecas de linkagem
execute_process(COMMAND sdl2-config --libs OUTPUT_VARIABLE SDL2_LIBS OUTPUT_STRIP_TRAILING_WHITESPACE)
set(LINK_LIBS ${SDL2_LIBS} SDL2_image GL GLEW)

# Alvo
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Linkagem
target_link_libraries(${PROJECT_NAME} ${LINK_LIBS})

# Alvo de limpeza manual
add_custom_target(clean
    COMMAND ${CMAKE_COMMAND} -E remove -f ${BIN_DIR}/${PROJECT_NAME} ${CMAKE_BINARY_DIR}/CMakeFiles/${PROJECT_NAME}.dir/*.o
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/CMakeFiles
    COMMENT "Cleaning build files..."
)
