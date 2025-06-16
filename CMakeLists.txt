cmake_minimum_required(VERSION 3.10)
project(TP1Trabalho2 VERSION 1.0 LANGUAGES CXX)

# C++ padrão
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Diretórios fonte
include_directories(src)

# Arquivos fonte
file(GLOB_RECURSE SOURCE_FILES
    "Source/*.cpp"
)

# Executável principal
add_executable(tp1 ${SOURCE_FILES})

# Teste separado (opcional, ou pode usar add_subdirectory mais tarde)
add_executable(test_app "Tests")
