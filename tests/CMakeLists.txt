add_executable(tests_run
        TestExample.cpp
        ${CMAKE_SOURCE_DIR}/src/game/logic/level/block/Block.cpp
        ${CMAKE_SOURCE_DIR}/src/game/logic/level/block/Block.h
        ${CMAKE_SOURCE_DIR}/src/game/logic/level/block/concept/BlockConcept.cpp
        ${CMAKE_SOURCE_DIR}/src/game/logic/level/block/concept/BlockConcept.h
        ${CMAKE_SOURCE_DIR}/src/game/logic/level/block/TextBlock.cpp
        ${CMAKE_SOURCE_DIR}/src/game/logic/level/block/TextBlock.h
        ${CMAKE_SOURCE_DIR}/src/game/logic/level/block/concept/ConceptController.cpp
        ${CMAKE_SOURCE_DIR}/src/game/logic/level/block/concept/ConceptController.h
        ${CMAKE_SOURCE_DIR}/src/game/logic/level/block/NounBlock.cpp
        ${CMAKE_SOURCE_DIR}/src/game/logic/level/block/NounBlock.h
        ${CMAKE_SOURCE_DIR}/src/game/logic/level/block/VerbBlock.cpp
        ${CMAKE_SOURCE_DIR}/src/game/logic/level/block/VerbBlock.h
        ${CMAKE_SOURCE_DIR}/src/game/logic/level/block/PropertyBlock.cpp
        ${CMAKE_SOURCE_DIR}/src/game/logic/level/block/PropertyBlock.h
        ${CMAKE_SOURCE_DIR}/src/game/logic/level/block/BlockFactory.cpp
        ${CMAKE_SOURCE_DIR}/src/game/logic/level/block/BlockFactory.h
        ${CMAKE_SOURCE_DIR}/src/game/logic/property/Property.cpp
        ${CMAKE_SOURCE_DIR}/src/game/logic/property/Property.h
        ${CMAKE_SOURCE_DIR}/src/game/logic/level/Level.cpp
        ${CMAKE_SOURCE_DIR}/src/game/logic/level/Level.h
        ${CMAKE_SOURCE_DIR}/src/game/logic/GameLogic.cpp
        ${CMAKE_SOURCE_DIR}/src/game/logic/GameLogic.h
        ${CMAKE_SOURCE_DIR}/src/game/logic/property/StopProperty.cpp
        ${CMAKE_SOURCE_DIR}/src/game/logic/property/StopProperty.h
        ${CMAKE_SOURCE_DIR}/src/game/logic/property/PushProperty.cpp
        ${CMAKE_SOURCE_DIR}/src/game/logic/property/PushProperty.h
        ${CMAKE_SOURCE_DIR}/src/game/logic/property/YouProperty.cpp
        ${CMAKE_SOURCE_DIR}/src/game/logic/property/YouProperty.h
        ${CMAKE_SOURCE_DIR}/src/game/logic/property/WinProperty.cpp
        ${CMAKE_SOURCE_DIR}/src/game/logic/property/WinProperty.h
        ${CMAKE_SOURCE_DIR}/src/game/logic/rule/RuleInterpreter.cpp
        ${CMAKE_SOURCE_DIR}/src/game/logic/rule/RuleInterpreter.h
        ${CMAKE_SOURCE_DIR}/src/game/logic/rule/RuleParser.cpp
        ${CMAKE_SOURCE_DIR}/src/game/logic/rule/RuleParser.h
        ${CMAKE_SOURCE_DIR}/src/game/logic/rule/Rule.cpp
        ${CMAKE_SOURCE_DIR}/src/game/logic/rule/Rule.h
        ${CMAKE_SOURCE_DIR}/src/game/logic/rule/PropertyRule.cpp
        ${CMAKE_SOURCE_DIR}/src/game/logic/rule/PropertyRule.h
        ${CMAKE_SOURCE_DIR}/src/game/logic/rule/NounRule.cpp
        ${CMAKE_SOURCE_DIR}/src/game/logic/rule/NounRule.h
        ${CMAKE_SOURCE_DIR}/src/game/logic/property/PropertyController.cpp
        ${CMAKE_SOURCE_DIR}/src/game/logic/property/PropertyController.h
)

find_package(Catch2 CONFIG REQUIRED)
target_link_libraries(tests_run PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)

include_directories(${CMAKE_SOURCE_DIR}/src/ ${CMAKE_SOURCE_DIR}/tests)

include(Catch)
catch_discover_tests(tests_run)