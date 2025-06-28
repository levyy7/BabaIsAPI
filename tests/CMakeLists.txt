add_executable(tests_run
        TestExample.cpp
        ../src/game/logic/level/block/Block.cpp
        ../src/game/logic/level/block/Block.h
        ../src/game/logic/level/block/concept/BlockConcept.cpp
        ../src/game/logic/level/block/concept/BlockConcept.h
        ../src/game/logic/level/block/TextBlock.cpp
        ../src/game/logic/level/block/TextBlock.h
        ../src/game/logic/level/block/concept/ConceptController.cpp
        ../src/game/logic/level/block/concept/ConceptController.h
        ../src/game/logic/level/block/NounBlock.cpp
        ../src/game/logic/level/block/NounBlock.h
        ../src/game/logic/level/block/VerbBlock.cpp
        ../src/game/logic/level/block/VerbBlock.h
        ../src/game/logic/level/block/PropertyBlock.cpp
        ../src/game/logic/level/block/PropertyBlock.h
        ../src/game/logic/level/block/BlockFactory.cpp
        ../src/game/logic/level/block/BlockFactory.h
        game/logic/level/block/TestBlock.cpp
        ../src/game/logic/property/Property.cpp
        ../src/game/logic/property/Property.h
        ../src/game/logic/level/Level.cpp
        ../src/game/logic/level/Level.h
        ../src/game/logic/GameLogic.cpp
        ../src/game/logic/GameLogic.h
        ../src/game/logic/property/StopProperty.cpp
        ../src/game/logic/property/StopProperty.h
        ../src/game/logic/property/PushProperty.cpp
        ../src/game/logic/property/PushProperty.h
        ../src/game/logic/property/YouProperty.cpp
        ../src/game/logic/property/YouProperty.h
        ../src/game/logic/property/WinProperty.cpp
        ../src/game/logic/property/WinProperty.h
        ../src/game/logic/rule/RuleInterpreter.cpp
        ../src/game/logic/rule/RuleInterpreter.h
        ../src/game/logic/rule/RuleParser.cpp
        ../src/game/logic/rule/RuleParser.h
        ../src/game/logic/rule/Rule.cpp
        ../src/game/logic/rule/Rule.h
        ../src/game/logic/rule/PropertyRule.cpp
        ../src/game/logic/rule/PropertyRule.h
        ../src/game/logic/rule/NounRule.cpp
        ../src/game/logic/rule/NounRule.h
        ../src/game/logic/property/PropertyController.cpp
        ../src/game/logic/property/PropertyController.h
)

find_package(Catch2 CONFIG REQUIRED)
target_link_libraries(tests_run PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)

include_directories(${CMAKE_SOURCE_DIR}/src/game/logic/level/block ${CMAKE_SOURCE_DIR}/src/game/logic/level/block/concept)

include(Catch)
catch_discover_tests(tests_run)