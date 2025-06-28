# Sources for the library
set(GAME_MODULE_SOURCES
        game/engine/WindowedGameManager.cpp
        game/engine/event/EventManager.cpp
        game/engine/event/KeyboardEventManager.cpp
        game/engine/event/ApiEventManager.cpp
        game/engine/SpriteManager.cpp
        game/engine/LevelLoader.cpp
        game/engine/GraphicManager.cpp
        game/engine/GameManager.cpp
        game/engine/GameManager.h
)

# Headers for include directories
set(GAME_MODULE_INCLUDES
        game/engine
        game/engine/event
        ${CMAKE_SOURCE_DIR}/resources/definitions
        ${CMAKE_SOURCE_DIR}/resources/maps
        ${CMAKE_SOURCE_DIR}/resources/sprites
)

add_library(GameModules STATIC ${GAME_MODULE_SOURCES})

target_include_directories(GameModules PUBLIC ${GAME_MODULE_INCLUDES} ${CMAKE_SOURCE_DIR}/src)

# Find SFML and link necessary components
find_package(SFML COMPONENTS Network Graphics Window Audio System CONFIG REQUIRED)
target_link_libraries(GameModules PRIVATE SFML::Graphics SFML::Window SFML::System)

# Find Crow and asio
find_package(Crow CONFIG REQUIRED)
find_package(asio CONFIG REQUIRED)

target_link_libraries(GameModules PRIVATE Crow::Crow asio::asio)

# Include additional source files for the executable
set(APP_SOURCES
        main.cpp
        game/Game.cpp
        game/logic/level/block/Block.cpp
        game/logic/level/block/TextBlock.cpp
        game/logic/level/block/NounBlock.cpp
        game/logic/level/block/concept/BlockConcept.cpp
        game/logic/level/block/concept/ConceptController.cpp
        game/logic/level/block/VerbBlock.cpp
        game/logic/level/block/PropertyBlock.cpp
        game/logic/level/block/BlockFactory.cpp
        game/logic/property/Property.cpp
        game/logic/level/Level.cpp
        game/logic/GameLogic.cpp
        game/logic/property/StopProperty.cpp
        game/logic/property/PushProperty.cpp
        game/logic/property/YouProperty.cpp
        game/logic/property/WinProperty.cpp
        game/logic/rule/RuleInterpreter.cpp
        game/logic/rule/RuleParser.cpp
        game/logic/rule/Rule.cpp
        game/logic/rule/PropertyRule.cpp
        game/logic/rule/NounRule.cpp
        game/logic/property/PropertyController.cpp
        api/GameController.cpp
        api/command/Command.cpp
        api/command/CommandQueue.cpp
        api/dto/StatusDTO.cpp
        api/command/StatusCommand.cpp
        api/command/LevelCommand.cpp
        game/logic/property/DefeatProperty.cpp
        game/logic/property/HotProperty.cpp
        game/logic/property/ShutProperty.cpp
        game/logic/property/SinkProperty.cpp
)

add_executable(${PROJECT_NAME} ${APP_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
        game
        game/logic
        game/logic/level
        game/logic/level/block
        game/logic/level/block/concept
        game/logic/property
        game/logic/rule
        api
        api/command
        api/dto
        ${CMAKE_SOURCE_DIR}/resources/definitions
        ${CMAKE_SOURCE_DIR}/resources/maps
        ${CMAKE_SOURCE_DIR}/resources/sprites
)

target_link_libraries(${PROJECT_NAME} PRIVATE GameModules Crow::Crow asio::asio)

# Optional: Find and link Brotli if needed by your project
find_package(unofficial-brotli CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE unofficial::brotli::brotlidec unofficial::brotli::brotlienc)