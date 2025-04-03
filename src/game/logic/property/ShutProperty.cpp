//
// Created by Eneko on 01/04/2025.
//

#include "ShutProperty.h"

#include "BlockConcept.h"
#include "PropertyController.h"

ShutProperty::ShutProperty() : Property("SHUT") {
}

bool ShutProperty::stops(const Block *&block) {
    if (block->getBlockConcept()->getBlockProperties().contains(PropertyController::getPropertyMap()["KEY"])) return
            false;

    return true;
}

std::set<Block *> ShutProperty::getBlocksToDelete(Block *const executedBy, const std::vector<Block *> &blocksInCell) {
    std::set<Block *> toDelete;

    for (Block *block: blocksInCell) {
        if (block->getBlockConcept()->getBlockProperties().contains(PropertyController::getPropertyMap()["OPEN"])) {
            toDelete.insert(executedBy);
            toDelete.insert(block);
            break;
        }
    }

    return toDelete;
}
