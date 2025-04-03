//
// Created by Eneko on 22/03/2025.
//

#ifndef PROPERTYBLOCK_H
#define PROPERTYBLOCK_H
#include "Property.h"
#include "TextBlock.h"


class PropertyBlock : public TextBlock {
public:
    PropertyBlock(const std::string &name, BlockConcept *blockConcept, Property *property);

    PropertyBlock(const std::string &name, Location location, BlockConcept *blockConcept, Property *property);

    virtual ~PropertyBlock();

    [[nodiscard]] Property *getProperty() const;

private:
    Property *property;
};


#endif //PROPERTYBLOCK_H
