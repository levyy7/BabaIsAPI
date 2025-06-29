//
// Created by Eneko on 01/04/2025.
//

#include "ShutProperty.h"

#include "PropertyController.h"
#include "game/logic/level/block/concept/BlockConcept.h"

ShutProperty::ShutProperty() : Property("SHUT") {
}

bool ShutProperty::stops(const Block *&block) {
    if (block->getBlockConcept()->getBlockProperties().find(PropertyController::getPropertyMap()["KEY"]) != block->getBlockConcept()->getBlockProperties().end()) return
            false;

    return true;
}

std::set<Block *> ShutProperty::getBlocksToDelete(Block *const executedBy, const std::vector<Block *> &blocksInCell) {
    std::set<Block *> toDelete;

    for (Block *block: blocksInCell) {
        if (block->getBlockConcept()->getBlockProperties().find(PropertyController::getPropertyMap()["OPEN"]) != block->getBlockConcept()->getBlockProperties().end()) {
            toDelete.insert(executedBy);
            toDelete.insert(block);
            break;
        }
    }

    return toDelete;
}
