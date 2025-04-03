//
// Created by Eneko on 22/03/2025.
//
#include "BlockConcept.h"

#include "Property.h"
#include "../Block.h"
#include "../NounBlock.h"

BlockConcept::BlockConcept(std::string name) {
    this->name = name;
    this->physicalRepresentations = std::unordered_set<Block *>{};
}

std::string BlockConcept::getName() const {
    return this->name;
}

void BlockConcept::addProperty(Property *property) {
    this->properties.insert(property);
}

void BlockConcept::clearProperties() {
    this->properties.clear();
}

std::unordered_set<Block *> BlockConcept::getBlockRepresentations() const {
    return physicalRepresentations;
}

bool BlockConcept::isPushedBy(const Block *block) const {
    for (Property *property: properties) {
        if (property->isPushedBy(block)) return true;
    }

    return false;
}

bool BlockConcept::stops(const Block *block) const {
    if (isPushedBy(block)) return false;

    for (Property *property: properties) {
        if (property->stops(block)) return true;
    }

    return false;
}

bool BlockConcept::isMoveable() const {
    for (Property *property: properties) {
        if (property->isMoveable()) return true;
    }

    return false;
}

std::unordered_set<NounBlock *> BlockConcept::getBlockReferences() const {
    return physicalReferences;
}

std::unordered_set<Property *> BlockConcept::getBlockProperties() const {
    return properties;
}

bool BlockConcept::hasProperty(const std::string &name) const {
    for (Property *p: properties) {
        if (p->getName() == name) return true;
    }

    return false;
}

bool BlockConcept::isWin(const std::vector<Block *> &blocksInCell) const {
    for (Property *property: properties) {
        if (property->isWin(blocksInCell)) return true;
    }

    return false;
}

std::set<Block *>
BlockConcept::getBlocksToDelete(Block *const calledBy, const std::vector<Block *> &blocksInCell) const {
    std::set<Block *> blocksToDelete = {};

    for (Property *property: properties) {
        blocksToDelete = unionSets(blocksToDelete, property->getBlocksToDelete(calledBy, blocksInCell));
    }

    return blocksToDelete;
}

void BlockConcept::addPhysicalRepresentation(Block *block) {
    physicalRepresentations.insert(block);
}

void BlockConcept::removePhysicalRepresentation(Block *block) {
    physicalRepresentations.erase(block);
}

void BlockConcept::addPhysicalReference(NounBlock *noun) {
    physicalReferences.insert(noun);
}

void BlockConcept::removePhysicalReference(NounBlock *noun) {
    physicalReferences.erase(noun);
}


std::set<Block *> BlockConcept::unionSets(const std::set<Block *> &set1, const std::set<Block *> &set2) {
    std::set<Block *> result(set1); // Start with the first set
    result.insert(set2.begin(), set2.end()); // Insert all elements of the second set
    return result;
}
