//
// Created by Eneko on 22/03/2025.
//

#include "PropertyBlock.h"

PropertyBlock::PropertyBlock(const std::string &name, BlockConcept *blockConcept, Property *property)
    : TextBlock(name, blockConcept) {
    this->property = property;
}

PropertyBlock::PropertyBlock(const std::string &name, Location location, BlockConcept *blockConcept, Property *property)
    : TextBlock(name, location, blockConcept) {
    this->property = property;
}

PropertyBlock::~PropertyBlock() {
}

Property *PropertyBlock::getProperty() const {
    return property;
}
