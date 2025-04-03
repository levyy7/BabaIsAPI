//
// Created by Eneko on 22/03/2025.
//

#include "BlockFactory.h"

#include <algorithm>
#include <map>
#include <set>
#include <stdexcept>

#include "NounBlock.h"
#include "VerbBlock.h"
#include "PropertyBlock.h"
#include "PropertyController.h"
#include "PushProperty.h"
#include "StopProperty.h"
#include "WinProperty.h"
#include "YouProperty.h"
#include "concept/ConceptController.h"

const std::set<std::string> BLOCK_NAMES = {
    "ALGAE", "ALL", "ANNI", "BABA", "BAT", "BELT", "BIRD", "BOG", "BOLT",
    "BOX", "BRICK", "BUBBLE", "BUG", "CAKE", "CLIFF", "CLOUD", "COG",
    "CRAB", "CURSOR", "DOOR", "DUST", "EMPTY", "FENCE", "FIRE", "FLAG",
    "FLOWER", "FOLIAGE", "FRUIT", "FUNGUS", "GHOST", "GRASS", "GROUP",
    "HAND", "HEDGE", "ICE", "IMAGE", "JELLY", "KEKE", "KEY", "LAVA",
    "LEAF", "LEVEL", "LINE", "LOVE", "ME", "MOON", "ORB", "PILLAR",
    "PIPE", "ROBOT", "ROCK", "ROCKET", "ROSE", "RUBBLE", "SKULL",
    "STAR", "STATUE", "SUN", "TEXT", "TILE", "TREE", "UFO", "VIOLET",
    "WALL", "WATER"
};

// Set of block names prefixed with "text_"
const std::set<std::string> NOUN_BLOCK_NAMES = []() {
    std::set<std::string> temp_set;
    for (const auto &name: BLOCK_NAMES) {
        temp_set.insert("TEXT_" + name);
    }
    return temp_set;
}();

// Set of verbs in lowercase
const std::set<std::string> VERB_BLOCK_NAMES = {
    "IS", "HAS", "MAKE", "AND", "NOT", "ON", "NEAR", "FACING", "LONELY"
};


Block *BlockFactory::produceBlock(const std::string &blockName) {
    return produceBlock(blockName, {0, 0});
}

Block *BlockFactory::produceBlock(const std::string &blockName, Location location) {
    std::string uppercaseBlockName = toUpperCase(blockName);

    if (BLOCK_NAMES.contains(uppercaseBlockName)) {
        //Is regular Block
        BlockConcept *blockConcept = ConceptController::getBlockConcept(uppercaseBlockName);

        return new Block(uppercaseBlockName, location, blockConcept);
    } else {
        //Is text block
        BlockConcept *blockConcept = ConceptController::getBlockConcept("TEXT");

        if (NOUN_BLOCK_NAMES.contains(uppercaseBlockName)) {
            std::string referencedConceptName = uppercaseBlockName.substr(5);
            BlockConcept *referencedConcept = ConceptController::getBlockConcept(referencedConceptName);

            return new NounBlock(uppercaseBlockName, location, blockConcept, referencedConcept);
        } else if (VERB_BLOCK_NAMES.contains(uppercaseBlockName)) {
            return new VerbBlock(uppercaseBlockName, location, blockConcept);
        } else if (PropertyController::getPropertyMap().contains(uppercaseBlockName)) {
            return new PropertyBlock(uppercaseBlockName, location, blockConcept,
                                     PropertyController::getPropertyMap()[uppercaseBlockName]);
        }
    }

    throw std::runtime_error("Not supported block name: " + blockName);
}


std::string BlockFactory::toUpperCase(const std::string &s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::toupper(c); });

    return result;
}
