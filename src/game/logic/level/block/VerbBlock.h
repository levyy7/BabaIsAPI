//
// Created by Eneko on 22/03/2025.
//

#ifndef VERBBLOCK_H
#define VERBBLOCK_H
#include "TextBlock.h"


class VerbBlock final : public TextBlock {
public:
    VerbBlock(const std::string &name, BlockConcept *blockConcept);

    VerbBlock(const std::string &name, Location location, BlockConcept *blockConcept);

    virtual ~VerbBlock();
};


#endif //VERBBLOCK_H
