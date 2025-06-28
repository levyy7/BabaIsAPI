//
// Created by Eneko on 01/04/2025.
//

#include "HotProperty.h"

#include "BlockConcept.h"
#include "PropertyController.h"

HotProperty::HotProperty() : Property("HOT") {
}

std::set<Block *> HotProperty::getBlocksToDelete(Block *const executedBy, const std::vector<Block *> &blocksInCell) {
    std::set<Block *> toDelete;

    for (Block *block: blocksInCell) {
        if (block->getBlockConcept()->getBlockProperties().find(PropertyController::getPropertyMap()["MELT"]) != block->getBlockConcept()->getBlockProperties().end()) {
            toDelete.insert(block);
            break;
        }
    }

    return toDelete;
}
