//
// Created by Eneko on 23/03/2025.
//

#include "Property.h"

Property::Property(std::string name) {
    this->name = name;
}

std::string Property::getName() const {
    return name;
}

std::set<Block *> Property::getBlocksToDelete(Block *const executedBy, const std::vector<Block *> &blocksInCell) {
    return {};
}

bool Property::stops(const Block *&block) {
    return false;
}

bool Property::isPushedBy(const Block *&block) {
    return false;
}

bool Property::isMoveable() {
    return false;
}

bool Property::isWin(const std::vector<Block *> &blocksInCell) {
    return false;
}
