add_subdirectory(SFML)
add_subdirectory(Crow)

add_library(external INTERFACE)
target_link_libraries(external INTERFACE SFML::Main)
target_link_libraries(external INTERFACE SFML::Graphics)
target_link_libraries(external INTERFACE SFML::Window)
target_link_libraries(external INTERFACE Crow::Crow)