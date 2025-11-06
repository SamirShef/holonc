cmake_minimum_required(VERSION 3.10)
project(holonc VERSION 0.0.1 LANGUAGES C)

set(CMAKE_C_STANDART 11)
set(CMAKE_C_STANDART_REQUIRED ON)

find_package(Doxygen REQUIRED)

if(DOXYGEN_FOUND)
    set(DOXYGEN_INPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/include")
    set(DOXYGEN_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/docs")
    set(DOXYGEN_HTML_OUTPUT "${DOXYGEN_OUTPUT_DIR}/html")
    
    doxygen_add_docs(
        generate-docs
        ${DOXYGEN_INPUT_DIR}
        COMMENT "Generating API documentation with Doxygen"
    )
endif()

file(GLOB_RECURSE SOURCES "src/*.c")

include_directories(include)

add_executable(${PROJECT_NAME} ${SOURCES})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)