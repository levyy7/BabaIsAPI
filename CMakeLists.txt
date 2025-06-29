cmake_minimum_required(VERSION 3.22)
project(BabaIsAPI)

set(LEVEL_LOADER_HEADERS
    ${CMAKE_SOURCE_DIR}/resources/definitions/NounType.def
    ${CMAKE_SOURCE_DIR}/resources/definitions/OpType.def
    ${CMAKE_SOURCE_DIR}/resources/definitions/PropertyType.def
    ${CMAKE_SOURCE_DIR}/resources/definitions/IconType.def
)

add_subdirectory(src)
if (NOT CMAKE_BUILD_TYPE STREQUAL "Release")
    add_subdirectory(tests)
endif()
