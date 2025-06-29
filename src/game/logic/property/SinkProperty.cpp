//
// Created by Eneko on 01/04/2025.
//

#include "SinkProperty.h"

#include "PropertyController.h"

SinkProperty::SinkProperty() : Property("SINK") {
}

std::set<Block *> SinkProperty::getBlocksToDelete(Block *const executedBy, const std::vector<Block *> &blocksInCell) {
    std::set<Block *> toDelete;

    for (Block *block: blocksInCell) {
        if (block != executedBy)
            toDelete.insert(executedBy);
        toDelete.insert(block);
    }

    return toDelete;
}
