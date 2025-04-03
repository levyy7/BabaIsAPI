//
// Created by Eneko on 22/03/2025.
//

#include "VerbBlock.h"

VerbBlock::VerbBlock(const std::string &name, BlockConcept *blockConcept)
    : TextBlock(name, blockConcept) {
}

VerbBlock::VerbBlock(const std::string &name, Location location, BlockConcept *blockConcept)
    : TextBlock(name, location, blockConcept) {
}

VerbBlock::~VerbBlock() {
}
