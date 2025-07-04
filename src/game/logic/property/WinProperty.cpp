//
// Created by Eneko on 26/03/2025.
//

#include "WinProperty.h"

#include "game/logic/level/block/concept/BlockConcept.h"


WinProperty::WinProperty() : Property("WIN") {
}

bool WinProperty::isWin(const std::vector<Block *> &blocksInCell) {
    for (const Block *block: blocksInCell) {
        if (block->getBlockConcept()->hasProperty("YOU")) return true;
    }

    return false;
}
