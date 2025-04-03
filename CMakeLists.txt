cmake_minimum_required(VERSION 3.30)
project(BabaIsAPI)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LEVEL_LOADER_HEADERS
        ${CMAKE_SOURCE_DIR}/resources/definitions/NounType.def
        ${CMAKE_SOURCE_DIR}/resources/definitions/OpType.def
        ${CMAKE_SOURCE_DIR}/resources/definitions/PropertyType.def
        ${CMAKE_SOURCE_DIR}/resources/definitions/IconType.def
)

add_subdirectory(external)
add_subdirectory(src)
add_subdirectory(tests)

