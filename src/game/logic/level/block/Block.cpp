//
// Created by Eneko on 21/03/2025.
//

#include "Block.h"
#include "concept/BlockConcept.h"


Block::Block(const std::string &name, BlockConcept *blockConcept)
    : name(name), location({0, 0}), blockConcept(blockConcept) {
    blockConcept->addPhysicalRepresentation(this);
}

Block::Block(const std::string &name, const Location &location, BlockConcept *blockConcept)
    : name(name), location(location), blockConcept(blockConcept) {
    blockConcept->addPhysicalRepresentation(this);
}

Block::~Block() {
    blockConcept->removePhysicalRepresentation(this);
}


std::string Block::getName() const {
    return name;
}

Location Block::getLocation() const {
    return location;
}

BlockConcept *Block::getBlockConcept() const {
    return blockConcept;
}


Location Block::move(MoveDirection moveDirection) {
    switch (moveDirection) {
        case MoveDirection::UP:
            --location.y;
            break;
        case MoveDirection::DOWN:
            ++location.y;
            break;
        case MoveDirection::LEFT:
            --location.x;
            break;
        case MoveDirection::RIGHT:
            ++location.x;
            break;
        case MoveDirection::STILL:
            break;
    }

    return location;
}

Location Block::move(const Location &moveTo) {
    location = moveTo;

    return location;
}
