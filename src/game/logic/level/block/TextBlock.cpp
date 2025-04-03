//
// Created by Eneko on 22/03/2025.
//

#include "TextBlock.h"

TextBlock::TextBlock(std::string name, BlockConcept *blockConcept): Block(name, blockConcept) {
}

TextBlock::TextBlock(std::string name, Location location, BlockConcept *blockConcept): Block(
    name, location, blockConcept) {
}

TextBlock::~TextBlock() = default;
