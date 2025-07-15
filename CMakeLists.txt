cmake_minimum_required(VERSION 3.10)
project(SistemaInvestimento LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Diretórios de include
include_directories(
    ${PROJECT_SOURCE_DIR}/Source
    ${PROJECT_SOURCE_DIR}/Source/Libs
    ${PROJECT_SOURCE_DIR}/Source/Presentation
    ${PROJECT_SOURCE_DIR}/Source/Service
    ${PROJECT_SOURCE_DIR}/Tests
)

# Procura SQLite3
find_package(SQLite3 REQUIRED)

# ========= Executável principal =========
add_executable(main
    Source/main.cpp
    Source/DB/DB.cpp
    Source/Libs/dominios.cpp
    Source/Presentation/AccountPre.cpp
    Source/Presentation/AuthenticationPre.cpp
    Source/Presentation/InvestmentPre.cpp
    Source/Service/AccountSer.cpp
    Source/Service/AuthenticationSer.cpp
    Source/Service/InvestmentSer.cpp
)

target_link_libraries(main PRIVATE SQLite::SQLite3)

# ========= updateData =========
add_executable(updateData
    Source/DB/UpdateDadosHistoricos.cpp
    Source/Libs/dominios.cpp
)

target_link_libraries(updateData PRIVATE SQLite::SQLite3)

# ========= Teste principal =========
add_executable(test_exec
    Source/Tests/TestMain.cpp
    Source/Libs/dominios.cpp
    Source/Presentation/AuthenticationPre.cpp
    Source/Presentation/AccountPre.cpp
    Source/Presentation/InvestmentPre.cpp
    Source/DB/DB.cpp
)

target_link_libraries(test_exec PRIVATE SQLite::SQLite3)

# ========= clearDbTest =========
add_executable(clearDbTest
    Source/Tests/ClearDbTest.cpp
    Source/Libs/dominios.cpp
    Source/DB/DB.cpp
)

target_link_libraries(clearDbTest PRIVATE SQLite::SQLite3)

# ========= Doxygen =========
find_package(Doxygen)
if (DOXYGEN_FOUND)
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Gerando documentação com Doxygen"
        VERBATIM
    )
endif()

# ========= Alvo 'run' =========
add_custom_target(run
    COMMAND main
    DEPENDS main
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
