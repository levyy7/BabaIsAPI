//
// Created by Eneko on 22/03/2025.
//

#include "NounBlock.h"

#include "game/logic/level/block/concept/BlockConcept.h"

NounBlock::NounBlock(const std::string &name, BlockConcept *blockConcept, BlockConcept *referencedConcept)
    : TextBlock(name, blockConcept), referencedConcept(referencedConcept) {
    referencedConcept->addPhysicalReference(this);
}

NounBlock::NounBlock(const std::string &name, Location location, BlockConcept *blockConcept,
                     BlockConcept *referencedConcept)
    : TextBlock(name, location, blockConcept), referencedConcept(referencedConcept) {
    referencedConcept->addPhysicalReference(this);
}

NounBlock::~NounBlock() {
    referencedConcept->removePhysicalReference(this);
}

BlockConcept *NounBlock::getReferencedConcept() const {
    return referencedConcept;
}
