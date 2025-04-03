//
// Created by Eneko on 01/04/2025.
//

#include "DefeatProperty.h"

#include "BlockConcept.h"
#include "PropertyController.h"

DefeatProperty::DefeatProperty() : Property("DEFEAT") {
}

std::set<Block *> DefeatProperty::getBlocksToDelete(Block *const executedBy, const std::vector<Block *> &blocksInCell) {
    std::set<Block *> toDelete;

    for (Block *block: blocksInCell) {
        if (block->getBlockConcept()->getBlockProperties().contains(PropertyController::getPropertyMap()["YOU"])) {
            toDelete.insert(block);
            break;
        }
    }

    return toDelete;
}
