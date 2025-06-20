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

#---------------------------------------------------------------------#

# --- Documentação via Doxygen ---
find_package(Doxygen REQUIRED)
if(DOXYGEN_FOUND)
  set(DOXY_IN ${CMAKE_CURRENT_SOURCE_DIR}/Docs/Doxyfile.in)
  set(DOXY_OUT ${CMAKE_CURRENT_BINARY_DIR}/Docs/Doxyfile)

  configure_file(${DOXY_IN} ${DOXY_OUT} @ONLY)

  add_custom_target(doc ALL
    COMMAND ${Doxygen_EXECUTABLE} ${DOXY_OUT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Gerando documentação com Doxygen"
    VERBATIM
  )
else()
  message(WARNING "Doxygen não encontrado – 'make doc' não vai gerar documentação")
endif()

