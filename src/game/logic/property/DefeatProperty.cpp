//
// Created by Eneko on 01/04/2025.
//

#include "DefeatProperty.h"

#include "PropertyController.h"
#include "game/logic/level/block/concept/BlockConcept.h"

DefeatProperty::DefeatProperty() : Property("DEFEAT") {
}

std::set<Block *> DefeatProperty::getBlocksToDelete(Block *const executedBy, const std::vector<Block *> &blocksInCell) {
    std::set<Block *> toDelete;

    for (Block *block: blocksInCell) {
        if (block->getBlockConcept()->getBlockProperties().find(PropertyController::getPropertyMap()["YOU"]) != block->getBlockConcept()->getBlockProperties().end()) {
            toDelete.insert(block);
            break;
        }
    }

    return toDelete;
}
